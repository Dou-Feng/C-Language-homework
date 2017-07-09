//
// Created by Famine on 2017/7/8.
//

#include "total.h"

struct year *create() {
    struct year *head, *tail;
    head = (struct year *) malloc(sizeof(struct year));
    head->prior = NULL;
    tail = head;
    tail->next = NULL;
    return head;
}

void addData(struct year *head, struct schedule *schHead, char *startTime, char *endTime, char *nianfen) {
    /*添加到链表尾，头指针不存放数据，使得每个节点都会有前一个节点指向它，方便之后的链表排序和元素交换*/
    struct year *p = head;
    struct year *prior;
    struct schedule *schP = schHead;
    int index = 0;
    while (p->next) {
        p = p->next;
    }
    p->next = (struct year *) malloc(sizeof(struct year));
    prior = p;
    p = p->next;
    p->prior = prior;
    while (schP) {
        /*当计划表的年份为指定年份，并且在一定时间段内，那么就可以添加到改年份的计划表格中*/
        if (strstr(schP->CSNo, nianfen) && strcmp(startTime, schP->startTime) >= 0
                && strcmp(schP->finishTime, endTime) >= 0) {
            p->list[index++] = schP;
        }
        schP = schP->next;
    }
    /*最后是以NULL结尾*/
    p->list[index] = NULL;
    strcpy(p->nianfen, nianfen);
    /*下一个节点指向空*/
    p->next = NULL;
    /*记录列表长度*/
    p->length = index - 1;
    dataHandle(p);
}

/*struct year {
    char nianfen[5];
    struct schedule *list[1000];
    int length;
    struct year *next;
    struct year *prior;
    int registeredProjectNum;
    int supportedProjectNum;
    int fund;
    float supportingRate;
    float passingRate;
    float excellentRate;
    float qualifiedRate;
    float unfinishedRate;
    int studentNum;

};*/
void dataHandle(struct year *p) {
    /*遍历list中所有计划表*/
    for (int i = 0; i <= p->length; ++i) {
        /*用于遍历该计划表项目的移动指针*/
        struct project *proP = p->list[i]->projectHead->next;
        p->registeredProjectNum += p->list[i]->projectNum;
        p->supportedProjectNum += p->list[i]->realSupProNum;
        /*总的资金数*/
        p->fund += p->list[i]->fund;
        p->passingRate += p->list[i]->finishProNum;
        while (proP) {
            /*此处应该添加判断，当前项目是支持的项目时才有效*/
            if (proP->isSupported) {
                if (strstr(proP->judgement, "优")) {
                    p->excellentRate += 1;
                    p->qualifiedRate += 1;
                } else if (strstr(proP->judgement, "良")) {
                    p->qualifiedRate += 1;
                } else if (strstr(proP->judgement, "未能正常结题")) {
                    p->unfinishedRate += 1;
                }
                p->studentNum += proP->member;
                proP = proP->next;
            }
        }
    }
    /*我认为支持率应该是 支持项目数 / 所有报名的项目数*/
    p->supportingRate = p->supportedProjectNum / p->registeredProjectNum;
    /*我认为优秀率应该是优秀的项目数 / 通过的项目数*/
    p->excellentRate = p->excellentRate / p->passingRate;
    /*我认为合格率是合格的项目数 / 通过的项目数*/
    p->qualifiedRate = p->qualifiedRate / p->passingRate;
    /*我认为通过率应该是 通过的项目数 / 实际支持的项目数*/
    p->passingRate = p->passingRate / p->supportedProjectNum;
    /*我认为未结题率应该是 未完成的项目数 / 实际支持的项目数*/
    p->unfinishedRate = p->unfinishedRate / p->supportedProjectNum;
}

