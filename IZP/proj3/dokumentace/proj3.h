
/** 
 *	@mainpage
 *	@brief Projekt 3 - Jednoducha shlukova analyza.
 *
 *  @par Vice podrobnosti zde:
 *	@link
 *		proj3.h
 *	@endlink
 */

/**
 *	@file proj3.h
 *	@brief Projekt 3 - Jednoducha shlukova analyza.
 *  Soubor obsahuje veskere funkce potrebne k provedeni shlukove analyzy.
 *  
 *  Jednoducha shlukova analyza, metodou nejblizsiho souseda (single linkage).
 *  Shlukova analyza se provadi na dvourozmernych objektech. Tyto objekty jsou 
 *  nacitany ze souboru a kazdy objekt je identifikovan celym cislem.
 *  Pro vizualizaci vysledku shlukove analyzy se da pouzit tento nastroj:
 *  http://www.fit.vutbr.cz/study/courses/IZP/public/cluster.php
 *
 *  Metoda nejblizsiho souseda vybira ke spojeni vzdy dva shluky, ktere maji 
 *  k sobe nejblize. Vzdalenost dvou shluku je rovna nejmensi vzdalenosti dvou 
 *  objektu z obou shluku.
 *
 *	@author Ladislav Ondris xondri07@stud.fit.vutbr.cz
 *	@date 9.12.2018
 *
 *  @see https://en.wikipedia.org/wiki/Cluster_analysis
 * */

/**
 *	@struct obj_t
 *	@brief Struktura reprezentujici jeden bod.
 *	@var obj_t::id
 *	Jedinecny identifikator.
 *	@var obj_t::x
 *	Souradnice x objektu.
 *	@var obj_t::y
 *	Souradnice y objektu. 	
 */
 struct obj_t {
	 int id;
	 float x;
	 float y;
 };

/**
 *	@struct cluster_t
 *	@brief Struktura reprezentující jeden shluk obsahujici mnozinu objektu.
 *	@var cluster_t::size
 *	Zaplnena velikost pole obj - pocet objektu ve shluku.
 *	@var cluster_t::capacity
 *	Velikost pole obj - maximalni pocet objektu, ktere lze do pole ulozit.
 *	@var cluster_t::obj
 *	Pole objektu nachazejicich se ve shluku.
 */
struct cluster_t {
	int size;
	int capacity;
	struct obj_t *obj;
};

/**
 * @defgroup cluster_basic Zakladni operace se shlukem
 * @{
 */

/**
 *
 *  @brief Inicializuje shluk.
 *
 *  Inicializace shluku 'c'. Alokuje pamet pro cap objektu (kapacitu).
 *  Ukazatel NULL u pole objektu znamena kapacitu 0.
 *	
 *	@param c Shluk, ktery bude inicializovan.
 *	@param cap Kapacita, na kterou shluk bude inicializovan.
 *
 *  @pre c != NULL
 *  @pre cap >= 0
 *	@post size = 0
 *	@post capacity >= 0
 */
void init_cluster(struct cluster_t *c, int cap);

/**
 *  @brief Vycisteni shluku.
 *
 *	Odstraneni vsech objektu shluku a inicializace na prazdny shluk.
 *	
 *	@param c Shluk, ktery bude vycisten.
 *  
 *  @pre c != NULL
 *	@post Velikost i kapacita shluku bude rovna 0, pole objektu bude dealokovano.
 */
void clear_cluster(struct cluster_t *c);

/**
 *	Udava po jak velkych castech se realokuje pole objektu ve shluku, 
 *	pokud je nedostatecna kapacita.
 */
extern const int CLUSTER_CHUNK;

/**
 * 	@brief Zmena kapacity shluku 'c' na kapacitu 'new_cap'.
 *
 *  @param c Shluk, jehoz kapacita bude zvetsena.	
 *	@param new_cap Nova kapacita, na kterou bude shluk inicializovan.
 *
 *	@pre c != NULL
 *	@pre kapacita shluku >= 0
 *	@pre new_cap >= 0
 *	@post kapacita shluku == new_cap
 *
 *	@return Vraci NULL, pokud se alokace nepovedla, 
 *	jinak vraci ukazatel na realokovany shluk.
 */
struct cluster_t *resize_cluster(struct cluster_t *c, int new_cap);

/**
 * @brief Prida objekt do shluku.
 *
 * Prida objekt 'obj' na konec shluku 'c'. Rozsiri shluk, pokud se do nej objekt nevejde.
 * 
 * @param c Shluk, do ktereho se bude pridavat objekt.
 * @param obj Objekt, ktery bude pridavan do shluku.
 *
 * @pre c != NULL
 * @pre obj != NULL
 * @post Objekt 'obj' bude pridan na konec shluku 'c'.
 */
void append_cluster(struct cluster_t *c, struct obj_t obj);

/**
 * @}
 */

/**
 * @defgroup objects_operations Operace nad objekty
 * @{
 */
/**
 * @brief Pocita euklidovskou vzdalenost mezi dvema objekty.
 *
 * @param o1 Prvni objekt.
 * @param o2 Druhy objekt.
 *
 * @pre o1 != NULL
 * @pre o2 != NULL
 * @post Vysledek je vzdy vetsi nebo rovno 0.
 * @return Vraci vzdalenost mezi objekty.
 */
float obj_distance(struct obj_t *o1, struct obj_t *o2);


