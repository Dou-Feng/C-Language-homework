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


/*����Ŀ���ơ� ���������������ۡ��ɹ����͡��ɹ����Ƶ� 5 �ַ�ʽ
���в�ѯ�����ж���Ŀ���ơ� �ɹ����ƿɽ���ģ����ѯ�� �������ɽ��������ѯ����
��þ��� 5 ��Ԫ���ڵ�������Ŀ�ȣ���ͬʱ����������Ա���Ҳ�����Ա�������� 1��
2�� 3����˳����������� ֧����ϲ�ѯ��*/
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

/*���ڸı������ָ��ָ�򣬵��ｻ��Ԫ�ص�����*/
void exchangeProject(struct project *, int, int);

void sortProject(struct project *);