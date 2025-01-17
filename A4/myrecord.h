/*
 * myrecord.h
 *
 *  Created on: Jun. 4, 2024
 *      Author: dillonquick
 */

#ifndef MYRECORD_H_
#define MYRECORD_H_

#include <stdio.h>

#define NAME_LENGTH 20

// Define structures
typedef struct {
    char name[NAME_LENGTH];
    float score;
} RECORD;

typedef struct {
    int count;
    float mean;
    float stddev;
    float median;
} STATS;

typedef struct {
    char letter_grade[3];
} GRADE;

/*
 * Define a structure named RECORD to hold a person's name of 20 characters and
 * the score of float type.
*/

/*
 * Define a structure named STATS containing fields: int count, float mean,
 * loat stddev (standard deviation), and float median.
*/

/*
 * Define a structure named GRADE to hold a string letter_grade at most 2 letters.
*/

/*
 * Convert a percentage grade to letter grade defined by percentage ranges
 * A+=[90, 100], A=[85, 90), A-=[80, 85), B+=[77, 80), B=[73, 77) B=[70, 73),
 * C+=[67, 70), C=[63, 77), C-=[60, 63), D+=[57,60),D=[53,57),D=[50,53), F=[0,50).
 *
 * @param score -  percetage grade.
 *
 * @return - letter grade wrapped in GRADE structure type.
 */
GRADE grade(float score);

/*
 *  Import record data from file and retrieves and stores all record entries
 *  in the RECORD array passed by records, and returns the number of record count.
 *
 *  @param *fp -  FILE pointer to intput file.
 *  @param dataset - array of RECODR type to store record data.
 *  @return   - number record count
 */
int import_data(FILE *fp, RECORD *dataset);


/*
 *  Take the RECORD data array as input, compute the average score, standard deviation,
 *  median of the score values of the record data, and returns the results in STATS type.
 *
 *  @param dataset -  input record data array.
 *  @param count -  the number of data record in dataset array.
 *  @return  -  stats value in STATS type.
 */
STATS process_data(RECORD *dataset, int count);

/*
 *  This function takes output file named outfilename,
 *  RECORD array by records,and output stats information,
 *   and processed record data to files in required format.
 *
 *  @param *fp -  FILE pointer to output file.
 *  @param count -  the number of data record in dataset array.
 *  @return - returns 1 if successful; 0 if count < 1
 */
int report_data(FILE *fp,  RECORD *dataset, int count);

#endif /* MYRECORD_H_ */
