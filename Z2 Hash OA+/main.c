#include<stdio.h>
#include<stdlib.h>

int *nastavTab(){
    int *pole = NULL;
    pole = (int*) malloc (7 * sizeof(int) + sizeof(int) + sizeof(int) + sizeof(int));
    if (pole == NULL) return 0;
    for (int i = 0; i < 9; i++){
        pole[i] = 0;
    }
    pole[0] = 7;
    pole[1] = 7;
    pole[9] = -1;
return pole;
}

int tabCounter(int *pole){
    int count = pole[0];
    return count;
}

int *resize(int *pole){
    int *tmp = NULL;
    int velkost;
    velkost = tabCounter(pole);
    tmp = (int*) malloc (velkost * 2 * sizeof(int) + sizeof(int) + sizeof(int) + sizeof(int));

    for (int k = 0; k < velkost * 2 + 2; k++){
        tmp[k] = 0;
    }

    for (int i = 0; i < velkost; i++){
        tmp[i] = pole[i];
    }

    tmp[0] = velkost * 2;
    tmp[1] += velkost;
    tmp[velkost * 2 + 2] = -1;
    pole = tmp;
    return pole;
}

void insert(int **pole, int data){
    int kluc;
    int velkost;
    velkost = tabCounter(*pole);

    int vlozenePrvky = (*pole)[1];
    (*pole)[1] = vlozenePrvky - 1;

    int ratio;
    ratio = velkost*0.3;
    ratio++;

    if (vlozenePrvky < ratio) *pole = resize(*pole);

    kluc = data % velkost;

    int flag = 0;
    if ((kluc == 0) || (kluc == 1)) kluc = kluc + 2;
    int i = kluc;
    while  (i < velkost){
    if ((*pole)[i] != 0) {i++;}
    else {(*pole)[i] = data; flag = 1;break;}
        }
        if (flag == 0) {
            int j = 2;
            while  (j < velkost){
            if ((*pole)[j] != 0) {j++;}
            else {
                    (*pole)[j] = data;
                    break;
                    }
            }
        }
}

int search(int *pole, int s){
    int flag = 0;
    int velkost;
    velkost = tabCounter(pole);

    int kluc = s % velkost;
    if ((kluc == 0) || (kluc == 1)) kluc = kluc + 2;

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
    int j = 2;
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
    for (int i = 2; i < velkost; i++){
     printf("%d ", pole[i]);
    }
}

int main(){
    int *pole;
    pole = nastavTab();
    for (int i = 1; i <= 100000; i++)
    {
    insert(&pole, 8);
    }
    //vypisTab(pole);
    return 0;
}
