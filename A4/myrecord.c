/*
 * myrecord.c
 *
 *  Created on: Jun. 4, 2024
 *      Author: dillonquick
 */

#include <stdio.h>
#include <math.h>
#include <string.h>
#include "myrecord.h"
#include "mysort.h"

GRADE grade(float score) {
    GRADE g;
    if (score >= 90) {
        strcpy(g.letter_grade, "A+");
    } else if (score >= 85) {
        strcpy(g.letter_grade, "A");
    } else if (score >= 80) {
        strcpy(g.letter_grade, "A-");
    } else if (score >= 77) {
        strcpy(g.letter_grade, "B+");
    } else if (score >= 73) {
        strcpy(g.letter_grade, "B");
    } else if (score >= 70) {
        strcpy(g.letter_grade, "B-");
    } else if (score >= 67) {
        strcpy(g.letter_grade, "C+");
    } else if (score >= 63) {
        strcpy(g.letter_grade, "C");
    } else if (score >= 60) {
        strcpy(g.letter_grade, "C-");
    } else if (score >= 57) {
        strcpy(g.letter_grade, "D+");
    } else if (score >= 53) {
        strcpy(g.letter_grade, "D");
    } else if (score >= 50) {
        strcpy(g.letter_grade, "D-");
    } else {
        strcpy(g.letter_grade, "F");
    }
    return g;
}

int import_data(FILE *fp, RECORD *dataset) {
	if (!fp){
		return 0;
	}
	int count = 0;
	char line[100];
	while (fgets(line, sizeof(line),fp)) {
		char name[50];
		float score;
		sscanf(line, "%[^,],%f", name, &score);
		strcpy(dataset[count].name, name);
		dataset[count].score = score;
		count++;
	}
		return count;


}

STATS process_data(RECORD *dataset, int count) {
    STATS stats;
    float total_score = 0;

    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (dataset[j].score > dataset[j + 1].score) {
                RECORD temp = dataset[j];
                dataset[j] = dataset[j + 1];
                dataset[j + 1] = temp;
            }
        }
    }

    for (int i = 0; i < count; i++) {
        total_score += dataset[i].score;
    }
    stats.mean = total_score / count;

    float sum_of_squares = 0;
    for (int i = 0; i < count; i++) {
        sum_of_squares += (dataset[i].score - stats.mean) * (dataset[i].score - stats.mean);
    }
    stats.stddev = sqrt(sum_of_squares / count);

    if (count % 2 == 0) {
        stats.median = (dataset[count / 2 - 1].score + dataset[count / 2].score) / 2.0;
    } else {
        stats.median = dataset[count / 2].score;
    }
	stats.count = count;

    return stats;
}

int report_data(FILE *fp, RECORD *dataset, int n) {
    if (n < 1) return 0;

    STATS stats = process_data(dataset, n);

    fprintf(fp, "Count: %d\n", stats.count);
    fprintf(fp, "Mean: %.2f\n", stats.mean);
    fprintf(fp, "Standard Deviation: %.2f\n", stats.stddev);
    fprintf(fp, "Median: %.2f\n", stats.median);

    for (int i = 0; i < n; i++) {
        GRADE g = grade(dataset[i].score);
        fprintf(fp, "%s,%.1f,%s\n", dataset[i].name, dataset[i].score, g.letter_grade);
    }

    return 1;
}
