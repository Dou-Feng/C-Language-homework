//
// Created by Famine on 2017/7/2.
//

#include <malloc.h>
#include <stdio.h>
#include "project.h"

/*������Ŀ����
�÷���
    ���룺��
    �������Ŀ�����ͷָ��*/
struct project *createProject() {
    struct project *head = (struct project *) malloc(sizeof(struct project));
    struct project *tail;
    tail = head;
    tail->next = NULL;
    head->prior = NULL;
    return head;
}


/*�����Ŀ����
�÷���
    ���룺��Ŀ����ͷָ�룬�ļ�ָ��
    �������
*/
void addProject(struct project *head, char *CNo, char *projectName, float fund, int number, char *startTime, char *endTime, char *judgement,
                char *leadMan, char *leadManNum, char *productForm, char *product, int isSupport) {
    /*��ӵ�����β��ͷָ�벻������ݣ�ʹ��ÿ���ڵ㶼����ǰһ���ڵ�ָ����������֮������������Ԫ�ؽ���*/
    struct project *p = head;
    struct project *prior;
    while (p->next) {
        p = p->next;
    }
    p->next = (struct project *) malloc(sizeof(struct project));
    prior = p;
    p = p->next;
    p->prior = prior;
    /*��ʽѡ��*/
    p->member = number;
    strcpy(p->CNo, CNo);
    strcpy(p->proName, projectName);
    p->money = fund;
    strcpy(p->startTime, startTime);
    strcpy(p->finishTime, endTime);
    strcpy(p->judgement, judgement);
    strcpy(p->leadMan, leadMan);
    strcpy(p->leadPhoneNum, leadManNum);
    strcpy(p->productForm, productForm);
    strcpy(p->productName, product);
    p->isSupported = isSupport;

    /*Ϊ��Ŀ������Ա��*/
    p->peopleHead = createPeople();
    /*next�ڵ�ΪNUll*/
    p->next = NULL;
    sortProject(head);
}

/*ˢ�����������
������Ա����Ӧ���Ǻ���Ա��Ľڵ���������ģ�����ÿ����Ա֮��Ӧ�õ��ôκ���
�÷���
    ���룺��Ŀ�Ľڵ�ָ��
    �������*/
void refreshProList(struct project *p) {
    p->member = 0;
    struct people *people1 = p->peopleHead->next;
    while (people1) {
        p->member++;
        people1 = people1->next;
    }
}


/*ɾ����������װ��ɾ��ϸ�ڣ��Ȳ�ѯ��ȷ��ɾ��
�÷���
    ���룺��Ŀ����ͷָ��
    �������*/
void deleteProject(struct project *head, int number) {

    struct project *temp_prior;
    struct project *temp_next;
    struct project *p = head->next;
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


/*������Ŀ�ڵ�
�÷���
    ���룺��Ŀͷָ�룬�ڵ�1��λ�ã��ڵ�2��λ��*/
void exchangeProject(struct project *head, int chg1, int chg2) {
    struct project *prior1 = head, *prior2 = head, *aftarget1, *aftarget2, *target1, *target2;
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

/*����Ŀ��������
�÷���
    ���룺��Ŀͷָ��
    �������*/
void sortProject(struct project *head) {
    int length = 0;
    struct project *p = head->next;
    while (p != NULL) {
        length++;
        p = p->next;
    }
    p = head->next;
    char temp_CNo[1000][16];
    for (int i = 0; i < length; ++i) {
        strcpy(temp_CNo[i], p->CNo);
        p = p->next;
    }
    char temp[16];
    for (int i = 0; i < length; ++i) {
        for (int j = i; j < length; ++j) {
            if (strcmp(temp_CNo[i], temp_CNo[j]) > 0) {
                strcpy(temp, temp_CNo[i]);
                strcpy(temp_CNo[i], temp_CNo[j]);
                strcpy(temp_CNo[j], temp);
                exchangeProject(head, i + 1, j + 1);
            }
        }
    }
}
