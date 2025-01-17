/*
 -------------------------------------------------------
 File:     myrecord_bst_ptest.c
 About:    public test driver
 Author:   HBF
 Version:  2024-01-30
 -------------------------------------------------------
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "bst.h"
#include "myrecord_bst.h"

typedef struct {
	int count;
	float mean;
	float stddev;
	float median;
} STATS;

void display_bst_stats(BSTDS *root);
void test_import_data();

RECORD tests[] = { { "A04", 40 }, { "A01", 10 }, { "A02", 20 }, { "A03", 30 }, {
		"A08", 80 }, { "A05", 50 }, { "A06", 60 }, { "A07", 70 }, { "A09", 90 },
		{ "A10", 100 } };

char *search_keys[] = { "A02", "A04", "B2", "A08" };
char *delete_keys[] = { "A01", "A03", "A05", "A10" };

BSTDS bstds = { 0 };

void display_bst_stats(BSTDS *root) {
	printf("%s %d ", "count", root->count);
	printf("%s %.1f ", "mean", root->mean);
	printf("%s %.1f", "stddev", root->stddev);
}

void test_add_record() {
	printf("------------------\n");
	printf("Test: add_record\n\n");
	int n = sizeof(tests) / sizeof(RECORD);
	for (int i = 0; i < n; i++) {
		printf("%s(%s %.1f): ", "add_record", tests[i].name, tests[i].score);
		add_record(&bstds, tests[i]);
		display_bst_stats(&bstds);
		printf("\n");
	}
	printf("\n");
}

void test_remove_record() {
	printf("------------------\n");
	printf("Test: remove_record\n\n");
	int n = sizeof tests / sizeof *tests;
	for (int i = n - 1; i >= 0; i--) {
		printf("%s(%s): ", "remove_record", tests[i].name);
		remove_record(&bstds, tests[i].name);
		display_bst_stats(&bstds);
		printf("\n");
	}

	printf("\n");
}

int main(int argc, char* args[]) {
	if (argc <= 1) {
		test_add_record();
		test_remove_record();
		bstds_clean(&bstds);
	} else {
		test_import_data();
	}
	return 0;
}

int import_data(FILE *fp, BSTDS *bst) {
	char line[40];
	RECORD record = { 0 };
	while (fgets(line, sizeof(line), fp) != NULL) {
		if (sscanf(line, "%[^,],%f", record.name, &record.score) >= 2)
			add_record(bst, record);
	}
	return bst->count;
}

void test_import_data() {
	printf("------------------\n");
	printf("Test: import_data\n\n");
	
	BSTDS bst = { 0 };
	FILE *fp = fopen("marks.txt", "r");
	int n = import_data(fp, &bst);
	fclose(fp);
	printf("%s(): %d\n", "import_data", n);

	
	printf("%s(): ", "process_data");
	display_bst_stats(&bst);
	printf("\n");
	bstds_clean(&bst);
	printf("\n");
}

