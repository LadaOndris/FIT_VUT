/*
 * Sample implementation of Huffman two-pass algorithm.
 * Original sources taken from DDJ October, 1992.
 *
 * Implemented by Sergey Vakulenko, <vak@kiae.su>.
 */

#include <stdio.h>

/* ---- Huffman tree structure for building ---- */
struct htree {
	long cnt;               /* character frequency */
	short parent;           /* offset to parent node */
	short right;            /* offset to right child node */
	short left;             /* offset to left child node */
};

/* ---- Huffman tree structure in compressed file ---- */
struct htr {
	short right;            /* offset to right child node */
	short left;             /* offset to left child node */
};

static long bytectr;
static struct htree ht [512];
static struct htr htr [256];
static short root;
static short treect;
static FILE *fo;
static short ct;
static char out [1024];
static short in;

/* ---- flush remaining bits to the compressed output file ---- */
static void outflush ()
{
	char *p;

	if (ct == 0)
		return;
	while (ct < sizeof (out))
		out [ct++] = 0;
	p = out;
	while (p < out+sizeof(out)) {
		int c = *p++ << 7;
		c |= *p++ << 6;
		c |= *p++ << 5;
		c |= *p++ << 4;
		c |= *p++ << 3;
		c |= *p++ << 2;
		c |= *p++ << 1;
		c |= *p++;
		putc (c, fo);
	}
	ct = 0;
}

/* ---- compress a character value into a bit stream ---- */
static void compress (int h, int child)
{
	int hp;

	if ((hp = ht[h].parent) != -1)
		compress (hp, h);
	if (child) {
		if (ct >= sizeof (out))
			outflush ();
		out [ct++] = (child == ht[h].left);
	}
}

/* ---- build a Huffman tree from a frequency array ---- */
static void buildtree (void)
{
	int i;

	treect = 256;
	/* ---- preset node pointers to -1 ---- */
	for (i=0; i<treect; ++i) {
		ht[i].parent = -1;
		ht[i].right = -1;
		ht[i].left = -1;
	}
	/* ---- build the Huffman tree ---- */
	while (1) {
		int h1= -1, h2 = -1;
		/* ---- find the two lowest frequencies ---- */
		for (i=0; i<treect; ++i) {
			if (i != h1) {
				struct htree *htt = ht+i;
				/* ---- find a node without a parent ---- */
				if (htt->cnt > 0 && htt->parent == -1) {
					/* ---- h1 & h2 -> lowest nodes ---- */
					if (h1 == -1 || htt->cnt < ht[h1].cnt) {
						if (h2 == -1 || ht[h1].cnt < ht[h2].cnt)
							h2 = h1;
						h1 = i;
					} else if (h2 == -1 || htt->cnt < ht[h2].cnt)
						h2 = i;
				}
			}
		}
		/* ---- if only h1 -> a node, that's the root ---- */
		if (h2 == -1) {
			root = h1 - 256;
			break;
		}
		/* ---- combine two nodes and add one ---- */
		ht[h1].parent = treect;
		ht[h2].parent = treect;
		if (! ht)
			break;
		/* ---- the new node's frequency is the sum of the two
			nodes with the lowest frequencies ---- */
		ht[treect].cnt = ht[h1].cnt + ht[h2].cnt;
		/* ---- the new node points to the two that it combines ---- */
		ht[treect].right = h1;
		ht[treect].left = h2;
		/* ---- the new node has no parent (yet) ---- */
		ht[treect].parent = -1;
		++treect;
	}
	treect -= 256;
}

/* ---- compress the file from i to o ---- */
huff (FILE *i, FILE *o)
{
	int c;

	/* ---- global variable is faster than parameter passing ---- */
	fo = o;

	/* ---- read the input file and count character frequency ---- */
	bytectr = 0;
	while ((c = getc (i)) >= 0) {
		++ht[c].cnt;
		++bytectr;
	}

	/* ---- build the Huffman tree ---- */
	buildtree ();
	/* ---- write the byte count to the output file ---- */
	fwrite (&bytectr, sizeof (bytectr), 1, fo);
	/* ---- write the tree count to the output file ---- */
	fwrite (&treect, sizeof (treect), 1, fo);
	/* ---- write the root offset to the output file ---- */
	fwrite (&root, sizeof (root), 1, fo);
	/* ---- write the tree to the output file ---- */
	for (c=0; c<treect; ++c) {
		short lf = ht[c+256].left - 256;
		short rt = ht[c+256].right - 256;
		fwrite (&lf, sizeof (lf), 1, fo);
		fwrite (&rt, sizeof (rt), 1, fo);
	}

	/* ---- compress the file ---- */
	fseek (i, 0L, 0);
	ct = 0;
	while ((c = getc (i)) >= 0)
		compress (c, 0);
	outflush (fo);
}

/* ---- read a character from the compressed file ---- */
int getchuff (FILE *i)
{
	short h = root;
	/* ---- walk the Huffman tree ---- */
	do {
		/* ---- h is a node pointer ---- */
		if (ct == 8) {
			/* ---- read 8 bits of compressed data ---- */
			if ((in = getc (i)) < 0)
				return (-1);
			ct = 0;
		}
		/* ---- point to left or right node based on msb --- */
		if (in & 0x80)
			h = htr[h].left;
		else
			h = htr[h].right;
		/* ---- shift the next bit in ---- */
		in <<= 1;
		++ct;
	} while (h >= 0);
	/* ---- h < 0 = decompressed character ---- */
	return (h + 256);
}

/* ---- decompress the file from i to o ---- */
dehuff (FILE *i, FILE *o)
{
	int c;

	/* ---- read the byte count ---- */
	fread (&bytectr, sizeof (bytectr), 1, i);
	/* ---- read the frequency count ---- */
	fread (&treect, sizeof (treect), 1, i);
	/* ---- read the root offset ---- */
	fread (&root, sizeof (root), 1, i);
	/* ---- read in the tree ---- */
	for (c=0; c<treect; ++c) {
		fread (&htr[c].left, sizeof (htr[c].left), 1, i);
		fread (&htr[c].right, sizeof (htr[c].right), 1, i);
	}
	ct = 8;
	while (--bytectr >= 0 && (c = getchuff (i)) >= 0)
		putc (c, o);
}

int main (int argc, char **argv)
{
	FILE *i, *o;
	int c, dflag=0;

	if (! strcmp (argv[0] + strlen (argv[0]) - 6, "dehuff"))
		++dflag;
	if (! strcmp (argv[1], "-d")) {
		++argv;
		--argc;
		++dflag;
	}
	if (argc < 3) {
		printf ("Usage: huff [-d] infile outfile\n\n");
		printf ("Compresses (by default) or decompresses (-d) infile\n");
		printf ("to outfile, using Huffman two-pass algorithm.\n");
		printf ("Implemented by Sergey Vakulenko, <vak@kiae.su>.\n");
		exit (1);
	}
	i = fopen (argv[1], "rb");
	if (! i) {
		perror (argv[1]);
		exit (1);
	}
	o = fopen (argv[2], "wb");
	if (! o) {
		perror (argv[2]);
		exit (1);
	}
	if (dflag)
		dehuff (i, o);
	else
		huff (i, o);
	fclose (i);
	fclose (o);
	return (0);
}
