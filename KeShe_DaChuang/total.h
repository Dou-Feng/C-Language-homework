//
// Created by Famine on 2017/7/8.
//

#include "schedule.h"

#ifndef KESHE_DACHUANG_TOTAL_H
#define KESHE_DACHUANG_TOTAL_H

#endif //KESHE_DACHUANG_TOTAL_H

struct year {
    char nianfen[5];
    struct schedule *list[1000];
    int length;
    struct year *next;
    struct year *prior;
    int registeredProjectNum;
    int supportedProjectNum;
    int fund;
    float supportingRate;
    float passingRate;
    float excellentRate;
    float qualifiedRate;
    float unfinishedRate;
    int studentNum;

};

/*统计指定时间期限内各年的年度计划里所申报的项目数、获得支持的项目数、
资金、 支持率、 验收通过率、优良率、合格率、未结题率、参与学生数量等，以及
总的申报的项目数、获得支持的项目数、支持率、验收通过率、优良率、合格率、
未结题率等。 可指定按年度申报数、获得支持的项目数、 资金总数、 支持率、验收
通过率等排序。没有指定时间期限时为有记录以来的所有情况。
统计指定时间期限内指定姓名的学生参加的项目、项目数量、验收通过率、验
收优良率、未结题率。支持模糊查询，可按学号、姓名、项目数量、验收通过率等
排序。 没有指定时间期限时为有记录以来的所有情况。

统计指定时间期限内有某院系学生参加的项目数量， 验收通过率、验收优良率、
未结题率等。支持模糊查询。可按项目数量，验收通过率、验收优良率、未结题率
从大到小排序。没有指定时间期限时为有记录以来的所有情况。
统计指定时间内的各院系参与创新活动的比例，比例计算公式为：
排名第一的学生为本院系的项目数/项目总数。
没有指定时间期限时为有记录以来各年度项目所有情况。 按比例大小从大到小
排序*/

struct year *create();

void addData(struct year *, struct schedule *, char *, char *, char *);

void dataHandle(struct year *);