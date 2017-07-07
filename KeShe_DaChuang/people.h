//
// Created by Famine on 2017/7/1.
//
#include <string.h>
#ifndef KESHE_DACHUANG_PEOPLE_H
#define KESHE_DACHUANG_PEOPLE_H

#endif //KESHE_DACHUANG_PEOPLE_H

struct people {
    char SNo[12];
    char name[20];
    int age;
    char grade;
    char collegeAndMajor[30];
    char class[10];
    char speciality[20];
    char undertakeTask[20];
    char phoneNum[12];
    int rank;
    struct people *next;
};

struct people *createPeople();

void addPeople(struct people *);

void findPeople(struct people *);