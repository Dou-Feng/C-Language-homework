//
// Created by Famine on 2017/7/11.
//

#include "student.h"

/*得到满足条件的项目*/
/*先得到满足名字的project然后，在从project中抽取数据，加入到student中*/
struct student *getStudent(char *name, struct schedule *head, char *startTime, char *finishTime) {
    /*数组下标*/
    int index = 0;
    char SNo[10];
    struct project *collection[1000];
    /*计划表移动指针*/
    struct schedule *p_schedule = head->next;
    while (p_schedule) {
        /*项目移动指针*/
        struct project *p_project = p_schedule->projectHead->next;
        while (p_project) {
            /*人员移动指针*/
            struct people *p_people = p_project->peopleHead->next;
            /*当人员不为空且在时间限定范围之内为真*/
            while (p_people && strcmp(p_project->startTime, startTime) >= 0 &&
                   strcmp(p_project->finishTime, finishTime) <= 0) {
                /*判断：当名字一致时，可以加入到容器*/
                if (strcmp(p_people->name, name) == 0) {
                    collection[index++] = p_project;
                    strcpy(SNo, p_people->SNo);
                    /*直接跳出该项目，不会再遍历人员表了*/
                    break;
                }
                /*指针移位*/
                p_people = p_people->next;
            }
            /*指针移位*/
            p_project = p_project->next;
        }
        /*指针移位*/
        p_schedule = p_schedule->next;
    }
    /*注意最后是以NULL结束*/
    collection[index] = NULL;
    return getStudentData(name, SNo, collection);
}

/*统计指定时间期限内指定姓名的学生参加的项目、项目数量、验收通过率、验
收优良率、未结题率。支持模糊查询，可按学号、姓名、项目数量、验收通过率等
排序。 没有指定时间期限时为有记录以来的所有情况。*/
struct student *getStudentData(char *name, char *SNo, struct project **p) { /* 需要名字和满足名字的项目数组*/
    struct student *stu = (struct student *) malloc(sizeof(struct student));
    /*用于加入项目数组的索引*/
    int index;
    for (index = 0; p[index]; ++index) {
        stu->collection_project[index] = p[index];
        if (strcmp(p[index]->judgement, "未能正常通过")) {
            stu->passingRate += 1;
        } else {
            stu->unfinishedRate += 1;
        }
        if (strcmp(p[index]->judgement, "优")  == 0 && strcmp(p[index]->judgement, "良")  == 0) {
            stu->excellentAndGoodRate += 1;
        }
    }
    /*得到的项目数就是索引数*/
    stu->project_number = index;
    /*优良率: 优良数 / 项目数*/
    stu->excellentAndGoodRate /= stu->project_number;
    /*通过率：通过数 / 项目数*/
    stu->passingRate /= stu->project_number;
    strcpy(stu->name, name);
    strcpy(stu->SNo, SNo);
    stu->unfinishedRate /= stu->project_number;
    return stu;
}

void printStudent(struct student *p) {
    printf("%-10s%-14d%-12.4f%-12.4f%-10.4f\n", p->name, p->project_number, p->passingRate, p->excellentAndGoodRate, p->unfinishedRate);
    /*先不打印项目详细数据*/
    /*printf("参与的项目为：\n");
    printProCollection(p->collection_project);*/
}

