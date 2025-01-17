/*--------------------------------------------------
 File:    dllist_ptest.c
 About:   public test driver
 Author:  HBF
 Version: 2024-05-30
 --------------------------------------------------
 */

#include <stdio.h>
#include <stdlib.h>
#include "dllist.h"

char tests[] = { 'A', 'B', 'C', 'D' };

void display_forward(DLL *dllp) {
	NODE *np = dllp->start;
	printf("length %d forward ", dllp->length);
	while (np != NULL) {
		printf("%c ", np->data);
		np = np->next;
	}
}

void display_backward(DLL *dllp) {
	NODE *np = dllp->end;
	printf("length %d backward ", dllp->length);
	while (np != NULL) {
		printf("%c ", np->data);
		np = np->prev;
	}
}

void test_new_node() {
	printf("------------------\n");
	printf("Test: new_node\n\n");
	int n = sizeof tests / sizeof *tests;
	NODE *np = NULL;
	for (int i = 0; i < n; i++) {
		np = new_node(tests[i]);
		printf("new_node(%c): %c\n", tests[i], np->data);
		free(np);
	}
	printf("\n");
}

void test_dll_insert_start() {
	printf("------------------\n");
	printf("Test: dll_insert_start\n\n");

	int n = sizeof tests / sizeof *tests;
	DLL dllist = { 0 };
	printf("given dll: ");
	display_forward(&dllist);
	printf("\n");
	for (int i = 0; i < n; i++) {
		dll_insert_start(&dllist, new_node(tests[i]));
		printf("dll_insert_start(%c): ", tests[i]);
		display_forward(&dllist);
		printf("\n");
	}
	dll_clean(&dllist);
	printf("\n");
}

void test_dll_insert_end() {
	printf("------------------\n");
	printf("Test: dll_insert_end\n\n");
	int n = sizeof tests / sizeof *tests;
	DLL dllist = { 0 };
	printf("given dll: ");
	display_forward(&dllist);
	printf("\n");
	for (int i = 0; i < n; i++) {
		dll_insert_end(&dllist, new_node(tests[i]));
		printf("dll_insert_end(%c): ", tests[i]);
		display_forward(&dllist);
		printf("\n");
	}
	printf("resulted dll: ");
	display_backward(&dllist);
	printf("\n");
	dll_clean(&dllist);

	printf("\n");
}

void test_dll_delete_start() {
	printf("------------------\n");
	printf("Test: dll_delete_start\n\n");

	int n = sizeof tests / sizeof *tests;
	DLL dllist = { 0 };
	for (int i = 0; i < n; i++) {
		dll_insert_start(&dllist, new_node(tests[i]));
	}
	printf("given dll: ");
	display_forward(&dllist);
	printf("\n");
	for (int i = 0; i < n; i++) {
		printf("dll_delete_start(%c): ", tests[i]);
		dll_delete_start(&dllist);
		display_forward(&dllist);
		printf("\n");
	}
	dll_clean(&dllist);
	printf("\n");
}

void test_dll_delete_end() {
	printf("------------------\n");
	printf("Test: dll_delete_end\n\n");

	int n = sizeof tests / sizeof *tests;
	DLL dllist = { 0 };
	for (int i = 0; i < n; i++) {
		dll_insert_start(&dllist, new_node(tests[i]));
	}
	printf("given dll: ");
	display_forward(&dllist);
	printf("\n");
	for (int i = 0; i < n; i++) {
		printf("dll_delete_end(%c): ", tests[i]);
		dll_delete_end(&dllist);
		display_forward(&dllist);
		printf("\n");
	}
	dll_clean(&dllist);
	printf("\n");
}

int main(int argc, char* args[]) {
	test_new_node();
	test_dll_insert_start();
	test_dll_insert_end();
	test_dll_delete_start();
	test_dll_delete_end();
	return 0;
}