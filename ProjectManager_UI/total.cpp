#include "total.h"
#include <stdio.h>

/*填充schedule的容器*/
void getInTimeSch(struct schedule **collection, struct schedule *head, char *startTime, char *finishTime) {
    struct schedule *p = head->next;
    int index = 0;
    while (p) {
        if (strcmp(startTime, p->startTime) <= 0 && strcmp(finishTime, p->finishTime) >= 0) {
            collection[index++] = p;
        }
        p = p->next;
    }
    collection[index] = NULL;
}

/*把schedule中的数据进过处理存到data中*/
struct data *getSchData(struct schedule *p) {
    struct data *daTa = (struct data *) malloc(sizeof(struct data));
    memset(daTa, 0, sizeof(struct data));
    struct project *project_p = p->projectHead->next;
    strcpy(daTa->scheduleNo, p->CSNo);
    daTa->registeredProjectNum = p->projectNum;
    daTa->fund = p->fund;
    daTa->supportedProjectNum = p->realSupProNum;
    daTa->passingRate = (float) p->finishProNum;
    if (daTa->registeredProjectNum == 0)
        return daTa;
    while (project_p) {
        daTa->studentNum += project_p->member;
        if (strstr(project_p->judgement, "优")) {
            daTa->excellentRate += 1;
            daTa->qualifiedRate += 1;
        }
        else if (strstr(project_p->judgement, "良")) {
            daTa->qualifiedRate += 1;
        }
        else if (strstr(project_p->judgement, "未能正常结题")) {
            daTa->unfinishedRate += 1;
        }
        project_p = project_p->next;
    }
    /*我认为支持率应该是 支持项目数 / 所有报名的项目数*/
    daTa->supportingRate = (float) daTa->supportedProjectNum / daTa->registeredProjectNum;
    if (daTa->supportedProjectNum) {
        /*我认为优秀率应该是优秀的项目数 / 实际支持的项目数*/
        daTa->excellentRate = daTa->excellentRate / daTa->supportedProjectNum;
        /*我认为合格率是合格的项目数 / 实际支持的项目数*/
        daTa->qualifiedRate = daTa->qualifiedRate / daTa->supportedProjectNum;
        /*我认为通过率应该是 通过的项目数 / 实际支持的项目数*/
        daTa->passingRate = daTa->passingRate / daTa->supportedProjectNum;
        /*我认为未结题率应该是 未完成的项目数 / 实际支持的项目数*/
        daTa->unfinishedRate = daTa->unfinishedRate / daTa->supportedProjectNum;
    }
    return daTa;
}


/*填充data容器*/
void fullDataCollection(struct data **collectionData, struct schedule **collectionSch) {
    int index;
    for (index = 0; collectionSch[index]; ++index) {
        collectionData[index] = getSchData(collectionSch[index]);
    }
    collectionData[index] = NULL;
}

/* 1.通过率排序*/
void sortDataByPassingRate(struct data **collectionData, struct schedule **collectionSch) {
    struct data *temp_data;
    struct schedule *temp_schedule;
    int index_1, index_2;
    for (index_1 = 0; collectionSch[index_1]; index_1++) {
        for (index_2 = index_1 + 1; collectionSch[index_2]; index_2++) {
            if (collectionData[index_1]->passingRate < collectionData[index_2]->passingRate) {
                temp_schedule = collectionSch[index_1];
                collectionSch[index_1] = collectionSch[index_2];
                collectionSch[index_2] = temp_schedule;
                temp_data = collectionData[index_1];
                collectionData[index_1] = collectionData[index_2];
                collectionData[index_2] = temp_data;
            }
        }
    }
}
/*2.支持数排序*/
void sortDataBySupportedNum(struct data **collectionData, struct schedule **collectionSch) {
    struct data *temp_data;
    struct schedule *temp_schedule;
    int index_1, index_2;
    for (index_1 = 0; collectionSch[index_1]; index_1++) {
        for (index_2 = index_1 + 1; collectionSch[index_2]; index_2++) {
            if (collectionData[index_1]->supportedProjectNum < collectionData[index_2]->supportedProjectNum) {
                temp_schedule = collectionSch[index_1];
                collectionSch[index_1] = collectionSch[index_2];
                collectionSch[index_2] = temp_schedule;
                temp_data = collectionData[index_1];
                collectionData[index_1] = collectionData[index_2];
                collectionData[index_2] = temp_data;
            }
        }
    }
}
/*3.资金排序*/
void sortDataByFund(struct data **collectionData, struct schedule **collectionSch) {
    struct data *temp_data;
    struct schedule *temp_schedule;
    int index_1, index_2;
    for (index_1 = 0; collectionSch[index_1]; index_1++) {
        for (index_2 = index_1 + 1; collectionSch[index_2]; index_2++) {
            if (collectionData[index_1]->fund < collectionData[index_2]->fund) {
                temp_schedule = collectionSch[index_1];
                collectionSch[index_1] = collectionSch[index_2];
                collectionSch[index_2] = temp_schedule;
                temp_data = collectionData[index_1];
                collectionData[index_1] = collectionData[index_2];
                collectionData[index_2] = temp_data;
            }
        }
    }
}

/*支持率排序*/
void sortDataBySupportingRate(struct data **collectionData, struct schedule **collectionSch) {
    struct data *temp_data;
    struct schedule *temp_schedule;
    int index_1, index_2;
    for (index_1 = 0; collectionSch[index_1]; index_1++) {
        for (index_2 = index_1 + 1; collectionSch[index_2]; index_2++) {
            if (collectionData[index_1]->supportingRate < collectionData[index_2]->supportingRate) {
                temp_schedule = collectionSch[index_1];
                collectionSch[index_1] = collectionSch[index_2];
                collectionSch[index_2] = temp_schedule;
                temp_data = collectionData[index_1];
                collectionData[index_1] = collectionData[index_2];
                collectionData[index_2] = temp_data;
            }
        }
    }
}

void sortDataByregisteredProjectNum(data **collectionData, schedule **collectionSch)
{
    struct data *temp_data;
    struct schedule *temp_schedule;
    int index_1, index_2;
    for (index_1 = 0; collectionSch[index_1]; index_1++) {
        for (index_2 = index_1 + 1; collectionSch[index_2]; index_2++) {
            if (collectionData[index_1]->registeredProjectNum < collectionData[index_2]->registeredProjectNum) {
                temp_schedule = collectionSch[index_1];
                collectionSch[index_1] = collectionSch[index_2];
                collectionSch[index_2] = temp_schedule;
                temp_data = collectionData[index_1];
                collectionData[index_1] = collectionData[index_2];
                collectionData[index_2] = temp_data;
            }
        }
    }
}
