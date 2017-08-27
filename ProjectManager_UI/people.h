//
// Created by Famine on 2017/7/1.
//
#include <string.h>
#include <stdio.h>
#include <string.h>
#define _CRT_SECURE_NO_WARNINGS
#ifndef KESHE_DACHUANG_PEOPLE_H
#define KESHE_DACHUANG_PEOPLE_H

#endif //KESHE_DACHUANG_PEOPLE_H

struct people {
    char SNo[12];
    char name[20];
    int age;
    char grade[10];
    char collegeAndMajor[30];
    char classes[10];
    char speciality[20];
    char undertakeTask[20];
    char phoneNum[12];
    int rank;
    struct people *next;
    struct people *prior;
};

struct people *createPeople();

void addPeople(struct people *head, char *SNo, char *name, int age, char *grade, char *college, char *classes, char *speciality, char *undertake,
               char *phone, int rank);

void deletePeople(struct people *, int number);

void sortPeople(struct people *);

void exchangePeople(struct people *, int, int);
