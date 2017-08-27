//
// Created by Famine on 2017/7/2.
//
#include <stdio.h>
#include <string.h>
#include "schedule.h"
#define _CRT_SECURE_NO_WARNINGS

/*创建计划链表
用法：
    输入：无
    输出：计划链表头指针*/
struct schedule *createSchedule() {
    /*头指针和尾指针*/
    struct schedule *head, *tail;
    /*分配内存*/
    head = (struct schedule *) malloc(sizeof(struct schedule));
    tail = head;
    /*下一个节点指向空*/
    tail->next = NULL;
    /*前一个指针指为空*/
    tail->prior = NULL;
    return head;
    /*完成创建一个链表的头部分，先决条件为 头节点有内存分配但是不存放数据，下一个指针指向空，
     * 前一个指针指向空*/
}


/* 添加计划数据
 用法：
    输入：计划表头指针
    输出：无*/
void addSchedule(struct schedule *head, char *CSNo, float fund, char *leadMan, char *startTime, char *endTime) {
    /*添加到链表尾，头指针不存放数据，使得每个节点都会有前一个节点指向它，方便之后的链表排序和元素交换*/
    struct schedule *p = head;
    struct schedule *prior;
    struct project *prop;
    /*遍历到链表尾部*/
    while (p->next) {
        p = p->next;
    }
    /*分配内存*/
    p->next = (struct schedule *) malloc(sizeof(struct schedule));
    /*使指向前一个指针指向p*/
    prior = p;
    /*立刻进行p的位移*/
    p = p->next;
    /*使指向前一个指针指向p的前一位*/
    p->prior = prior;
    /*为计划添加项目*/
    p->projectHead = createProject();
    /*next节点为NUll*/
    p->next = NULL;
    /*找到project的存放数据的头节点*/
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
    /*关联数据应该是从下一级链表中获得，而不是从键盘或者文件获得*/
    /*用project的头指针开始进行遍历，逐渐的到相关数据*/
    while (prop) {
        p->projectNum++;
        if (prop->isSupported)
            p->realSupProNum++;
        if (!strstr(prop->judgement, "未能正常结题")) {
            p->finishProNum++;
        }
        prop = prop->next;
    }
}



/*用于刷新计划表中的数据*/
/*在每次更改选定项目信息之后进行刷新
用法：
    输入：计划表节点
    输出：无*/
void refreshSchList(struct schedule *p) {
    struct project *proP = p->projectHead->next;
    if (!proP)
        return;
    p->projectNum = 0;
    p->realSupProNum = 0;
    p->finishProNum = 0;
    /*遍历计划中的项目链表*/
    while (proP) {
        p->projectNum++;
        /*当项目为支持*/
        if (proP->isSupported)
            p->realSupProNum++;
        /*不是未能正常结题，完成项目数就可以加一*/
        if (!strstr(proP->judgement, "未能正常结题")) {
            p->finishProNum++;
        }
        proP = proP->next;
    }
}

/*删除操作*/
void deleteSchedule(struct schedule *head, int number) {
    struct schedule *temp_prior, *temp_next;
    struct schedule *p = head->next;
    for (int i = 0; i < number; i++) {
        p = p->next;
    }
    temp_prior = p->prior;
    temp_next = p->next;
    temp_prior->next = temp_next;
    /*防止越界访问*/
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
