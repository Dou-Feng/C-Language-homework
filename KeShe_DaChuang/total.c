#include "total.h"

/*���schedule������*/
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

/*��schedule�е����ݽ�������浽data��*/
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
        if (strstr(project_p->judgement, "��")) {
            daTa->excellentRate += 1;
            daTa->qualifiedRate += 1;
        }
        else if (strstr(project_p->judgement, "��")) {
            daTa->qualifiedRate += 1;
        }
        else if (strstr(project_p->judgement, "δ����������")) {
            daTa->unfinishedRate += 1;
        }
        project_p = project_p->next;
    }
    /*����Ϊ֧����Ӧ���� ֧����Ŀ�� / ���б�������Ŀ��*/
    daTa->supportingRate = (float) daTa->supportedProjectNum / daTa->registeredProjectNum;
    if (daTa->supportedProjectNum) {
            /*����Ϊ������Ӧ�����������Ŀ�� / ʵ��֧�ֵ���Ŀ��*/
            daTa->excellentRate = daTa->excellentRate / daTa->supportedProjectNum;
            /*����Ϊ�ϸ����Ǻϸ����Ŀ�� / ʵ��֧�ֵ���Ŀ��*/
            daTa->qualifiedRate = daTa->qualifiedRate / daTa->supportedProjectNum;
            /*����Ϊͨ����Ӧ���� ͨ������Ŀ�� / ʵ��֧�ֵ���Ŀ��*/
            daTa->passingRate = daTa->passingRate / daTa->supportedProjectNum;
            /*����Ϊδ������Ӧ���� δ��ɵ���Ŀ�� / ʵ��֧�ֵ���Ŀ��*/
            daTa->unfinishedRate = daTa->unfinishedRate / daTa->supportedProjectNum;
    }
    return daTa;
}


/*���data����*/
void fullDataCollection(struct data **collectionData, struct schedule **collectionSch) {
    int index;
    for (index = 0; collectionSch[index]; ++index) {
        collectionData[index] = getSchData(collectionSch[index]);
    }
    collectionData[index] = NULL;
}




/*����*/
void sortData(struct data **collectionData, struct schedule **collectionSch) {
    int way = -1;
    printf("��������Ҫѡ�������ʽ��1.֧����Ŀ��2.ͨ����3.�ʽ���4.֧����)\n");
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
 /* 1.ͨ��������*/
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
/*2.֧��������*/
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
/*3.�ʽ�����*/
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
/*֧��������*/
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

/*��ӡ����*/
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


/*��ӡdata����*/
void printDataCollection(struct data **collection) {
    int index = 0;
    FILE *data = fopen("H:/data/data_keshe_baobiao.dat", "a+");
    char title[10][15] = {"��Ŀ���", "�걨��Ŀ��", "֧����Ŀ��", "�ʽ���", "��Ŀ֧����", "����ͨ����", "������", "�ϸ���", "δ������", "ѧ����"};
    fprintf(data, "%-10s%-12s%-12s%-10s%-12s%-12s%-10s%-10s%-12s%-12s\n", title[0], title[1], title[2], title[3], title[4],
        title[5], title[6], title[7], title[8], title[9]);
    fprintf(stdout, "%-10s%-12s%-12s%-10s%-12s%-12s%-10s%-10s%-12s%-12s\n", title[0], title[1], title[2], title[3], title[4],
                   title[5], title[6], title[7], title[8], title[9]);;
    for (; collection[index]; index++) {
        printData(collection[index]);
    }
    printf("\n");
}

