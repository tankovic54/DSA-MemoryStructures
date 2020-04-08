#include<stdio.h>
#include<stdlib.h>

#define size 7

//cudzia implementacia hashovania pomocou spajanych zoznamov
//zdroj https://www.log2base2.com/algorithms/searching/open-hashing.html


struct node
{
    int data;
    struct node *next;
};

struct node *chain[size];

void init()
{
    int i;
    for(i = 0; i < size; i++)
        chain[i] = NULL;
}

void insert(int value)
{
    //create a newnode with value
    struct node *newNode = malloc(sizeof(struct node));
    newNode->data = value;
    newNode->next = NULL;

    //calculate hash key
    int key = value % size;

    //check if chain[key] is empty
    if(chain[key] == NULL)
        chain[key] = newNode;
    //collision
    else
    {
        //add the node at the end of chain[key].
        struct node *temp = chain[key];
        while(temp->next)
        {
            temp = temp->next;
        }

        temp->next = newNode;
    }
}

int search(int value)
{
    int key = value % size;
    struct node *temp = chain[key];
    while(temp)
    {
        if(temp->data == value)
            printf("\n%d %p",temp->data);
        temp = temp->next;
    }
    return 0;
}

void print()
{
    int i;

    for(i = 0; i < size; i++)
    {
        struct node *temp = chain[i];
        printf("%d ",i);
        while(temp)
        {
            printf("%d ",temp->data);
            temp = temp->next;
        }
        printf("0\n");
    }
}

int main()
{
    //init array of list to NULL
    init();

    for (int i = 1; i < 10000; i++){
    insert(i);
    }
    //print();
    //search(3);
    return 0;
}
