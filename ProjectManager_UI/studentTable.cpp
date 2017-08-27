//
// Created by Famine on 2017/7/11.
//

#include "studentTable.h"


void getAllName(char **collection_name, struct schedule *head,char *startTime, char *finishTime) {  /*collection_name ���������е����֣� head�Ǽƻ������ͷָ��*/
    /*��Ҫ���������һ��nameΪNULL*/
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
                /*��collection��Ϊ��ʱ*/
                while (collection_name[index]) {
                    /*�����ǰ��Ա�����ֺ������������˵����ֶ���һ��ʱ*/
                    if (strcmp(collection_name[index++], people_p->name) == 0) {
                        isTheSameInCollection = 1;
                        break;
                    }
                }
                if (!isTheSameInCollection) {
                    /*collection_name[index] = (char *) malloc(sizeof(char) * 20);
                    *//*һ���Ƿ������ڴ��collection����*//*
                    strcpy(collection_name[index++], people_p->name);*/
                    collection_name[index++] = people_p->name;
                }
                /*������NULL��β*/
                collection_name[index] = NULL;
                /*ָ���ƶ�*/
                people_p = people_p->next;
            }
            /*ָ���ƶ�*/
            project_p = project_p->next;
        }
        /*ָ���ƶ�*/
        schedule_p = schedule_p->next;
    }
    if (!index_all) /*����ڼƻ�����û����Ա��Ϣ����ô��Ȼ����һ��������*/
        collection_name[0] = NULL;
}

void getStudentCollection(struct student **studentCollection, char **nameCollection, struct schedule *head, char *startTime, char *endTime) {
    /*��Ҫһ��ѧ�������飬��һ�����ֵ����飬���мƻ����ͷָ��*/
    /*�õ�ʱ������*/
    int index = 0;
    while (nameCollection[index]) {
        studentCollection[index] = getStudent(nameCollection[index], head, startTime, endTime);
        index++;
    }
    studentCollection[index] = NULL;
}




/*����*/
/*1.��ѧ������*/
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
