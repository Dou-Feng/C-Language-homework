//
// Created by Famine on 2017/7/2.
//
#include <stdio.h>
#include <string.h>
#include "schedule.h"
#define _CRT_SECURE_NO_WARNINGS

/*�����ƻ�����
�÷���
    ���룺��
    ������ƻ�����ͷָ��*/
struct schedule *createSchedule() {
    /*ͷָ���βָ��*/
    struct schedule *head, *tail;
    /*�����ڴ�*/
    head = (struct schedule *) malloc(sizeof(struct schedule));
    tail = head;
    /*��һ���ڵ�ָ���*/
    tail->next = NULL;
    /*ǰһ��ָ��ָΪ��*/
    tail->prior = NULL;
    return head;
    /*��ɴ���һ�������ͷ���֣��Ⱦ�����Ϊ ͷ�ڵ����ڴ���䵫�ǲ�������ݣ���һ��ָ��ָ��գ�
     * ǰһ��ָ��ָ���*/
}


/* ��Ӽƻ�����
 �÷���
    ���룺�ƻ���ͷָ��
    �������*/
void addSchedule(struct schedule *head, char *CSNo, float fund, char *leadMan, char *startTime, char *endTime) {
    /*��ӵ�����β��ͷָ�벻������ݣ�ʹ��ÿ���ڵ㶼����ǰһ���ڵ�ָ����������֮������������Ԫ�ؽ���*/
    struct schedule *p = head;
    struct schedule *prior;
    struct project *prop;
    /*����������β��*/
    while (p->next) {
        p = p->next;
    }
    /*�����ڴ�*/
    p->next = (struct schedule *) malloc(sizeof(struct schedule));
    /*ʹָ��ǰһ��ָ��ָ��p*/
    prior = p;
    /*���̽���p��λ��*/
    p = p->next;
    /*ʹָ��ǰһ��ָ��ָ��p��ǰһλ*/
    p->prior = prior;
    /*Ϊ�ƻ������Ŀ*/
    p->projectHead = createProject();
    /*next�ڵ�ΪNUll*/
    p->next = NULL;
    /*�ҵ�project�Ĵ�����ݵ�ͷ�ڵ�*/
    prop = p->projectHead->next;


    p->projectNum = 0;
    p->realSupProNum = 0;
    p->finishProNum = 0;
    strcpy(p->CSNo, CSNo);
    p->fund = fund;
    strcpy(p->leadMan, leadMan);
    strcpy(p->startTime, startTime);
    strcpy(p->finishTime, endTime);
    sortSchedule(head);
    /*��������Ӧ���Ǵ���һ�������л�ã������ǴӼ��̻����ļ����*/
    /*��project��ͷָ�뿪ʼ���б������𽥵ĵ��������*/
    while (prop) {
        p->projectNum++;
        if (prop->isSupported)
            p->realSupProNum++;
        if (!strstr(prop->judgement, "δ����������")) {
            p->finishProNum++;
        }
        prop = prop->next;
    }
}



/*����ˢ�¼ƻ����е�����*/
/*��ÿ�θ���ѡ����Ŀ��Ϣ֮�����ˢ��
�÷���
    ���룺�ƻ���ڵ�
    �������*/
void refreshSchList(struct schedule *p) {
    struct project *proP = p->projectHead->next;
    if (!proP)
        return;
    p->projectNum = 0;
    p->realSupProNum = 0;
    p->finishProNum = 0;
    /*�����ƻ��е���Ŀ����*/
    while (proP) {
        p->projectNum++;
        /*����ĿΪ֧��*/
        if (proP->isSupported)
            p->realSupProNum++;
        /*����δ���������⣬�����Ŀ���Ϳ��Լ�һ*/
        if (!strstr(proP->judgement, "δ����������")) {
            p->finishProNum++;
        }
        proP = proP->next;
    }
}

/*ɾ������*/
void deleteSchedule(struct schedule *head, int number) {
    struct schedule *temp_prior, *temp_next;
    struct schedule *p = head->next;
    for (int i = 0; i < number; i++) {
        p = p->next;
    }
    temp_prior = p->prior;
    temp_next = p->next;
    temp_prior->next = temp_next;
    /*��ֹԽ�����*/
    if (temp_next)
        temp_next->prior = temp_prior;
    free(p);
}


void exchangeSchedule(struct schedule *head, int chg1, int chg2) {
    struct schedule *prior1 = head, *prior2 = head, *aftarget1, *aftarget2, *target1, *target2;
    for (int i = 0; i < chg1 - 1; ++i) {
        if (!prior1)
            return;
        prior1 = prior1->next;
    }
    for (int j = 0; j < chg2 - 1; ++j) {
        if (!prior2)
            return;
        prior2 = prior2->next;
    }
    target1 = prior1->next;
    target2 = prior2->next;
    aftarget1 = prior1->next->next;
    aftarget2 = prior2->next->next;
    if (prior1 == target2) {
        /*����next�ڵ�*/
        prior2->next = target1;
        target1->next = target2;
        target2->next = aftarget1;
        /*����prior�ڵ�*/
        target1->prior = prior2;
        target2->prior = target1;
        if (aftarget1)
            aftarget1->prior = target2;
    } else if (prior2 == target1) {
        prior1->next = target2;
        target2->next = target1;
        target1->next = aftarget2;

        target2->prior = prior1;
        target1->prior = target2;
        if (aftarget2)
            aftarget2->prior = target1;
    } else if (target1 == target2) {
        return;
    } else {
        prior1->next = target2;
        target2->next = aftarget1;
        prior2->next = target1;
        target1->next = aftarget2;

        target1->prior = prior2;
        target2->prior = prior1;
        if (aftarget1)
            aftarget1->prior = target2;
        if (aftarget2)
            aftarget2->prior = target1;
    }
}

void sortSchedule(struct schedule *head) {
    int length = 0;
    struct schedule *p = head->next;
    while (p != NULL) {
        length++;
        p = p->next;
    }
    p = head->next;
    char temp_CSNo[1000][16];
    for (int i = 0; i < length; ++i) {
        strcpy(temp_CSNo[i], p->CSNo);
        p = p->next;
    }
    char temp[16];
    for (int i = 0; i < length; ++i) {
        for (int j = i; j < length; ++j) {
            if (strcmp(temp_CSNo[i], temp_CSNo[j]) > 0) {
                strcpy(temp, temp_CSNo[i]);
                strcpy(temp_CSNo[i], temp_CSNo[j]);
                strcpy(temp_CSNo[j], temp);
                exchangeSchedule(head, i + 1, j + 1);
            }
        }
    }
}
