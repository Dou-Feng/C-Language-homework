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
};

struct project *createProject();

void addProject(struct project *, FILE *);


/*按项目名称、 经费数、结题评价、成果类型、成果名称等 5 种方式
进行查询。其中对项目名称、 成果名称可进行模糊查询， 经费数可进行区间查询（如
获得经费 5 万元以内的所有项目等）。同时输出参与的人员，且参与人员按照排名 1、
2、 3…的顺序依次输出。 支持组合查询。*/
void findProject(struct project *);

void findProCollectionByProName(struct project **,struct project *, char *);

void findProCollectionByMoney(struct project **, struct project *, float max,float min);

void findProCollectionByJudgement(struct project **, struct project *, char *);

void findProCollectionByProductForm(struct project **, struct project *, char *);

void findProCollectionByProductName(struct project **, struct project *, char *);

void findProCombine(struct project **, struct project *, float, float, char *, char *, char *,
        char *);



void deleteProject(struct project *);


void modifyProject(struct project *);

void modifyProDetail(struct project *);


void printProject(struct project *);

void printProTable(struct project *);

void printProCollection(struct project **);

/*用于改变链表的指针指向，到达交换元素的作用*/
void exchangeProject(struct project *, int, int);

void sortProject(struct project *);