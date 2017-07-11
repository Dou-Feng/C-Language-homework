//
// Created by Famine on 2017/7/11.
//

#include "studentTable.h"


void getAllName(char **collection_name, struct schedule *head) {  /*collection_name 用与存放所有的名字， head是计划链表的头指针*/
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
                if (!isTheSameInCollection)
                /*一定是分配了内存的collection才行*/
                strcpy(collection_name[index++], people_p->name);
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

void getStudentCollection(struct student **studentCollection, char **nameCollection, struct schedule *head) {
    /*需要一个学生的数组，和一个名字的数组，还有计划表的头指针*/
    /*得到时间区间*/
    char time[2][10];
    printf("请输入开始时间：");
    scanf("%s", time[0]);
    printf("请输入结束时间：");
    scanf("%s", time[1]);
    /*添加条目索引*/
    int index = 0;
    while (nameCollection[index]) {
        studentCollection[index++] = getStudent(nameCollection[index], head, time[0], time[1]);
    }
    studentCollection[index] = NULL;
}

void printStudentCollection(struct student **collection) {
    char title[5][12] = {"姓名", "参与项目数量", "验收通过率", "验收优良率", "未结题率"};
    printf("%-10s%-14s%-12s%-12s%-10s\n", title[0], title[1], title[2], title[3], title[4]);
    int index = 0;
    while (collection[index]) {
        printStudent(collection[index++]);
    }
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
