//
// Created by Famine on 2017/7/11.
//

#ifndef KESHE_DACHUANG_STUDENT_H
#define KESHE_DACHUANG_STUDENT_H

#endif //KESHE_DACHUANG_STUDENT_H


#include "college.h"

typedef struct student {
    char SNo[12];
    char name[12];
    struct project *collection_project[100];
    int project_number;
    float passingRate;
    float excellentAndGoodRate;
    float  unfinishedRate;
}Stu;

struct student *getStudent(char *name, struct schedule *head, char *startTime, char *finishTime);

struct student *getStudentData(char *, char *, struct project **);


