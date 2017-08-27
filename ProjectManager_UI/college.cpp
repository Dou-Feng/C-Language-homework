  //
// Created by Famine on 2017/7/11.
//
#include "college.h"

struct college *getCollege(struct schedule *head, char *collegeName, char *startTime, char *finishTime) {
    /*���ҵ���collegeName��ص�project*/
    struct project *collection_project[1000];
    int index = 0;
    struct schedule *schedule_p = head->next;
    while (schedule_p) {
        struct project *project_p = schedule_p->projectHead->next;
        /*��ǰproject��Ϊ�գ�������ʱ�䷶Χ��*/
        while (project_p && strcmp(project_p->startTime, startTime) >= 0 &&
                            strcmp(project_p->finishTime, finishTime) <= 0) {
            struct people *people_p = project_p->peopleHead->next;
            while (people_p) {
                /*���ѧԺ�������ѧԺ��ƥ��*/
                if (strstr(people_p->collegeAndMajor, collegeName)) {
                    collection_project[index++] = project_p;
                    /*ֻҪ������һ���˵�ѧԺ������ѧԺ��ƥ����ô �Ϳ�������ѭ����*/
                    break;
                }
                people_p = people_p->next;
            }
            project_p = project_p->next;
        }
        schedule_p = schedule_p->next;
    }
    collection_project[index] = NULL;
    /*����college�Ĵ���*/
    struct college *college_p = (struct college *) malloc(sizeof(struct college));
    memset(college_p, 0, sizeof(struct college));
    college_p->projectNum = index;

    /*����index*/
    index = 0;
    while (collection_project[index]) {
        if (strcmp(collection_project[index]->judgement, "δ����������")) {
            college_p->passingRate += 1;
        } else {
            college_p->unfinishedRate += 1;
        }
        if (strcmp(collection_project[index]->judgement, "��")  == 0 || strcmp(collection_project[index]->judgement, "��")  == 0) {
            college_p->excellentAndGoodRate += 1;
        }
        index++;
    }
    /*������: ������ / ��Ŀ��*/
    college_p->excellentAndGoodRate /= college_p->projectNum;
    /*ͨ���ʣ�ͨ���� / ��Ŀ��*/
    college_p->passingRate /= college_p->projectNum;
    strcpy(college_p->collegeName, collegeName);
    college_p->unfinishedRate /= college_p->projectNum;
    return college_p;
}


void getCollegeCollection(struct college **college_collection, char **name_collection, struct schedule *head, char *startTime, char *endTime) {

    int index = 0;
    while (name_collection[index]) {
        college_collection[index] = getCollege(head, name_collection[index], startTime, endTime);
        index++;
    }
    college_collection[index] = NULL;
}



void getCollegeName(char **collection_name, struct schedule *head, char *startTime, char *finishTime) {
    struct schedule *schedule_p = head->next;
    int index = 0;
    while (schedule_p) {
        struct project *p_project = schedule_p->projectHead->next;
        while (p_project && strcmp(p_project->startTime, startTime) >= 0 &&
               strcmp(p_project->finishTime, finishTime) <= 0) {
            struct people *people_p = p_project->peopleHead->next;
            while (people_p) {
                index = 0;
                int isTheSameInCollection = 0;
                /*��collection��Ϊ��ʱ*/
                while (collection_name[index]) {
                    if (strstr(people_p->collegeAndMajor, collection_name[index++])) {
                        isTheSameInCollection = 1;
                        break;
                    }
                }
                if (!isTheSameInCollection) {
                    collection_name[index++] = people_p->collegeAndMajor;
                }
                /*������NULL��β*/
                collection_name[index] = NULL;
                /*ָ���ƶ�*/
                people_p = people_p->next;
            }
            /*ָ���ƶ�*/
            p_project = p_project->next;
        }
        /*ָ���ƶ�*/
        schedule_p = schedule_p->next;
    }
}


void sortCollegedentByProjectNum(college **collection)
{
    int index1, index2;
    struct college *temp;
    for (index1 = 0; collection[index1]; ++index1) {
        for (index2 = index1 + 1; collection[index2] ; ++index2) {
            if (collection[index1]->projectNum < collection[index2]->projectNum) {
                temp = collection[index1];
                collection[index1] = collection[index2];
                collection[index2] = temp;
            }
        }
    }
}

void sortCollegeByPassingRate(college **collection)
{
    int index1, index2;
    struct college *temp;
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

void sortCollegeByexcellentRate(college **collection)
{
    int index1, index2;
    struct college *temp;
    for (index1 = 0; collection[index1]; ++index1) {
        for (index2 = index1 + 1; collection[index2] ; ++index2) {
            if (collection[index1]->excellentAndGoodRate < collection[index2]->excellentAndGoodRate) {
                temp = collection[index1];
                collection[index1] = collection[index2];
                collection[index2] = temp;
            }
        }
    }
}

void sortCollegeByunfinishedRate(college **collection)
{
    int index1, index2;
    struct college *temp;
    for (index1 = 0; collection[index1]; ++index1) {
        for (index2 = index1 + 1; collection[index2] ; ++index2) {
            if (collection[index1]->unfinishedRate < collection[index2]->unfinishedRate) {
                temp = collection[index1];
                collection[index1] = collection[index2];
                collection[index2] = temp;
            }
        }
    }
}
