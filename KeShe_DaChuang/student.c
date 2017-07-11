//
// Created by Famine on 2017/7/11.
//

#include "student.h"

/*得到满足条件的项目*/
void getProject(struct project **collection, char *name, struct schedule *head, char *startTime, char *finishTime) {
    /*数组下标*/
    int index = 0;
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
}

/*统计指定时间期限内指定姓名的学生参加的项目、项目数量、验收通过率、验
收优良率、未结题率。支持模糊查询，可按学号、姓名、项目数量、验收通过率等
排序。 没有指定时间期限时为有记录以来的所有情况。*/
struct student *getStudentData(struct project *p) {

}