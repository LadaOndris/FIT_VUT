
static // POZOR: GCC potrebuje static, aby fungovalo stejne jako C99 bez static [GCC BUG?]
inline int f1(void) { // INLINE DEFINICE funkce podle C99
     return 5;
}

// pokud ji prekladac vzdy rozvine inline, staci pouze tato definice
// pokud ne, musi byt v jednom modulu jeji externi deklarace (nebo definice)
// prekladac si muze zvolit, zda bude pouzivat inline nebo klasicke volani

// deklarace jine externi fce
int f2(void);

