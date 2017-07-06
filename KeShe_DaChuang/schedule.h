//
// Created by Famine on 2017/7/1.
//

#include <malloc.h>
#include "project.h"

#ifndef KESHE_DACHUANG_SCHEDULE_H
#define KESHE_DACHUANG_SCHEDULE_H

#endif //KESHE_DACHUANG_SCHEDULE_H
/*双向链表*/
struct schedule {
    char CSNo[10];
    float fund;
    char leadMan[10];
    int projectNum;
    int realSupProNum;
    int finishProNum;
    char startTime[9];
    char finishTime[9];
    int excellentProNum;
    struct project *projectHead;
    struct schedule *next;
    struct schedule *prior;
};

/*创建链表*/
struct schedule* createSchedule();


/*在链表尾添加一组数据*/
void addSchedule(struct schedule *, FILE *data);

/*通过年度编号查找出所有的与关键词有关的计划表*/
void findSchCollectionByCSNo(struct schedule **,struct schedule *head, char *keyword);

/*查找操作*/
void findSchedule(struct schedule *);

/*通过经费查找，返回值为查找到的节点的指针*/
void findSchCollectionByFundMax(struct schedule **collection,struct schedule *head,float max,float min);

/*通过实际支持项目查找出所有的计划表*/
void findSchCollectionBySupMax(struct schedule **collection, struct schedule *head, int max,int min);

/*组合查询*/
void findSchCollectionCombine(struct schedule **collection, struct schedule *head, char *, float, float,
                              int ,int);

/*删除一个节点*/
void deleteSchedule(struct schedule *);


/*修改操作*/
void modifySchedule(struct schedule *);

/*修改具体的节点的内容*/
void modifyDetailSchedule(struct schedule *);


/*打印单个节点的具体内容*/
void printSchedule(struct schedule *);

/*打印计划表格*/
void printSchTable(struct schedule *);

/*打印容器里的计划表*/
void printSchCollection(struct schedule **);


/*用于改变链表的指针指向，到达交换元素的作用*/
void chgLocation(struct schedule *head, int chg1, int chg2);

void sortSchedule(struct schedule *head);