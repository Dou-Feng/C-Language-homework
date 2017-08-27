//
// Created by Famine on 2017/7/1.
//

#include "people.h"
#include <stdio.h>

#ifndef KESHE_DACHUANG_PROJECT_H
#define KESHE_DACHUANG_PROJECT_H

#endif //KESHE_DACHUANG_PROJECT_H

struct project {
    char CNo[10];
    char proName[40];
    float money;
    int member;
    char startTime[9];
    char finishTime[9];
    char judgement[13];
    char leadMan[10];
    char leadPhoneNum[12];
    char productForm[5];
    char productName[40];
    struct people *peopleHead;
    struct project *next;
    struct project *prior;
    int isSupported;
};

struct project *createProject();

void addProject(struct project *head, char *CNo, char *projectName, float fund, int number, char *startTime, char *endTime, char *judgement,
                char *leadMan, char *leadManNum, char *productForm, char *product, int isSupport);

void deleteProject(struct project *, int number);

void exchangeProject(struct project *, int, int);

void sortProject(struct project *);

void refreshProList(struct project *p);
