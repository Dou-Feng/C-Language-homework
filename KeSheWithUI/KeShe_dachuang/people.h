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

void addPeople(struct people *, FILE *);



void findPeople(struct people *);

void findPeopleByName(struct people **collection, struct people *head, char *keyword);

void findPeopleBySpe(struct people **, struct people *, char *);


void deletePeople(struct people *);




void sortPeople(struct people *);

void exchangePeople(struct people *, int, int);




void modifyPeople(struct people *);

void modifyPeopleDetail(struct people *p);




void printPeoCollection(struct people **);

void printPeople(struct people *);

void printPeoTable(struct people *);

void printPeoByRank(struct people *);