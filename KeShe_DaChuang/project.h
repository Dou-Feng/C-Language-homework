//
// Created by Famine on 2017/7/1.
//

#include "people.h"

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
};

struct project *createProject();

struct project *findProByCNo(struct project *, char *);

void printProject(struct project *);

void printProTable(struct project *);

void modifyProject(struct project *);