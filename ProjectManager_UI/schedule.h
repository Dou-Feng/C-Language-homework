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

struct schedule* createSchedule();



void addSchedule(struct schedule *head, char *CSNo, float fund, char *leadMan, char *startTime, char *endTime);


void deleteSchedule(struct schedule *, int number);




void exchangeSchedule(struct schedule *head, int chg1, int chg2);


void sortSchedule(struct schedule *head);

void refreshSchList(struct schedule *p);
