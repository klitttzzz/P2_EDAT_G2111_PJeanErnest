#include <stdio.h>
#include <stdlib.h>
#include "list.h"
#include "file_utils.h"

int read_float(FILE *file, float *grade);

int main(int argc, char *argv[]) {
    char *filename = argv[1];
    int order = atoi(argv[2]);
    List *list = list_new();
    List *ordered_list = list_new();
    FILE *file = fopen(filename, "r");
    float grade, *grade_ptr = NULL, *data = NULL;
    int index = 0, i;
    size_t half_size;

    if (argc != 3) {
        fprintf(stderr, "Usage: %s <grades_file> <order>\n", argv[0]);
        return -1;
    }

    if (order != 1 && order != -1) {
        fprintf(stderr, "Order must be 1 (ascending) or -1 (descending).\n");
        return -1;
    }

    if (!file) {
        perror("Error opening file");
        return -1;
    }

    if (!list || !ordered_list) {
        fprintf(stderr, "Error creating lists.\n");
        fclose(file);
        return -1;
    }

    while (read_float(file, &grade) == OK) {
        grade_ptr = malloc(sizeof(float));
        if (!grade_ptr) {
            fprintf(stderr, "Error allocating memory.\n");
            fclose(file);
            list_free(list);
            list_free(ordered_list);
            return -1;
        }
        *grade_ptr = grade;

        if (index % 2 == 0) {
            list_pushBack(list, grade_ptr);
        } else {
            list_pushFront(list, grade_ptr);
        }
        index++;
    }
    fclose(file);

    printf("SIZE: %i\n", (int)list_size(list));
    list_print(stdout, list, float_print);
    printf("\nFinished inserting. Now we extract from the beginning and insert in order:\n");

    half_size = list_size(list) / 2;
    for (i = 0; i < half_size; i++) {
        data = list_popFront(list);
        list_pushInOrder(ordered_list, data, float_cmp, order);
        float_print(stdout, data);
        free(data);
    }
    printf("\nNow we extract from the end and insert in order:\n");

    while (!list_isEmpty(list)) {
        data = list_popBack(list);
        list_pushInOrder(ordered_list, data, float_cmp, order);
        float_print(stdout, data);
        free(data);
    }
    printf("\n");

    printf("SIZE: %i\n", (int)list_size(ordered_list));
    list_print(stdout, ordered_list, float_print);
    printf("\n");

    list_free(list);
    list_free(ordered_list);

    return 0;
}

int read_float(FILE *file, float *grade) {
    if (fscanf(file, "%f", grade) == 1) {
        return OK;
    }
    return ERROR;
}