/**
 * Kostra programu pro 3. projekt IZP 2018/19
 *
 * Jednoducha shlukova analyza: 2D nejblizsi soused.
 * Single linkage
 */
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <math.h> // sqrtf
#include <limits.h> // INT_MAX
#include <stdbool.h>
#include <errno.h>

/*****************************************************************
 * Ladici makra. Vypnout jejich efekt lze definici makra
 * NDEBUG, napr.:
 *   a) pri prekladu argumentem prekladaci -DNDEBUG
 *   b) v souboru (na radek pred #include <assert.h>
 *      #define NDEBUG
 */
#ifdef NDEBUG
#define debug(s)
#define dfmt(s, ...)
#define dint(i)
#define dfloat(f)
#else

// vypise ladici retezec
#define debug(s) printf("- %s\n", s)

// vypise formatovany ladici vystup - pouziti podobne jako printf
#define dfmt(s, ...) printf(" - "__FILE__":%u: "s"\n",__LINE__,__VA_ARGS__)

// vypise ladici informaci o promenne - pouziti dint(identifikator_promenne)
#define dint(i) printf(" - " __FILE__ ":%u: " #i " = %d\n", __LINE__, i)

// vypise ladici informaci o promenne typu float - pouziti
// dfloat(identifikator_promenne)
#define dfloat(f) printf(" - " __FILE__ ":%u: " #f " = %g\n", __LINE__, f)

#endif

#define is_fractional(x) ((x) - (int)(x)) 

/*****************************************************************
 * Deklarace potrebnych datovych typu:
 *
 * TYTO DEKLARACE NEMENTE
 *
 *   struct obj_t - struktura objektu: identifikator a souradnice
 *   struct cluster_t - shluk objektu:
 *      pocet objektu ve shluku,
 *      kapacita shluku (pocet objektu, pro ktere je rezervovano
 *          misto v poli),
 *      ukazatel na pole shluku.
 */

struct obj_t {
    int id;
    float x;
    float y;
};

struct cluster_t {
    int size;
    int capacity;
    struct obj_t *obj;
};

/*****************************************************************
 * Deklarace potrebnych funkci.
 *
 * PROTOTYPY FUNKCI NEMENTE
 *
 * IMPLEMENTUJTE POUZE FUNKCE NA MISTECH OZNACENYCH 'TODO'
 *
 */

/*
 Inicializace shluku 'c'. Alokuje pamet pro cap objektu (kapacitu).
 Ukazatel NULL u pole objektu znamena kapacitu 0.
*/
void init_cluster(struct cluster_t *c, int cap)
{
    assert(c != NULL);
    assert(cap >= 0);

	c->size = 0;
	c->capacity = cap;
	c->obj = malloc(sizeof(struct obj_t) * cap);
	if (!c->obj) {
		c->capacity = 0;
	}
}

/*
 Odstraneni vsech objektu shluku a inicializace na prazdny shluk.
 */
void clear_cluster(struct cluster_t *c)
{
	if (c->obj) { 
		free(c->obj);
		c->obj = NULL;
	}
	c->size = 0;
	c->capacity = 0;
}

/// Chunk of cluster objects. Value recommended for reallocation.
const int CLUSTER_CHUNK = 10;

/*
 Zmena kapacity shluku 'c' na kapacitu 'new_cap'.
 Vraci NULL pokud se alokace nepovedla, jinak vraci 
 ukazatel na realokovanej shluk.
 */
struct cluster_t *resize_cluster(struct cluster_t *c, int new_cap)
{
    assert(c);
    assert(c->capacity >= 0);
    assert(new_cap >= 0);

    if (c->capacity >= new_cap)
        return c;

    size_t size = sizeof(struct obj_t) * new_cap;

    void *arr = realloc(c->obj, size);
	if (arr == NULL)
        return NULL;

    c->obj = (struct obj_t*)arr;
    c->capacity = new_cap;
    return c;
}

/*
 Prida objekt 'obj' na konec shluku 'c'. Rozsiri shluk, pokud se do nej objekt
 nevejde.
 */
void append_cluster(struct cluster_t *c, struct obj_t obj)
{
	int new_cap = c->size + CLUSTER_CHUNK; 
	struct cluster_t *cluster = resize_cluster(c, new_cap);
	if (cluster) {
		c->obj[c->size] = obj;
		c->size++;
	}
}

/*
 Seradi objekty ve shluku 'c' vzestupne podle jejich identifikacniho cisla.
 */
void sort_cluster(struct cluster_t *c);

/*
 Do shluku 'c1' prida objekty 'c2'. Shluk 'c1' bude v pripade nutnosti rozsiren.
 Objekty ve shluku 'c1' budou serazeny vzestupne podle identifikacniho cisla.
 Shluk 'c2' bude nezmenen. Pokud se pridani objektu do shluhu 'c1' nepodari, 
 c1->size po vykonani bude mensi nez c1->size + c2->size pred vykonanim.
 */
