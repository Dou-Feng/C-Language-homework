//
// Created by Famine on 2017/7/11.
//
#include "college.h"

/*ͳ��ָ��ʱ����������ĳԺϵѧ���μӵ���Ŀ������ ����ͨ���ʡ����������ʡ�
δ�����ʵȡ�֧��ģ����ѯ���ɰ���Ŀ����������ͨ���ʡ����������ʡ�δ������
�Ӵ�С����û��ָ��ʱ������ʱΪ�м�¼���������������
ͳ��ָ��ʱ���ڵĸ�Ժϵ���봴�»�ı������������㹫ʽΪ��
������һ��ѧ��Ϊ��Ժϵ����Ŀ��/��Ŀ������
û��ָ��ʱ������ʱΪ�м�¼�����������Ŀ��������� ��������С�Ӵ�С
����*/
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


void getCollegeCollection(struct college **college_collection, char **name_collection, struct schedule *head) {
    char time[2][10] = {"20101010", "20180101"};
    /*printf("�����뿪ʼʱ�䣺");
    scanf("%s", time[0]);
    printf("���������ʱ�䣺");
    scanf("%s", time[1]);*/
    /*�����Ŀ����*/
    int index = 0;
    while (name_collection[index]) {
        college_collection[index] = getCollege(head, name_collection[index], time[0], time[1]);
        index++;
    }
    college_collection[index] = NULL;
}


void printCollege(struct college *p) {
    printf("%-20s%-14d%-12.4f%-12.4f%-10.4f\n", p->collegeName, p->projectNum, p->passingRate, p->excellentAndGoodRate, p->unfinishedRate);
}

void printCollegeCollection(struct college **collection) {
    char title[5][20] = {"ѧԺ����", "������Ŀ����", "����ͨ����", "����������", "δ������"};
    printf("%-20s%-14s%-12s%-12s%-10s\n", title[0], title[1], title[2], title[3], title[4]);
    int index = 0;
    while (collection[index]) {
        printCollege(collection[index++]);
    }
}

void getCollegeName(char **collection_name, struct schedule *head) {
    struct schedule *schedule_p = head->next;
    int index = 0;
    while (schedule_p) {
        struct project *project_p = schedule_p->projectHead->next;
        while (project_p) {
            struct people *people_p = project_p->peopleHead->next;
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
                    char *college;
                    /*�ִʷ����д��Ľ�*/
                    college = strtok(people_p->collegeAndMajor, "Ժ");
                    strcat(college, "Ժ");
                    printf("%s\n", college);
                    collection_name[index++] = college;
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
}