/**
 * @}
 */

/**
 *	@defgroup clusters Operace nad vice shluky
 *	@{
 */

/**
 * @brief Spoji dva shluky v jeden. 
 *
 * Do shluku 'c1' prida objekty 'c2'. Shluk 'c1' bude v pripade potreby rozsiren.
 * Objekty ve shluku 'c1' budou serazeny vzestupne podle identifikacniho cisla.
 * Pokud se pridani objektu do shluku 'c1' nepodari, velikost shluku 'c1' bude
 * po vykonani mensi nez soucet velikosti shluku 'c1' a 'c2' pred vykonanim.
 *
 * @param c1 Shluk, do ktereho se budou pridavat shluky z toho druheho shluku.
 * @param c2 Shluk, z ktereho se budou prekopirovavat objekty do prvniho shluku.
 *
 * @pre 'c1' != NULL
 * @pre 'c2' != NULL
 * @post Shluk 'c2' zustane nezmenen.
 * @post Shluk 'c1' bude obsahovat objekty obou shluku.
 */
void merge_clusters(struct cluster_t *c1, struct cluster_t *c2);

/**
 * @brief Odstrani shluk z pole shluku 'carr'. 
 *
 * @param carr Ukazetel na prvni polozku pole shluku o velikosti 'narr'.
 * @param narr Pocet polozek (shluku), kolik se nachazi v poli 'carr'.
 * @param idx Index prvku (shluku), ktery ma byt odstranen.
 *
 * @pre idx < narr
 * @pre narr > 0
 * @pre carr != NULL
 * @post Velikost pole 'carr' je o jedno mensi.
 * @return Vraci novy pocet shluku v poli.
 */
int remove_cluster(struct cluster_t *carr, int narr, int idx);

/**
 * @brief Vypocet vzdalenosti dvou shluku.
 *
 * Pocita vzdalenost mezi dvema shluky. Vysledna vzdalenost je 
 * rovna vzdalenosti dvou nejblizsich objektu z obou shluku.
 *
 * @param c1 Prvni shluk.
 * @param c2 Druhy shluk.
 *
 * @pre c1 != NULL
 * @pre c2 != NULL
 * @post Vysledek bude vzdy vetsi nebo rovno 0.
 * @return Vraci vzdalenost mezi objekty.
 */
float cluster_distance(struct cluster_t *c1, struct cluster_t *c2);

/**
 * @brief Nalezeni nejblizsich dvou shluku.
 *
 * Funkce najde dva nejblizsi shluky mezi vsemi shluky a jejich
 * indexy uklada do pameti na adresu 'c1' a 'c2'.
 *
 * @param carr Pole shluku, mezi kterymi se budou hledat dva nejblizsi.
 * @param narr Velikost pole 'carr'.
 * @param c1 Index prvniho z nejblizsich dvou shluku.
 * @param c2 Index druheho z nejblizsich dvou shluku.
 * 
 * @pre carr != NULL
 * @pre narr > 0
 * @post c1 >= 0
 * @post c2 >= 0
 */
void find_neighbours(struct cluster_t *carr, int narr, int *c1, int *c2);

/**
 * @brief Razeni objektu ve shluku vzestupne podle jejich identifikatoru.
 *
 * @param c Shluk, ktery bude serazen.
 *
 * @pre c != NULL
 * @post Objekty ve shluku 'c' budou serazeny podle identifikatoru.
 */
void sort_cluster(struct cluster_t *c);

/** 
 *  @brief Tisk shluku 'c' na stdout.
 *
 *  @pre c != NULL
 *  @post Shluk bude vytisten na stdout.
 *  @post Shluk zustane nezmenen.
 */
void print_cluster(struct cluster_t *c);
/**
 * @brief Tiskne pole shluku na stdout. 
 *
 * @param carr Ukazatel na prvni polozku (shluk).
 * @param narr Pocet shluku k tisknuti.
 * 
 * @pre narr >= 0
 * @pre carr != NULL
 * @post Pole shluku bude vytisteno.
 */
void print_clusters(struct cluster_t *carr, int narr);

/**
 * @}
 */

/**
 * @defgroup vstupy Operace pro zpracovani vstupu
 * @{
 */

/**
 * @brief Nacte shluky ze souboru.
 *
 * Ze souboru 'filename' nacte objekty. Pro kazdy objekt vytvori shluk a ulozi
 * jej do pole shluku. Alokuje prostor pro pole vsech shluku a ukazatel na prvni
 * polozku pole (ukazatel na prvni shluk v alokovanem poli) ulozi do pameti,
 * kam se odkazuje prametr 'arr'.
 *
 * @param filename Soubor, ze ktereho se budou objekty/shluky nacitat.
 * @param arr Ukazatel na pole shluku, kde se ulozi nactene pole shluku.
 *
 * @pre arr != NULL
 * @pre Soubor s nazvem 'filename' existuje, 
 * pricemz data uvnitr jsou ve spravnem formatu.
 * @post Ukazatel 'arr' bude ukazovat na zacatek alokovaneho a inicializovaneho 
 * pole shluku.
 * @return Vraci pocet nactenych objektu (shluku). V pripade chyby uklada 
 * do pameti, kam se odkazuje 'arr', hodnotu NULL.
 */
int load_clusters(char *filename, struct cluster_t **arr);

/**
 * @}
 */
