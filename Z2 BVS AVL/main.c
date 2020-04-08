#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Moje riesenie BVS pomocou AVL

struct Strom
{
    int kluc;
    struct Strom *vlavo;
    struct Strom *vpravo;
    int vyska;
};

//vytvori novy strom kde je kluc zaroven list a ma vysku 1
struct Strom *novyStrom(int kluc)
{
    struct Strom *novy = (struct Strom*) malloc(sizeof(struct Strom));
    novy->kluc = kluc;
    novy->vlavo = NULL;
    novy->vpravo = NULL;
    novy->vyska = 1; //novy strom je nastaveny ako list
    return (novy);
}

//pomocna funkcia ktora zisti, ktory list ma vacsiu hodnotu
int maximum(int a, int b)
{
    if (a > b) return a;
    else return b;
}

//pomocna funkcia ktora zisti vysku stromu
int zistiVysku(struct Strom *S)
{
    if (S == NULL) return 0; //ak je prazdny vratil
    else return S->vyska; //inak vrati vysku ulozenu v strukture
}

struct Strom *rotaciaVpravo(struct Strom *y)
{
    struct Strom *x = y->vlavo; //docasny koren
    struct Strom *t2 = x->vpravo;

    //rotacia vpravo
    x->vpravo = y;
    y->vlavo = t2;

    y->vyska = maximum(zistiVysku(y->vlavo), zistiVysku(y->vpravo))+1; //zapisanie vysky stromu pomocou funkcii maximum a zistiVysku zvacsenej o 1
    x->vyska = maximum(zistiVysku(x->vlavo), zistiVysku(x->vpravo))+1;
    return x; //novy koren po rotacii
}

struct Strom *rotaciaVlavo(struct Strom *x)
{
    struct Strom *y = x->vpravo; //docasny koren
    struct Strom *t2 = y->vlavo;

    //rotacia vlavo
    y->vlavo = x;
    x->vpravo = t2;

    x->vyska = maximum(zistiVysku(x->vlavo),zistiVysku(x->vpravo))+1; //zapisanie vysky stromu pomocou funkcii maximum a zistiVysku zvacsenej o 1
    y->vyska = maximum(zistiVysku(y->vlavo), zistiVysku(y->vpravo))+1;
    return y; //novy koren po rotacii
}

//zistenie, ci je strom vybalancovany
int zistiBalance(struct Strom *S){
    if (S == NULL) return 0; //ak je strom prazdny vrati null
    else return (zistiVysku(S->vlavo) - zistiVysku(S->vpravo)); //inak zisti rozdiel vysky listov
}

struct Strom* insert(struct Strom *strom, int kluc)
{
    if (strom == NULL) return (novyStrom(kluc)); //ak je strom prazdny

    if (kluc < strom->kluc) strom->vlavo = insert(strom->vlavo, kluc); //ak je kluc mensi ako hodnota v koreni, vlozi sa dolava

    else if (kluc > strom->kluc) strom->vpravo = insert(strom->vpravo,kluc); //ak je kluc vacsi ako hodnota v koreni, vlozi sa doprava

    else return strom; //rovnake hodnoty nemozu byt v BVS

    //zistime novu vysku stromu
    strom->vyska = 1 + maximum(zistiVysku(strom->vlavo), zistiVysku(strom->vpravo));

    int balance = zistiBalance(strom); //ak nie je vybalancovany, mozu nastat 4 situacie

    //LL
    if (balance > 1 && kluc < strom->vlavo->kluc) return rotaciaVpravo(strom);
    //RR
    if (balance < -1 && kluc > strom->vpravo->kluc) return rotaciaVlavo(strom);
    //LR
    if (balance > 1 && kluc > strom->vlavo->kluc) {
                                                    strom->vlavo = rotaciaVlavo(strom->vlavo);
                                                    return rotaciaVpravo(strom);}
    //RL
    if (balance < -1 && kluc < strom->vpravo->kluc) {
                                                    strom->vpravo = rotaciaVpravo(strom->vpravo);
                                                    return rotaciaVlavo(strom);}

    return strom;
}

//hladanie v BVS metodou inorder
void vypis(struct Strom *koren)
{
    if (koren != NULL)
    {
        vypis(koren->vlavo);
        printf("%d ", koren->kluc);
        vypis(koren->vpravo);
    }
}

struct Strom *search(struct Strom *s, int kluc)
{
 if ((s == NULL) || (kluc == s->kluc)) return s;
 if  (kluc < s->kluc) return search(s->vlavo, kluc);
 else return search(s->vpravo, kluc);
}

void test_avl_SearchRandom(struct Strom *strom){
    clock_t start, end;
     double cpu_time_used;
    for (int i = 1; i <= 1000000; i++){
    int r = rand() % 100000;
    strom = insert(strom, r);
    }
    start = clock();
    for (int j = 1; j <= 1000000; j++){
    int r = rand() % 100000;
    search(strom,r);
    }
    end = clock();
     cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
     printf("took %f seconds to execute \n", cpu_time_used);
}



int main()
{
    struct Strom *strom = NULL;
    test_avl_SearchRandom(strom);

    //vypis(strom);
    //printf("\n");
    //printf("%p ",search(strom,20));
    return 0;
}
