#include<stdio.h>
#include<stdlib.h>

int *nastavTab(){
    int *pole = NULL;
    pole = (int*) malloc (7 * sizeof(int) + sizeof(int));
    if (pole == NULL) return 0;
    for (int i = 0; i < 7; i++){
        pole[i] = 0;
    }
    pole[7] = -1;
return pole;
}

int tabCounter(int *pole){
    int count = 0;
    int i = 0;
    int cislo;
    while (cislo != -1){
        cislo = pole[i];
        i++;
        count++;
    }
    count--;
    //printf ("%d ",count);
    return count;
}

int insCounter(int *pole){
    int ins = 0;
    int velkost;
    velkost = tabCounter(pole);
    for (int i = 0; i < velkost; i++){
        if (pole[i] != 0) ins++;
    }
    return ins;
}

int *resize(int *pole){
    int *tmp = NULL;
    int velkost;
    velkost = tabCounter(pole);
    tmp = (int*) malloc (velkost * 2 * sizeof(int) + sizeof(int));

    for (int k = 0; k < velkost*2+1; k++){
        tmp[k] = 0;
    }

    for (int i = 0; i < velkost; i++){
        tmp[i] = pole[i];
    }

    tmp[velkost * 2 + 1] = -1;
    pole = tmp;
    return pole;
}

void insert(int **pole, int data){
    int kluc;
    int velkost;
    velkost = tabCounter(*pole);

    int vlozenePrvky = insCounter(*pole);

    if (vlozenePrvky > velkost*0.75) *pole = resize(*pole);

    kluc = data % velkost;

    if ((*pole)[kluc] == 0){
        (*pole)[kluc] = data;
    }
    else {
        int flag = 0;
        int i = kluc;
        while  (i < velkost){
        if ((*pole)[i] != 0) {i++;}
        else {(*pole)[i] = data; flag = 1;break;}
        }
        if (flag == 0) {
            int j = 0;
            while  (j < velkost){
            if ((*pole)[j] != 0) {j++;}
            else {
                    (*pole)[j] = data;
                    break;
                    }
            }
        }
    }
}

int search(int *pole, int s){
    int flag = 0;
    int velkost;
    velkost = tabCounter(pole);

    int kluc = s % velkost;

    int i = kluc;
    while (i < velkost){
        if (pole[i] == s)
            {
                flag = 1;
                break;
                return s;
            }
            else i++;
    }
if (flag) {
    int j = 0;
    while (j < velkost){
        if (pole[j] == s)
            {
                break;
                return s;
            }
            else j++;
    }
}
return 0;
}


void vypisTab(int *pole){
    int velkost;
    velkost = tabCounter(pole);
    for (int i = 0; i < velkost; i++){
     printf("%d ", pole[i]);
    }
}

int main(){
    int *pole;
    pole = nastavTab();
    for (int i = 0; i < 100000; i++)
    {
    insert(&pole, 8);
    }
    //vypisTab(pole);
    //printf("\n");
    return 0;
}
