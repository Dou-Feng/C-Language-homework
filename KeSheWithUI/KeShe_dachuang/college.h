#include "total.h"

#ifndef KESHE_DACHUANG_COLLEGE_H
#define KESHE_DACHUANG_COLLEGE_H

#endif //KESHE_DACHUANG_COLLEGE_H
/*统计指定时间期限内有某院系学生参加的项目数量， 验收通过率、验收优良率、
未结题率等。支持模糊查询。可按项目数量，验收通过率、验收优良率、未结题率
从大到小排序。没有指定时间期限时为有记录以来的所有情况。
统计指定时间内的各院系参与创新活动的比例，比例计算公式为：
排名第一的学生为本院系的项目数/项目总数。
没有指定时间期限时为有记录以来各年度项目所有情况。 按比例大小从大到小
排序*/

struct college {
    char collegeName[20];
    int projectNum;
    float passingRate;
    float excellentAndGoodRate;
    float unfinishedRate;
};

struct college *getCollege(struct schedule *, char *, char *, char *);

void getCollegeCollection(struct college **, char **, struct schedule *);

void printCollege(struct college *);

void printCollegeCollection(struct college **);

void getCollegeName(char **, struct schedule *);



/*排序*/
