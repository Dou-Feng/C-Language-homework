//
// Created by Famine on 2017/7/2.
//

#include "people.h"
#include <malloc.h>

/*创建人员信息的链表
 *用法：没有输入，返回一个人员链表的头指针*/
struct people *createPeople() {
    struct people *head, *tail;
    head = (struct people *) malloc(sizeof(struct people));
    tail = head;
    tail->next = NULL;
    tail->prior = NULL;
    return head;
}

/*添加人员链表的节点，并存入数据
 用法：
    输入：链表头指针，和文件指针
    输出：无，但是链表中多了一条数据*/
void addPeople(struct people *head, char *SNo, char *name, int age, char *grade, char *college, char *classes, char *speciality, char *undertake,
               char *phone, int rank) {
    /*添加到链表尾，头指针不存放数据，使得每个节点都会有前一个节点指向它，方便之后的链表排序和元素交换*/
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

    /*next节点为NUll*/
    p->next = NULL;
    sortPeople(head);
}




/*删除人员
用法：
    输入：人员链表头指针
    输出：无
    删除了链表中的一个节点*/
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
    /*防止越界访问*/
    if (temp_next) {
        temp_next->prior = temp_prior;
    }
    free(p);
}


/*交换链表中的位置
用法：
    输入：人员链表头指针，人员1在链表中的位置，人员2在链表中的位置*/
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
        /*更改next节点*/
        prior2->next = target1;
        target1->next = target2;
        target2->next = aftarget1;
        /*更改prior节点*/
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


/*根据学号字典序排序
用法：
    输入：人员链表头指针
    输出：无*/
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
