//
// Created by Famine on 2017/7/2.
//

#include <malloc.h>
#include <stdio.h>
#include "project.h"

/*创建项目链表
用法：
    输入：无
    输出：项目链表的头指针*/
struct project *createProject() {
    struct project *head = (struct project *) malloc(sizeof(struct project));
    struct project *tail;
    tail = head;
    tail->next = NULL;
    head->prior = NULL;
    return head;
}


/*添加项目数据
用法：
    输入：项目链表头指针，文件指针
    输出：无
*/
void addProject(struct project *head, char *CNo, char *projectName, float fund, int number, char *startTime, char *endTime, char *judgement,
                char *leadMan, char *leadManNum, char *productForm, char *product, int isSupport) {
    /*添加到链表尾，头指针不存放数据，使得每个节点都会有前一个节点指向它，方便之后的链表排序和元素交换*/
    struct project *p = head;
    struct project *prior;
    while (p->next) {
        p = p->next;
    }
    p->next = (struct project *) malloc(sizeof(struct project));
    prior = p;
    p = p->next;
    p->prior = prior;
    /*方式选择*/
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

    /*为项目创建人员表*/
    p->peopleHead = createPeople();
    /*next节点为NUll*/
    p->next = NULL;
    sortProject(head);
}

/*刷新链表的数据
对于人员个数应该是和人员表的节点数相关联的，所以每次人员之后都应该调用次函数
用法：
    输入：项目的节点指针
    输出：无*/
void refreshProList(struct project *p) {
    p->member = 0;
    struct people *people1 = p->peopleHead->next;
    while (people1) {
        p->member++;
        people1 = people1->next;
    }
}


/*删除操作，封装了删除细节，先查询再确定删除
用法：
    输入：项目链表头指针
    输出：无*/
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
    /*防止越界访问*/
    if (temp_next)
        temp_next->prior = temp_prior;
    free(p);

}


/*交换项目节点
用法：
    输入：项目头指针，节点1的位置，节点2的位置*/
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

/*对项目进行排序
用法：
    输入：项目头指针
    输出：无*/
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