void merge_clusters(struct cluster_t *c1, struct cluster_t *c2)
{
    assert(c1 != NULL);
    assert(c2 != NULL);

	for (int i = 0; i < c2->size; i++) {
		append_cluster(c1, c2->obj[i]);
	}
	sort_cluster(c1);
}

/**********************************************************************/
/* Prace s polem shluku */

/*
 Odstrani shluk z pole shluku 'carr'. Pole shluku obsahuje 'narr' polozek
 (shluku). Shluk pro odstraneni se nachazi na indexu 'idx'. Funkce vraci novy
 pocet shluku v poli.
*/
int remove_cluster(struct cluster_t *carr, int narr, int idx)
{
    assert(idx < narr);
    assert(narr > 0);
	clear_cluster(&carr[idx]);
	for (int i = idx + 1; i < narr; i++) {
		carr[i-1] = carr[i];
	}
	return narr-1;
}

/*
 Pocita Euklidovskou vzdalenost mezi dvema objekty.
 */
float obj_distance(struct obj_t *o1, struct obj_t *o2)
{
    assert(o1 != NULL);
    assert(o2 != NULL);

    float abs_x = fabs(o1->x - o2->x);
	float abs_y = fabs(o1->y - o2->y);
	return sqrt(abs_x * abs_x + abs_y * abs_y);
}

/*
 Pocita vzdalenost dvou shluku.
*/
float cluster_distance(struct cluster_t *c1, struct cluster_t *c2)
{
    assert(c1 != NULL);
    assert(c1->size > 0);
    assert(c2 != NULL);
    assert(c2->size > 0);

    float min_dist = INFINITY;

	for (int i = 0; i < c1->size; i++) {
		for (int j = 0; j < c2->size; j++) {
			float dist = obj_distance(&c1->obj[i], &c2->obj[j]);		
			if (dist < min_dist) {
				min_dist = dist;
			}
		}
	}
	return min_dist;
}

/*
 Funkce najde dva nejblizsi shluky. V poli shluku 'carr' o velikosti 'narr'
 hleda dva nejblizsi shluky. Nalezene shluky identifikuje jejich indexy v poli
 'carr'. Funkce nalezene shluky (indexy do pole 'carr') uklada do pameti na
 adresu 'c1' resp. 'c2'.
*/
void find_neighbours(struct cluster_t *carr, int narr, int *c1, int *c2)
{
    assert(narr > 0);

	float min_dist = INFINITY;

	for (int i = 0; i < narr; i++) {
		for (int j = 0; j < narr; j++) {
			if (i == j)
				continue;
			float dist = cluster_distance(&carr[i], &carr[j]);
			if (dist < min_dist) {
				min_dist = dist;
				*c1 = i;
				*c2 = j;
			}
		}
	}
}

// pomocna funkce pro razeni shluku
static int obj_sort_compar(const void *a, const void *b)
{
    // TUTO FUNKCI NEMENTE
    const struct obj_t *o1 = (const struct obj_t *)a;
    const struct obj_t *o2 = (const struct obj_t *)b;
    if (o1->id < o2->id) return -1;
    if (o1->id > o2->id) return 1;
    return 0;
}

/*
 Razeni objektu ve shluku vzestupne podle jejich identifikatoru.
*/
void sort_cluster(struct cluster_t *c)
{
    // TUTO FUNKCI NEMENTE
    qsort(c->obj, c->size, sizeof(struct obj_t), &obj_sort_compar);
}

/*
 Tisk shluku 'c' na stdout.
*/
void print_cluster(struct cluster_t *c)
{
    // TUTO FUNKCI NEMENTE
    for (int i = 0; i < c->size; i++)
    {
        if (i) putchar(' ');
        printf("%d[%g,%g]", c->obj[i].id, c->obj[i].x, c->obj[i].y);
    }
    putchar('\n');
}

/*
 * Uvolneni vsech shluku.
 */
void free_clusters(struct cluster_t *carr, int narr) {
	if (!carr)
		return;
	for (int i = 0; i < narr; i++) {
		clear_cluster(&carr[i]);
	}
	free(carr);
	carr = NULL;
}

/*
 * Kontroluje, ze data struktury obj obsahuji spravne hodnoty a jsou ve spravnem formatu.
 */
bool invalid_data(struct obj_t obj, struct cluster_t *carr, int clusters_count) {
	if (obj.x < 0 || obj.y < 0 || obj.x > 1000 || obj.y > 1000)
		return true;
	if (is_fractional(obj.x) || is_fractional(obj.y)) 
		return true;
	for (int i = 0; i < clusters_count; i++) {
		if (carr[i].obj && carr[i].obj->id == obj.id) {
			return true;
		}
	}
	return false;
}

