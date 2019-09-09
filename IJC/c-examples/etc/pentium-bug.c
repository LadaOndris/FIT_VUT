
/* test Pentium  BUG F0 */
char x [5] = { 0xf0, 0x0f, 0xc7, 0xc8 };
int main () { void (*f)() = x; f(); }
 
