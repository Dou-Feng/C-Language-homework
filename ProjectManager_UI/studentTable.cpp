//
// Created by Famine on 2017/7/11.
//

#include "studentTable.h"


void getAllName(char **collection_name, struct schedule *head,char *startTime, char *finishTime) {  /*collection_name 用与存放所有的名字， head是计划链表的头指针*/
    /*需要让数组最后一个name为NULL*/
    int index_all = 0;
    struct schedule *schedule_p = head->next;
    while (schedule_p) {
        struct project *project_p = schedule_p->projectHead->next;
        while (project_p && strcmp(project_p->startTime, startTime) >= 0 &&
               strcmp(project_p->finishTime, finishTime) <= 0) {
            struct people *people_p = project_p->peopleHead->next;
            int index = 0;
            while (people_p) {
                index_all = 1;
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
                    /*collection_name[index] = (char *) malloc(sizeof(char) * 20);
                    *//*一定是分配了内存的collection才行*//*
                    strcpy(collection_name[index++], people_p->name);*/
                    collection_name[index++] = people_p->name;
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
    if (!index_all) /*如果在计划表中没有人员信息，那么自然返回一个空数组*/
        collection_name[0] = NULL;
}

void getStudentCollection(struct student **studentCollection, char **nameCollection, struct schedule *head, char *startTime, char *endTime) {
    /*需要一个学生的数组，和一个名字的数组，还有计划表的头指针*/
    /*得到时间区间*/
    int index = 0;
    while (nameCollection[index]) {
        studentCollection[index] = getStudent(nameCollection[index], head, startTime, endTime);
        index++;
    }
    studentCollection[index] = NULL;
}




/*排序*/
/*1.按学号排序*/
void sortStudentBySNo(struct student **collection) {
    int index1, index2;
    struct student *temp;
    for (index1 = 0; collection[index1]; ++index1) {
        for (index2 = index1 + 1; collection[index2] ; ++index2) {
            if (strcmp(collection[index1]->SNo, collection[index2]->SNo) < 0) {
                temp = collection[index1];
                collection[index1] = collection[index2];
                collection[index2] = temp;
            }
        }
    }
}

void sortStudentByName(struct student **collection) {
    int index1, index2;
    struct student *temp;
    for (index1 = 0; collection[index1]; ++index1) {
        for (index2 = index1 + 1; collection[index2] ; ++index2) {
            if (strcmp(collection[index1]->name, collection[index2]->name) < 0) {
                temp = collection[index1];
                collection[index1] = collection[index2];
                collection[index2] = temp;
            }
        }
    }
}

void sortStudentByProjectNum(struct student **collection) {
    int index1, index2;
    struct student *temp;
    for (index1 = 0; collection[index1]; ++index1) {
        for (index2 = index1 + 1; collection[index2] ; ++index2) {
            if (collection[index1]->project_number < collection[index2]->project_number) {
                temp = collection[index1];
                collection[index1] = collection[index2];
                collection[index2] = temp;
            }
        }
    }
}

void sortStudentByPassingRate(struct student **collection) {
    int index1, index2;
    struct student *temp;
    for (index1 = 0; collection[index1]; ++index1) {
        for (index2 = index1 + 1; collection[index2] ; ++index2) {
            if (collection[index1]->passingRate < collection[index2]->passingRate) {
                temp = collection[index1];
                collection[index1] = collection[index2];
                collection[index2] = temp;
            }
        }
    }
}
