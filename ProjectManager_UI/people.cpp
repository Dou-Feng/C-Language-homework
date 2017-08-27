//
// Created by Famine on 2017/7/2.
//

#include "people.h"
#include <malloc.h>

/*������Ա��Ϣ������
 *�÷���û�����룬����һ����Ա�����ͷָ��*/
struct people *createPeople() {
    struct people *head, *tail;
    head = (struct people *) malloc(sizeof(struct people));
    tail = head;
    tail->next = NULL;
    tail->prior = NULL;
    return head;
}

/*�����Ա����Ľڵ㣬����������
 �÷���
    ���룺����ͷָ�룬���ļ�ָ��
    ������ޣ����������ж���һ������*/
void addPeople(struct people *head, char *SNo, char *name, int age, char *grade, char *college, char *classes, char *speciality, char *undertake,
               char *phone, int rank) {
    /*��ӵ�����β��ͷָ�벻������ݣ�ʹ��ÿ���ڵ㶼����ǰһ���ڵ�ָ����������֮������������Ԫ�ؽ���*/
    struct people *p = head;
    struct people *prior;
    while (p->next) {
        p = p->next;
    }
    p->next = (struct people *) malloc(sizeof(struct people));
    prior = p;
    p = p->next;
    p->prior = prior;


    strcpy(p->SNo, SNo);
    strcpy(p->name, name);
    p->age = age;
    strcpy(p->grade, grade);
    strcpy(p->collegeAndMajor,college);
    strcpy(p->classes, classes);
    strcpy(p->speciality, speciality);
    strcpy(p->undertakeTask, undertake);
    strcpy(p->phoneNum, phone);
    p->rank = rank;

    /*next�ڵ�ΪNUll*/
    p->next = NULL;
    sortPeople(head);
}




/*ɾ����Ա
�÷���
    ���룺��Ա����ͷָ��
    �������
    ɾ���������е�һ���ڵ�*/
void deletePeople(struct people *head, int number) {
    struct people *temp_prior;
    struct people *temp_next ;
    struct people *p = head->next;
    for (int i = 0; i < number; i++) {
        p = p->next;
    }
    temp_prior = p->prior;
    temp_next = p->next;
    temp_prior->next = temp_next;
    /*��ֹԽ�����*/
    if (temp_next) {
        temp_next->prior = temp_prior;
    }
    free(p);
}


/*���������е�λ��
�÷���
    ���룺��Ա����ͷָ�룬��Ա1�������е�λ�ã���Ա2�������е�λ��*/
void exchangePeople(struct people *head, int chg1, int chg2) {
    struct people *prior1 = head, *prior2 = head, *aftarget1, *aftarget2, *target1, *target2;
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


/*����ѧ���ֵ�������
�÷���
    ���룺��Ա����ͷָ��
    �������*/
void sortPeople(struct people *head) {
    int length = 0;
    struct people *p = head->next;
    while (p != NULL) {
        length++;
        p = p->next;
    }
    p = head->next;
    char temp_SNo[1000][16];
    for (int i = 0; i < length; ++i) {
        strcpy(temp_SNo[i], p->SNo);
        p = p->next;
    }
    char temp[16];
    for (int i = 0; i < length; ++i) {
        for (int j = i; j < length; ++j) {
            if (strcmp(temp_SNo[i], temp_SNo[j]) > 0) {
                strcpy(temp, temp_SNo[i]);
                strcpy(temp_SNo[i], temp_SNo[j]);
                strcpy(temp_SNo[j], temp);
                exchangePeople(head, i + 1, j + 1);
            }
        }
    }
}
