#include "total.h"

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
    daTa->passingRate = p->finishProNum;
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




/*排序*/
void sortData(struct data **collectionData, struct schedule **collectionSch) {
    int way = -1;
    printf("请输入你要选择的排序方式（1.支持项目数2.通过率3.资金数4.支持率)\n");
    scanf("%d", &way);
    switch  (way) {
        case 1:
            sortDataBySupportedNum(collectionData, collectionSch);
            break;
        case 2:
            sortDataByPassingRate(collectionData, collectionSch);
            break;
        case 3:
            sortDataByFund(collectionData, collectionSch);
            break;
        case 4:
            sortDataBySupportingRate(collectionData, collectionSch);
            break;
        default:
            break;
    }
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

/*打印数据*/
/*  int registeredProjectNum;
    int supportedProjectNum;
    float fund;
    float supportingRate;
    float passingRate;
    float excellentRate;
    float qualifiedRate;
    float unfinishedRate;
    int studentNum;*/
void printData(struct data *p) {
    FILE *data = fopen("H:/data/data_keshe_baobiao.dat", "a+");
    fprintf(data, "%-10s%-12d%-12d%-10.4f%-12.4f%-12.4f%-10.4f%-10.4f%-12.4f%-12d\n", p->scheduleNo, p->registeredProjectNum, p->supportedProjectNum,
        p->fund, p->supportingRate, p->passingRate, p->excellentRate, p->qualifiedRate, p->unfinishedRate, p->studentNum);
    fprintf(stdout, "%-10s%-12d%-12d%-10.4f%-12.4f%-12.4f%-10.4f%-10.4f%-12.4f%-12d\n", p->scheduleNo, p->registeredProjectNum, p->supportedProjectNum,
            p->fund, p->supportingRate, p->passingRate, p->excellentRate, p->qualifiedRate, p->unfinishedRate, p->studentNum);
    fclose(data);
}


/*打印data容器*/
void printDataCollection(struct data **collection) {
    int index = 0;
    FILE *data = fopen("H:/data/data_keshe_baobiao.dat", "a+");
    char title[10][15] = {"项目编号", "申报项目数", "支持项目数", "资金数", "项目支持率", "验收通过率", "优秀率", "合格率", "未结题率", "学生数"};
    fprintf(data, "%-10s%-12s%-12s%-10s%-12s%-12s%-10s%-10s%-12s%-12s\n", title[0], title[1], title[2], title[3], title[4],
        title[5], title[6], title[7], title[8], title[9]);
    fprintf(stdout, "%-10s%-12s%-12s%-10s%-12s%-12s%-10s%-10s%-12s%-12s\n", title[0], title[1], title[2], title[3], title[4],
                   title[5], title[6], title[7], title[8], title[9]);;
    for (; collection[index]; index++) {
        printData(collection[index]);
    }
    printf("\n");
}

