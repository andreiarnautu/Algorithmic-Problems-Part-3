/**
  *  Worg
  */
#include <stdio.h>
#include "sequence.h"

int main() {
	//  Astea doua linii sunt necesare pentru Sequence in sine.
	initialize_empty_node();
	Sequence* global_root = init();

	//  Inseram valorile de la 0 la 9 in ordine, apoi afisam Sequenceul.
	for (int i = 0; i < 10; i++) {
		global_root = insert(global_root, i, i);
	}
	write_Sequence(global_root);
	printf("\n");

	//  Stergem valoarea de la indexul 5, apoi afisam Sequenceul. Da ok.
	global_root = delete(global_root, 5);
	write_Sequence(global_root);
	printf("\n");

	//  Inseram elementul inapoi si afisam Sequenceul. Da ok.
	global_root = insert(global_root, 5, 5);
	write_Sequence(global_root);
	printf("\n");

	printf("Setare de element:\n");
	global_root = set(global_root, 10, 5);
	write_Sequence(global_root); printf("\n");
	global_root = set(global_root, 5, 5);
	write_Sequence(global_root); printf("\n");


	//  Facem query pe pozitia 6
	printf("%d\n", lookup(global_root, 6));

	//  Afisam dimensiunea structurii
	printf("%d\n", size(global_root));

	//  Splituim un Sequence si afisam apoi ce e in stanga si ce e in dreapta
	printf("Rezultatul splitului:\n");
	Sequence** split_result = split(global_root, 6);
	write_Sequence(split_result[0]); printf("\n");
	write_Sequence(split_result[1]); printf("\n");

	//  Dam concat la Sequenceuri (functia de concat)
	printf("Dupa ce reunim cele doua bucati:\n");
	global_root = concat(split_result[0], split_result[1]);
	write_Sequence(global_root); printf("\n");
	return 0;
}
