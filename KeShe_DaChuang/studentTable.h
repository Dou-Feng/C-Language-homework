//
// Created by Famine on 2017/7/11.
//

#ifndef KESHE_DACHUANG_STUDENTTABLE_H
#define KESHE_DACHUANG_STUDENTTABLE_H

#endif //KESHE_DACHUANG_STUDENTTABLE_H

/*统计指定时间期限内指定姓名的学生参加的项目、项目数量、验收通过率、验
收优良率、未结题率。支持模糊查询，可按学号、姓名、项目数量、验收通过率等
排序。 没有指定时间期限时为有记录以来的所有情况。*/
#include "student.h"

void getAllName(char **, struct schedule *);

void getStudentCollection(struct student **, char **, struct schedule *);

void printStudentCollection(struct student **collection);





void sortStudentBySNo(struct student **collection);

void sortStudentByName(struct student **collection);

void sortStudentByProjectNum(struct student **collection);

void sortStudentByPassingRate(struct student **collection);