/*
 Ze souboru 'filename' nacte objekty. Pro kazdy objekt vytvori shluk a ulozi
 jej do pole shluku. Alokuje prostor pro pole vsech shluku a ukazatel na prvni
 polozku pole (ukalazatel na prvni shluk v alokovanem poli) ulozi do pameti,
 kam se odkazuje parametr 'arr'. Funkce vraci pocet nactenych objektu (shluku).
 V pripade nejake chyby uklada do pameti, kam se odkazuje 'arr', hodnotu NULL.
*/
int load_clusters(char *filename, struct cluster_t **arr)
{
    assert(arr != NULL);
	*arr = NULL;
	// OPEN FILE
	FILE *fr;
	if ((fr = fopen(filename, "r")) == NULL) {
		fprintf(stderr, "Couldn't open a file: %s\n", filename);
		return 0;
	}
	// LOAD CLUSTERS COUNT
	int clusters_count;
	if (fscanf(fr, "count=%d", &clusters_count) != 1) {
		fprintf(stderr, "Parse error: Couldn't parse clusters count from a file.\n");
		fclose(fr);
		return 0;
	}
	// ALLOC CLUSTERS ARRAY
	struct cluster_t *clusters_arr = malloc(sizeof(struct cluster_t) * clusters_count);
	if (!clusters_arr) {
		fprintf(stderr, "Allocation failed.\n");
		fclose(fr);
		return 0;
	}
	// LOAD EACH LINE AS CLUSTER
	int i = 0;
	for (; i < clusters_count; i++) {
		init_cluster(&clusters_arr[i], CLUSTER_CHUNK);
		struct obj_t obj;
		if (fscanf(fr, "%d %f %f", &obj.id, &obj.x, &obj.y) != 3 
			|| invalid_data(obj, clusters_arr, i)) {
			free_clusters(clusters_arr, i + 1);
			fprintf(stderr, "Parse error: Invalid input data or end of file reached.\n");
			fclose(fr);
			return 0;
		}
		append_cluster(&clusters_arr[i], obj);
		if (clusters_arr[i].size == 0) {
			fprintf(stderr, "Error occured. Objects couldn't be loaded.\n");
			free_clusters(clusters_arr, i + 1);
			fclose(fr);
			return 0;
		}
	}
	fclose(fr);
	*arr = clusters_arr;
	return i;
}

/*
 Tisk pole shluku. Parametr 'carr' je ukazatel na prvni polozku (shluk).
 Tiskne se prvnich 'narr' shluku.
*/
void print_clusters(struct cluster_t *carr, int narr)
{
	if (narr <= 0)
		return;
    printf("Clusters:\n");
    for (int i = 0; i < narr; i++)
    {
        printf("cluster %d: ", i);
        print_cluster(&carr[i]);
    }
}

/*
 * Vypis napovedy k programu.
 */
void print_help() {
	printf("Start program with two arguments.\n"
		   "First argument specifies the file with objects to be clustered\n"
		   "and the second one the required number of clusters.\n\n");
}

/*
 * Vraci nenulove cislo, pokud nastala chyba.
 */
int parse_arguments(int argc, char *argv[], int *clusters_count) {
	if (argc == 2) {
		*clusters_count = 1;
		return 0;
	} 
	char *end_ptr;
	*clusters_count = strtod(argv[2], &end_ptr);
	if (*end_ptr != '\0' || *clusters_count <= 0 || errno == ERANGE) {
		fprintf(stderr, "Invalid argument: %s\n", argv[2]);
		return 1;
	}
	return 0;
}

/*
 * Provadi algoritmus seskupeni shluku, dokud se nedosahne 
 * pozadovaneho poctu shluku.
 */
void group_clusters(struct cluster_t **clusters, int *clusters_count,
	   	const int number_of_expected_clusters) {
	
	struct cluster_t *arr = *clusters;
	while (*clusters_count > number_of_expected_clusters) {
		int c1, c2;
		find_neighbours(arr, *clusters_count, &c1, &c2);
		int c1_size = arr[c1].size;
		int c2_size = arr[c2].size;
		merge_clusters(&arr[c1], &arr[c2]);
		*clusters_count = remove_cluster(arr, *clusters_count, c2);
		if (arr[c1].size < c1_size + c2_size) {
			fprintf(stderr, "Merging clusters failed.\n");	
			return;
		}
	}
}

int main(int argc, char *argv[])
{
	if (argc < 2 || argc > 3) {
		print_help();
		return 1;
	}
	int expected_clusters_count = 0;
	if (parse_arguments(argc, argv, &expected_clusters_count)) {
		return 1;
	}
    struct cluster_t *clusters = NULL;
	int clusters_count = load_clusters(argv[1], &clusters);
	if (!clusters) {
		return 1;
	}
	if (expected_clusters_count > clusters_count){
		fprintf(stderr, "File containsa fewer objects than expected number of clusters\n");
		free_clusters(clusters, clusters_count);
		return 1;
	}
	group_clusters(&clusters, &clusters_count, expected_clusters_count);
	if (clusters_count == expected_clusters_count) {
		print_clusters(clusters, clusters_count);
	}
	free_clusters(clusters, clusters_count);
}
#include <errno.h>
