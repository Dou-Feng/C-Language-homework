#include "schedule.h"

#ifndef KESHE_DACHUANG_TOTAL_H
#define KESHE_DACHUANG_TOTAL_H

#endif //KESHE_DACHUANG_TOTAL_H

struct data {
    char scheduleNo[10];
    int registeredProjectNum;
    int supportedProjectNum;
    float fund;
    float supportingRate;
    float passingRate;
    float excellentRate;
    float qualifiedRate;
    float unfinishedRate;
    int studentNum;

};

/*
 *


统计指定时间期限内有某院系学生参加的项目数量， 验收通过率、验收优良率、
未结题率等。支持模糊查询。可按项目数量，验收通过率、验收优良率、未结题率
从大到小排序。没有指定时间期限时为有记录以来的所有情况。
统计指定时间内的各院系参与创新活动的比例，比例计算公式为：
排名第一的学生为本院系的项目数/项目总数。
没有指定时间期限时为有记录以来各年度项目所有情况。 按比例大小从大到小
排序*/


void getInTimeSch(struct schedule **collection, struct schedule *, char *, char *);

struct data *getSchData(struct schedule *);

void sortData(struct data **collectionData, struct schedule **collectionSch);

void sortDataBySupportingRate(struct data **collectionData, struct schedule **collectionSch);

void sortDataByPassingRate(struct data **collectionData, struct schedule **collectionSch);

void sortDataBySupportedNum(struct data **collectionData, struct schedule **collectionSch);

void sortDataByFund(struct data **collectionData, struct schedule **collectionSch);

void printData(struct data*);

void fullDataCollection(struct data **collectionData, struct schedule **collectionSch);

void printDataCollection(struct data **);