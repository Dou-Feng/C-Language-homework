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
    /*��ӵ�����β��ͷָ�벻������ݣ�ʹ��ÿ���ڵ㶼����ǰһ���ڵ�ָ����������֮������������Ԫ�ؽ���*/
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
        /*���ƻ�������Ϊָ����ݣ�������һ��ʱ����ڣ���ô�Ϳ�����ӵ�����ݵļƻ������*/
        if (strstr(schP->CSNo, nianfen) && strcmp(startTime, schP->startTime) >= 0
                && strcmp(schP->finishTime, endTime) >= 0) {
            p->list[index++] = schP;
        }
        schP = schP->next;
    }
    /*�������NULL��β*/
    p->list[index] = NULL;
    strcpy(p->nianfen, nianfen);
    /*��һ���ڵ�ָ���*/
    p->next = NULL;
    /*��¼�б���*/
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
    /*����list�����мƻ���*/
    for (int i = 0; i <= p->length; ++i) {
        /*���ڱ����üƻ�����Ŀ���ƶ�ָ��*/
        struct project *proP = p->list[i]->projectHead->next;
        p->registeredProjectNum += p->list[i]->projectNum;
        p->supportedProjectNum += p->list[i]->realSupProNum;
        /*�ܵ��ʽ���*/
        p->fund += p->list[i]->fund;
        p->passingRate += p->list[i]->finishProNum;
        while (proP) {
            /*�˴�Ӧ������жϣ���ǰ��Ŀ��֧�ֵ���Ŀʱ����Ч*/
            if (proP->isSupported) {
                if (strstr(proP->judgement, "��")) {
                    p->excellentRate += 1;
                    p->qualifiedRate += 1;
                } else if (strstr(proP->judgement, "��")) {
                    p->qualifiedRate += 1;
                } else if (strstr(proP->judgement, "δ����������")) {
                    p->unfinishedRate += 1;
                }
                p->studentNum += proP->member;
                proP = proP->next;
            }
        }
    }
    /*����Ϊ֧����Ӧ���� ֧����Ŀ�� / ���б�������Ŀ��*/
    p->supportingRate = p->supportedProjectNum / p->registeredProjectNum;
    /*����Ϊ������Ӧ�����������Ŀ�� / ͨ������Ŀ��*/
    p->excellentRate = p->excellentRate / p->passingRate;
    /*����Ϊ�ϸ����Ǻϸ����Ŀ�� / ͨ������Ŀ��*/
    p->qualifiedRate = p->qualifiedRate / p->passingRate;
    /*����Ϊͨ����Ӧ���� ͨ������Ŀ�� / ʵ��֧�ֵ���Ŀ��*/
    p->passingRate = p->passingRate / p->supportedProjectNum;
    /*����Ϊδ������Ӧ���� δ��ɵ���Ŀ�� / ʵ��֧�ֵ���Ŀ��*/
    p->unfinishedRate = p->unfinishedRate / p->supportedProjectNum;
}

