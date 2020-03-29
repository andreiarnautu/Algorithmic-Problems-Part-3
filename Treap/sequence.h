/**
  *  Worg
  */
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct sequence {
	struct sequence *left_son;
	struct sequence *right_son;

	long long priority;
	int key;
	int size;
} Sequence;

Sequence* empty_node;

void initialize_empty_node() {
	srand(time(NULL));

	empty_node = malloc(sizeof(Sequence));
	empty_node->left_son = empty_node->right_son = NULL;
	empty_node->priority = -1;
	empty_node->key = 0;
	empty_node->size = 0;
}

Sequence* init() {
	Sequence* ret = malloc(sizeof(Sequence));
	ret = empty_node;
	return ret;
}

Sequence* new_node(int value) {
	Sequence* ret = malloc(sizeof(Sequence));
	ret->left_son = ret->right_son = empty_node;
    ret->priority = ((1LL * rand() << 45) + (1LL * rand() << 30) + (1LL * rand() << 15) + (1LL * rand())) & 0x7fffffffffffffff;
	ret->key = value;
	ret->size = 1;

	return ret;
}


void update(Sequence *node) {
	if (node != empty_node) {
		node->size = node->left_son->size + node->right_son->size + 1;
	}
}

Sequence** split_Sequence(Sequence* node, int index) {
	Sequence** ret = malloc(2 * sizeof(Sequence*));

	if (node == empty_node) {
		ret[0] = ret[1] = empty_node;
	} else if (index <= node->left_son->size) {
		Sequence** p = split_Sequence(node->left_son, index);
		ret[0] = p[0]; ret[1] = node;
		ret[1]->left_son = p[1];
		update(ret[1]);
	} else {
		Sequence** p = split_Sequence(node->right_son, index - node->left_son->size - 1);
		ret[0] = node; ret[1] = p[1];
		ret[0]->right_son = p[0];
		update(ret[0]);
	}

	return ret;
}

//  Wrapper peste functia de dinainte, care returna in stanga indecsii [0..index-1] in loc de [0..index].
//  Ca sa nu inlocuim vreo 100 de chestii in cod schimband functia de mai sus, facem aici un wrapper de o linie.
Sequence** split(Sequence* node, int index) {
	return split_Sequence(node, index + 1);
}

Sequence* concat(Sequence *a, Sequence *b) {
	Sequence* ret;
	if (a == empty_node) {
		ret = b;
	} else if (b == empty_node) {
		ret = a;
	} else if (a->priority > b->priority) {
		ret = a;
		ret->right_son = concat(a->right_son, b);
		update(ret);
	} else {
		ret = b;
		ret->left_son = concat(a, b->left_son);
		update(ret);
	}

	return ret;
}

Sequence* Sequence_insert(Sequence* root, Sequence* node, int index) {
	Sequence* ret;

	if (node->priority > root->priority) {
		//printf("Ramura 1\n"); return empty_node;
		Sequence** p = split_Sequence(root, index);
		node->left_son = p[0]; node->right_son = p[1];
		ret = node;
	} else if (index <= root->left_son->size) {
		//printf("Ramura 2\n"); return empty_node;
		ret = root;
		ret->left_son = Sequence_insert(ret->left_son, node, index);
	} else {
		//printf("Ramura 3\n"); return empty_node;
		ret = root;
		ret->right_son = Sequence_insert(ret->right_son, node, index - root->left_son->size - 1);
	}

	update(ret);
	return ret;
}

//  Un wrapper peste functia reala de insert. Ne facem viata mai usoara.
Sequence *insert(Sequence* root, int value, int where) {
//	printf("%lld\n", new_node(value)->priority);
//	return root;
	return Sequence_insert(root, new_node(value), where);
}

//  Pentru debugging
void write_Sequence(Sequence* node) {
	if (node != empty_node) {
		write_Sequence(node->left_son);
		printf("%d; ", node->key);
		write_Sequence(node->right_son);
	}
}

Sequence* delete(Sequence* root, int index) {
	Sequence* ret = empty_node;

	if (root != empty_node) {
		if (root->left_son->size == index) { //  E ok asa, avem indexare de la 0
			ret = concat(root->left_son, root->right_son);
			free(root);
		} else {
			if (index < root->left_son->size) {
				root->left_son = delete(root->left_son, index);
			} else {
				root->right_son = delete(root->right_son, index - root->left_son->size - 1);
			}
			ret = root;
		}
	}
	update(ret);
	return ret;
}

int lookup(Sequence* root, int index) {
	if (index < root->left_son->size) {
		return lookup(root->left_son, index);
	} else if (index == root->left_son->size) {
		return root->key;
	} else {
		return lookup(root->right_son, index - root->left_son->size - 1);
	}
}

int size(Sequence* root) {
	return root->size;
}

Sequence* set(Sequence* root, int item, int index) {
	if (index < root->left_son->size) {
		set(root->left_son, item, index);
	} else if (index == root->left_son->size) {
		root->key = item;
	} else {
		set(root->right_son, item, index - root->left_son->size - 1);
	}

	return root;
}
