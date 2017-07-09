//
// Created by Famine on 2017/7/1.
//

#include <malloc.h>
#include "project.h"

#ifndef KESHE_DACHUANG_SCHEDULE_H
#define KESHE_DACHUANG_SCHEDULE_H

#endif //KESHE_DACHUANG_SCHEDULE_H
/*˫������*/
/* ��ȱ��
 * Ͷ���ʽ�
 * ������
 * �걨��Ŀ��   (������Ŀ������
 * ʵ��֧����Ŀ ������isSupported)
 * ������Ŀ��  (�����������ۣ�
 * �ƻ���ʼʱ��
 * �ƻ����ʱ��
 * ��Ŀ������Ϣ*/
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


/*������β���һ������*/
void addSchedule(struct schedule *, FILE *data);

/*ͨ����ȱ�Ų��ҳ����е���ؼ����йصļƻ���*/
void findSchCollectionByCSNo(struct schedule **, struct schedule *head, char *keyword);

/*���Ҳ���*/
void findSchedule(struct schedule *);

/*ͨ�����Ѳ��ң�����ֵΪ���ҵ��Ľڵ��ָ��*/
void findSchCollectionByFundMax(struct schedule **collection, struct schedule *head,float max,float min);

/*ͨ��ʵ��֧����Ŀ���ҳ����еļƻ���*/
void findSchCollectionBySupMax(struct schedule **collection, struct schedule *head, int max,int min);

/*��ϲ�ѯ*/
void findSchCollectionCombine(struct schedule **collection, struct schedule *head, char *, float, float,
                              int ,int);

/*ɾ��һ���ڵ�*/
void deleteSchedule(struct schedule *);


/*�޸Ĳ���*/
void modifySchedule(struct schedule *);

/*�޸ľ���Ľڵ������*/
void modifyDetailSchedule(struct schedule *);


/*��ӡ�����ڵ�ľ�������*/
void printSchedule(struct schedule *);

/*��ӡ�ƻ����*/
void printSchTable(struct schedule *);

/*��ӡ������ļƻ���*/
void printSchCollection(struct schedule **);


/*���ڸı������ָ��ָ�򣬵��ｻ��Ԫ�ص�����*/
void exchangeSchedule(struct schedule *head, int chg1, int chg2);

/*�����ֵ������ȱ�Ž�������*/
void sortSchedule(struct schedule *head);

void refreshSchList(struct schedule *p);