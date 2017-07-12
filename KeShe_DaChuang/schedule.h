//
// Created by Famine on 2017/7/1.
//

#include <malloc.h>
#include "project.h"

#ifndef KESHE_DACHUANG_SCHEDULE_H
#define KESHE_DACHUANG_SCHEDULE_H

#endif //KESHE_DACHUANG_SCHEDULE_H

struct schedule {
    char CSNo[10];
    float fund;
    char leadMan[10];
    int projectNum;
    int realSupProNum;
    int finishProNum;
    char startTime[9];
    char finishTime[9];
    struct project *projectHead;
    struct schedule *next;
    struct schedule *prior;
};

/*��������*/
struct schedule* createSchedule();



void addSchedule(struct schedule *, FILE *data);


void findSchCollectionByCSNo(struct schedule **, struct schedule *head, char *keyword);


void findSchedule(struct schedule *);


void findSchCollectionByFundMax(struct schedule **collection, struct schedule *head,float max,float min);


void findSchCollectionBySupMax(struct schedule **collection, struct schedule *head, int max,int min);


void findSchCollectionCombine(struct schedule **collection, struct schedule *head, char *, float, float,
                              int ,int);


void deleteSchedule(struct schedule *);



void modifySchedule(struct schedule *);


void modifyDetailSchedule(struct schedule *);



void printSchedule(struct schedule *);


void printSchTable(struct schedule *);


void printSchCollection(struct schedule **);


void exchangeSchedule(struct schedule *head, int chg1, int chg2);


void sortSchedule(struct schedule *head);

void refreshSchList(struct schedule *p);