#include "student.h"

void getAllName(char **collection_name, struct schedule *head,char *startTime, char *finishTime);

void getStudentCollection(struct student **studentCollection, char **nameCollection, struct schedule *head, char *startTime, char *endTime);


void sortStudentBySNo(struct student **collection);

void sortStudentByName(struct student **collection);

void sortStudentByProjectNum(struct student **collection);

void sortStudentByPassingRate(struct student **collection);
