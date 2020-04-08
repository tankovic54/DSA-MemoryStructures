#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define RED 0
#define BLACK 1

//cuzdia implementacia Cerveno-cierneho stromu
//zdroj https://gist.github.com/aagontuk/38b4070911391dd2806f
//modifikovany main v sulade s mojim riesenim
//autor Ashfaqur Rahman
//posledna uprava 13.10.2015


struct node{
	int key;
	int color;
	struct node *parent;
	struct node *left;
	struct node *right;
};

struct node *ROOT;
struct node *NILL;

void left_rotate(struct node *x);
void right_rotate(struct node *x);
void tree_print(struct node *x);
void red_black_insert(int key);
void red_black_insert_fixup(struct node *z);
struct node *tree_search(int key);
void red_black_transplant(struct node *u, struct node *v);
void red_black_delete(struct node *z);
void red_black_delete_fixup(struct node *x);

int main(){
	NILL = malloc(sizeof(struct node));
	NILL->color = BLACK;

	ROOT = NILL;

    test_rb_insSearchRand1000000();

	//printf((tree_search(20) == NILL) ? "NILL\n" : "%p\n", tree_search(20));

	return 0;
}

void test_rb_insSearchRand(){
    clock_t start, end;
     double cpu_time_used;
    for (int i = 1; i <= 1000000; i++){
            int r = rand() % 100000;
            red_black_insert(r);
    }
    start = clock();
    for (int j = 1; j <= 1000000; j++){
        int r = rand() % 100000;
        tree_search(r);
    }
    end = clock();
     cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
     printf("took %f seconds to execute \n", cpu_time_used);
}


void tree_print(struct node *x){
	if(x != NILL){
		tree_print(x->left);
		printf("%d ", x->key);
		tree_print(x->right);
	}
}

struct node *tree_search(int key){
	struct node *x;

	x = ROOT;
	while(x != NILL && x->key != key){
		if(key < x->key){
			x = x->left;
		}
		else{
			x = x->right;
		}
	}

	return x;
}


void red_black_insert(int key){
	struct node *z, *x, *y;
	z = malloc(sizeof(struct node));

	z->key = key;
	z->color = RED;
	z->left = NILL;
	z->right = NILL;

	x = ROOT;
	y = NILL;

	while(x != NILL){
		y = x;
		if(z->key <= x->key){
			x = x->left;
		}
		else{
			x = x->right;
		}
	}

	if(y == NILL){
		ROOT = z;
	}
	else if(z->key <= y->key){
		y->left = z;
	}
	else{
		y->right = z;
	}

	z->parent = y;

	red_black_insert_fixup(z);
}

void red_black_insert_fixup(struct node *z){
	while(z->parent->color == RED){

		/* z's parent is left child of z's grand parent*/
		if(z->parent == z->parent->parent->left){

			/* z's grand parent's right child is RED */
			if(z->parent->parent->right->color == RED){
				z->parent->color = BLACK;
				z->parent->parent->right->color = BLACK;
				z->parent->parent->color = RED;
				z = z->parent->parent;
			}

			/* z's grand parent's right child is not RED */
			else{

				/* z is z's parent's right child */
				if(z == z->parent->right){
					z = z->parent;
					left_rotate(z);
				}

				z->parent->color = BLACK;
				z->parent->parent->color = RED;
				right_rotate(z->parent->parent);
			}
		}

		/* z's parent is z's grand parent's right child */
		else{

			/* z's left uncle or z's grand parent's left child is also RED */
			if(z->parent->parent->left->color == RED){
				z->parent->color = BLACK;
				z->parent->parent->left->color = BLACK;
				z->parent->parent->color = RED;
				z = z->parent->parent;
			}

			/* z's left uncle is not RED */
			else{
				/* z is z's parents left child */
				if(z == z->parent->left){
					z = z->parent;
					right_rotate(z);
				}

				z->parent->color = BLACK;
				z->parent->parent->color = RED;
				left_rotate(z->parent->parent);
			}
		}
	}

	ROOT->color = BLACK;
}

void left_rotate(struct node *x){
	struct node *y;

	y = x->right;
	x->right = y->left;
	if(y->left != NILL){
		y->left->parent = x;
	}

	y->parent = x->parent;
	if(y->parent == NILL){
		ROOT = y;
	}
	else if(x == x->parent->left){
		x->parent->left = y;
	}
	else{
		x->parent->right = y;
	}

	y->left = x;
	x->parent = y;
}

void right_rotate(struct node *x){
	struct node *y;

	y = x->left;
	x->left = y->right;
	if(y->right != NILL){
		y->right->parent = x;
	}

	y->parent = x->parent;
	if(y->parent == NILL){
		ROOT = y;
	}
	else if(x == x->parent->left){
		x->parent->left = y;
	}
	else{
		x->parent->right = y;
	}

	y->right = x;
	x->parent = y;
}

void red_black_transplant(struct node *u, struct node *v){
	if(u->parent == NILL){
		ROOT = v;
	}
	else if(u == u->parent->left){
		u->parent->left = v;
	}
	else{
		u->parent->right = v;
	}

	v->parent = u->parent;
}

