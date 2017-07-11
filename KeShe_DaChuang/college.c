//
// Created by Famine on 2017/7/11.
//
#include "college.h"

/*统计指定时间期限内有某院系学生参加的项目数量， 验收通过率、验收优良率、
未结题率等。支持模糊查询。可按项目数量，验收通过率、验收优良率、未结题率
从大到小排序。没有指定时间期限时为有记录以来的所有情况。
统计指定时间内的各院系参与创新活动的比例，比例计算公式为：
排名第一的学生为本院系的项目数/项目总数。
没有指定时间期限时为有记录以来各年度项目所有情况。 按比例大小从大到小
排序*/
struct college *getCollege(struct schedule *head, char *collegeName, char *startTime, char *finishTime) {
    /*先找到与collegeName相关的project*/
    struct project *collection_project[1000];
    int index = 0;
    struct schedule *schedule_p = head->next;
    while (schedule_p) {
        struct project *project_p = schedule_p->projectHead->next;
        /*当前project不为空，并且在时间范围内*/
        while (project_p && strcmp(project_p->startTime, startTime) >= 0 &&
                            strcmp(project_p->finishTime, finishTime) <= 0) {
            struct people *people_p = project_p->peopleHead->next;
            while (people_p) {
                /*如果学院和输入的学院相匹配*/
                if (strstr(people_p->collegeAndMajor, collegeName))
                    collection_project[index++] = project_p;
                people_p = people_p->next;
            }
            project_p = project_p->next;
        }
        schedule_p = schedule_p->next;
    }
    collection_project[index] = NULL;
    /*进行college的创建*/
    struct college *college_p = (struct college *) malloc(sizeof(struct college));
    college_p->projectNum = index;

    /*重置index*/
    index = 0;
    while (collection_project[index]) {
        if (strcmp(collection_project[index]->judgement, "未能正常通过")) {
            college_p->passingRate += 1;
        } else {
            college_p->unfinishedRate += 1;
        }
        if (strcmp(collection_project[index]->judgement, "优")  == 0 && strcmp(collection_project[index]->judgement, "良")  == 0) {
            college_p->excellentAndGoodRate += 1;
        }
    }
    /*优良率: 优良数 / 项目数*/
    college_p->excellentAndGoodRate /= college_p->projectNum;
    /*通过率：通过数 / 项目数*/
    college_p->passingRate /= college_p->projectNum;
    strcpy(college_p->collegeName, collegeName);
    college_p->unfinishedRate /= college_p->projectNum;
    return college_p;
}


void getCollegeCollection(struct college **college_collection, char **name_collection, struct schedule *head) {
    char time[2][10];
    printf("请输入开始时间：");
    scanf("%s", time[0]);
    printf("请输入结束时间：");
    scanf("%s", time[1]);
    /*添加条目索引*/
    int index = 0;
    while (name_collection[index]) {
        college_collection[index++] = getCollege(head, name_collection[index], time[0], time[1]);
    }
    college_collection[index] = NULL;
}


void printCollege(struct college *p) {
    printf("%-20s%-14d%-12.4f%-12.4f%-10.4f\n", p->collegeName, p->projectNum, p->passingRate, p->excellentAndGoodRate, p->unfinishedRate);
}

void printCollegeCollection(struct college **collection) {
    char title[5][12] = {"学院名称", "参与项目数量", "验收通过率", "验收优良率", "未结题率"};
    printf("%-20s%-14s%-12s%-12s%-10s\n", title[0], title[1], title[2], title[3], title[4]);
    int index = 0;
    while (collection[index]) {
        printCollege(collection[index++]);
    }
}

void getCollegeName(char **collection_name, struct schedule *head) {
    struct schedule *schedule_p = head->next;
    while (schedule_p) {
        struct project *project_p = schedule_p->projectHead->next;
        while (project_p) {
            struct people *people_p = project_p->peopleHead->next;
            while (people_p) {
                int index = 0;
                int isTheSameInCollection = 0;
                /*当collection不为空时*/
                while (collection_name[index]) {
                    /*如果当前人员的名字和容器中所有人的名字都不一样时*/
                    if (strcmp(collection_name[index++], people_p->name) == 0) {
                        isTheSameInCollection = 1;
                        break;
                    }
                }
                if (!isTheSameInCollection) {
                    /*一定是分配了内存的collection才行*/
                    char *college;
                    college = strtok(people_p->collegeAndMajor, "院");
                    strcat(college, "院");
                    printf("%s", college);
                    strcpy(collection_name[index], college);
                }
                /*容器以NULL结尾*/
                collection_name[index] = NULL;
                /*指针移动*/
                people_p = people_p->next;
            }
            /*指针移动*/
            project_p = project_p->next;
        }
        /*指针移动*/
        schedule_p = schedule_p->next;
    }
}

