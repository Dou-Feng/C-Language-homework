//
// Created by Famine on 2017/7/11.
//

#include "student.h"

/*�õ�������������Ŀ*/
/*�ȵõ��������ֵ�projectȻ���ڴ�project�г�ȡ���ݣ����뵽student��*/
struct student *getStudent(char *name, struct schedule *head, char *startTime, char *finishTime) {
    /*�����±�*/
    int index = 0;
    char SNo[10];
    struct project *collection[1000];
    /*�ƻ����ƶ�ָ��*/
    struct schedule *p_schedule = head->next;
    while (p_schedule) {
        /*��Ŀ�ƶ�ָ��*/
        struct project *p_project = p_schedule->projectHead->next;
        while (p_project) {
            /*��Ա�ƶ�ָ��*/
            struct people *p_people = p_project->peopleHead->next;
            /*����Ա��Ϊ������ʱ���޶���Χ֮��Ϊ��*/
            while (p_people && strcmp(p_project->startTime, startTime) >= 0 &&
                   strcmp(p_project->finishTime, finishTime) <= 0) {
                /*�жϣ�������һ��ʱ�����Լ��뵽����*/
                if (strcmp(p_people->name, name) == 0) {
                    collection[index++] = p_project;
                    strcpy(SNo, p_people->SNo);
                    /*ֱ����������Ŀ�������ٱ�����Ա����*/
                    break;
                }
                /*ָ����λ*/
                p_people = p_people->next;
            }
            /*ָ����λ*/
            p_project = p_project->next;
        }
        /*ָ����λ*/
        p_schedule = p_schedule->next;
    }
    /*ע���������NULL����*/
    collection[index] = NULL;
    return getStudentData(name, SNo, collection);
}

/*ͳ��ָ��ʱ��������ָ��������ѧ���μӵ���Ŀ����Ŀ����������ͨ���ʡ���
�������ʡ�δ�����ʡ�֧��ģ����ѯ���ɰ�ѧ�š���������Ŀ����������ͨ���ʵ�
���� û��ָ��ʱ������ʱΪ�м�¼���������������*/
struct student *getStudentData(char *name, char *SNo, struct project **p) { /* ��Ҫ���ֺ��������ֵ���Ŀ����*/
    struct student *stu = (struct student *) malloc(sizeof(struct student));
    /*���ڼ�����Ŀ���������*/
    int index;
    for (index = 0; p[index]; ++index) {
        stu->collection_project[index] = p[index];
        if (strcmp(p[index]->judgement, "δ������ͨ��")) {
            stu->passingRate += 1;
        } else {
            stu->unfinishedRate += 1;
        }
        if (strcmp(p[index]->judgement, "��")  == 0 && strcmp(p[index]->judgement, "��")  == 0) {
            stu->excellentAndGoodRate += 1;
        }
    }
    /*�õ�����Ŀ������������*/
    stu->project_number = index;
    /*������: ������ / ��Ŀ��*/
    stu->excellentAndGoodRate /= stu->project_number;
    /*ͨ���ʣ�ͨ���� / ��Ŀ��*/
    stu->passingRate /= stu->project_number;
    strcpy(stu->name, name);
    strcpy(stu->SNo, SNo);
    stu->unfinishedRate /= stu->project_number;
    return stu;
}

void printStudent(struct student *p) {
    printf("%-10s%-14d%-12.4f%-12.4f%-10.4f\n", p->name, p->project_number, p->passingRate, p->excellentAndGoodRate, p->unfinishedRate);
    /*�Ȳ���ӡ��Ŀ��ϸ����*/
    /*printf("�������ĿΪ��\n");
    printProCollection(p->collection_project);*/
}

