//
// Created by Famine on 2017/7/2.
//
#include <stdio.h>
#include <mem.h>
#include "schedule.h"

/*�����ƻ�����*/
struct schedule *createSchedule() {
    /*ͷָ���βָ��*/
    struct schedule *head, *tail;
    /*�����ڴ�*/
    head = (struct schedule *) malloc(sizeof(struct schedule));
    tail = head;
    /*��һ���ڵ�ָ���*/
    tail->next = NULL;
    /*ǰһ��ָ��ָΪ��*/
    tail->prior = NULL;
    return head;
    /*��ɴ���һ�������ͷ���֣��Ⱦ�����Ϊ ͷ�ڵ����ڴ���䵫�ǲ�������ݣ���һ��ָ��ָ��գ�
     * ǰһ��ָ��ָ���*/
}


/* ��Ӽƻ�����
 * ��ȱ��
 * Ͷ���ʽ�
 * ������
 * �걨��Ŀ��
 * ʵ��֧����Ŀ
 * ������Ŀ��
 * �ƻ���ʼʱ��
 * �ƻ����ʱ��
 * ������Ŀ��
 * ��Ŀ������Ϣ*/
void addSchedule(struct schedule *head, FILE *data) {
    /*��ӵ�����β��ͷָ�벻������ݣ�ʹ��ÿ���ڵ㶼����ǰһ���ڵ�ָ����������֮������������Ԫ�ؽ���*/
    struct schedule *p = head;
    struct schedule *prior;
    struct project *prop;
    /*����������β��*/
    while (p->next) {
        p = p->next;
    }
    /*�����ڴ�*/
    p->next = (struct schedule *) malloc(sizeof(struct schedule));
    /*ʹָ��ǰһ��ָ��ָ��p*/
    prior = p;
    /*���̽���p��λ��*/
    p = p->next;
    /*ʹָ��ǰһ��ָ��ָ��p��ǰһλ*/
    p->prior = prior;
    /*Ϊ�ƻ������Ŀ*/
    p->projectHead = createProject();
    /*next�ڵ�ΪNUll*/
    p->next = NULL;
    /*�ҵ�project�Ĵ�����ݵ�ͷ�ڵ�*/
    prop = p->projectHead->next;
    /*��ʽѡ��*/
    int way = 0;
    /*��ʼ��*/
    p->projectNum = 0;
    p->realSupProNum = 0;
    p->finishProNum = 0;
    printf("��ѡ���������ݵķ�ʽ\n"
                   "1.���ļ�����\n"
                   "2.�Ӽ�������\n");
    scanf("%d", &way);
    switch (way) {
        case 1:
            /*���뷽ʽһ���ļ�����*/
            fscanf(data, "%s%f%s%s%s", p->CSNo, &p->fund, p->leadMan,
                   p->startTime, p->finishTime);
            break;
        case 2:
            /*���뷽ʽ������������*/
            printf("������һϵ�����ݣ��ֱ�Ϊ��\n"
                           " * ��ȱ��\n"
                           " * Ͷ���ʽ�\n"
                           " * ������\n"
                           " * �ƻ���ʼʱ��\n"
                           " * �ƻ����ʱ��\n");
            fscanf(stdin, "%s%f%s%s%s", p->CSNo, &p->fund, p->leadMan,
                   p->startTime, p->finishTime);
            break;
        default:
            break;
    }

    sortSchedule(head);
    /*��������Ӧ���Ǵ���һ�������л�ã������ǴӼ��̻����ļ����*/
    /*��project��ͷָ�뿪ʼ���б������𽥵ĵ��������*/
    while (prop) {
        p->projectNum++;
        if (prop->isSupported)
            p->realSupProNum++;
        if (!strstr(prop->judgement, "δ����������")) {
            p->finishProNum++;
        }
        prop = prop->next;
    }
}

/*����ˢ�¼ƻ����е�����*/
/*��ÿ�θ�����Ŀ��Ϣ֮�����ˢ��*/
void refreshSchList(struct schedule *p) {
    struct project *proP = p->projectHead->next;
    p->projectNum = 0;
    p->realSupProNum = 0;
    p->finishProNum = 0;
    /*�����ƻ��е���Ŀ����*/
    while (proP) {
        p->projectNum++;
        /*����ĿΪ֧��*/
        if (proP->isSupported)
            p->realSupProNum++;
        /*����δ���������⣬�����Ŀ���Ϳ��Լ�һ*/
        if (!strstr(proP->judgement, "δ����������")) {
            p->finishProNum++;
        }
        proP = proP->next;
    }
}

/*ɾ������*/
void deleteSchedule(struct schedule *head) {
    struct schedule *collection[100];
    /*��Ϊ����ȱ��ɾ���͸�����ɾ��*/
    int way;
    char CSNoTemp[40];
    float fundTemp = 0;
    printf("����ȱ��ɾ����1\n�Ӿ���ɾ����2\n");
    scanf("%d", &way);
    switch (way) {
        case 1:
            printf("��������ȱ��\n");
            scanf("%s", CSNoTemp);
            findSchCollectionByCSNo(collection, head, CSNoTemp);
            break;
        case 2:
            printf("�����뾭��\n");
            scanf("%f", &fundTemp);
            findSchCollectionByFundMax(collection, head, fundTemp, fundTemp);
            break;
        default:
            break;
    }
    /*��ӡɾ����Ϣ�������ͷ��ڴ�*/
    for (int i = 0; collection[i]; ++i) {
        struct schedule *temp_prior;
        struct schedule *temp_next;
        printf("ɾ����Ϊ��");
        printSchedule(collection[i]);
        int configure = 0;
        printf("ȷ��ɾ��������1ȷ������0ȡ����\n");
        scanf("%d", &configure);
        if (configure) {
            temp_prior = collection[i]->prior;
            temp_next = collection[i]->next;
            temp_prior->next = temp_next;
            /*��ֹԽ�����*/
            if (temp_next)
                temp_next->prior = temp_prior;
            free(collection[i]);
        }
    }
}


/* ���Ҳ���
 * ͨ����ȱ�Ų��ң��Ժ����ң�
 * ͨ���ʽ���ң�֧�ַ�Χ���ң�
 * ͨ��֧����Ŀ���ң�֧�ַ�Χ���ң�
 * ��ϲ���*/
void findSchedule(struct schedule *head) {
    int method = 0;
    char temp_CSNo[10];
    int temp_sup[2];
    temp_sup[0] = 0;
    temp_sup[1] = 1000;
    float temp_fund[2];
    temp_fund[0] = 0;
    temp_fund[1] = 999999999;
    struct schedule *collection[100];
    collection[0] = NULL;
    printf("��������Ҫ���ҵķ�ʽ��\n"
                   "1.��ȱ�Ų���\n"
                   "2.�ʽ����\n"
                   "3.֧����Ŀ������\n"
                   "4.��ϲ���\n");
    scanf("%d", &method);
    switch (method) {
        case 1:
            printf("��������ȱ�ţ�");
            scanf("%s", temp_CSNo);
            findSchCollectionByCSNo(collection, head, temp_CSNo);
            if (collection[0]) {
                printf("���ҽ���ǣ�\n");
                printSchCollection(collection);
            } else {
                printf("û����ƥ��Ľ��\n");
            }
            break;
        case 2:
            printf("�������ʽ����Сֵ�����ֵ\n");
            printf("��Сֵ��");
            scanf("%f", &temp_fund[0]);
            printf("���ֵ��");
            scanf("%f", &temp_fund[1]);
            findSchCollectionByFundMax(collection, head, temp_fund[1], temp_fund[0]);
            if (collection[0]) {
                printf("���ҽ���ǣ�\n");
                printSchCollection(collection);
            } else {
                printf("û����ƥ��Ľ��\n");
            }
            break;
        case 3:
            printf("������֧����Ŀ������Сֵ�����ֵ\n");
            printf("��Сֵ��");
            scanf("%d", &temp_sup[0]);
            printf("���ֵ��");
            scanf("%d", &temp_sup[1]);
            findSchCollectionBySupMax(collection, head, temp_sup[1], temp_sup[0]);
            if (collection[0]) {
                printf("���ҽ���ǣ�\n");
                printSchCollection(collection);
            } else {
                printf("û����ƥ��Ľ��\n");
            }
            break;
        case 4:
            printf("��������ȱ�ţ�");
            scanf("%s", temp_CSNo);
            printf("�������ʽ����Сֵ�����ֵ\n");
            printf("��Сֵ��");
            scanf("%d", &temp_sup[0]);
            printf("���ֵ��");
            scanf("%d", &temp_sup[1]);
            printf("������֧����Ŀ������Сֵ�����ֵ\n");
            printf("��Сֵ��");
            scanf("%d", &temp_sup[0]);
            printf("���ֵ��");
            scanf("%d", &temp_sup[1]);
            findSchCollectionCombine(collection, head, temp_CSNo, temp_fund[1],
                                     temp_fund[0], temp_sup[1], temp_sup[0]);
            if (collection[0]) {
                printf("���ҽ���ǣ�\n");
                printSchCollection(collection);
            } else {
                printf("û����ƥ��Ľ��\n");
            }
            break;
        default:
            break;
    }
}


void findSchCollectionByCSNo(struct schedule **collection, struct schedule *head, char *keyword) {
    struct schedule *p = head->next;
    int index = 0;
    while (p) {
        if (strstr(p->CSNo, keyword)) {
            collection[index++] = p;
        }
        p = p->next;
    }
    collection[index] = NULL;
}


void findSchCollectionByFundMax(struct schedule **collection, struct schedule *head, float max, float min) {
    struct schedule *p = head->next;
    int index = 0;
    while (p) {
        if (p->fund >= min && p->fund <= max) {
            collection[index++] = p;
        }
        p = p->next;
    }
    collection[index] = NULL;
}

void findSchCollectionBySupMax(struct schedule **collection, struct schedule *head, int max, int min) {
    struct schedule *p = head->next;
    int index = 0;
    while (p) {
        if (p->realSupProNum >= min && p->realSupProNum <= max) {
            collection[index++] = p;
        }
        p = p->next;
    }
    collection[index] = NULL;
}

void findSchCollectionCombine(struct schedule **collection, struct schedule *head, char *keyword,
                              float f_max, float f_min, int i_max, int i_min) {
    struct schedule *p = head->next;
    int index = 0;
    while (p) {
        if (p->realSupProNum >= i_min && p->realSupProNum <= i_max &&
            p->fund >= f_min && p->fund <= f_max &&
            strstr(p->CSNo, keyword)) {
            collection[index++] = p;
        }
        p = p->next;
    }
    collection[index] = NULL;
}


/* ��ӡ�ƻ�����
 * ��ȱ��
 * Ͷ���ʽ�
 * ������
 * �걨��Ŀ��(������Ŀ������
 * ʵ��֧����Ŀ ������isSupported)
 * ������Ŀ��  (�����������ۣ�
 * �ƻ���ʼʱ��
 * �ƻ����ʱ��
 * ��Ŀ������Ϣ*/
void printSchedule(struct schedule *p) {
    FILE *dataOutput = fopen("H:/data/Output_schedule_temp.txt", "a+");
    fprintf(dataOutput, "%-12s%-12.4f%-10s%-14d%-16d%-14d%-16s%-14s\n", p->CSNo, p->fund, p->leadMan,
            p->projectNum, p->realSupProNum, p->finishProNum, p->startTime,
            p->finishTime);
    fprintf(stdout, "%-12s%-12.4f%-10s%-14d%-16d%-14d%-16s%-14s\n", p->CSNo, p->fund, p->leadMan,
            p->projectNum, p->realSupProNum, p->finishProNum, p->startTime,
            p->finishTime);
    fclose(dataOutput);
}

void printSchTable(struct schedule *head) {
    /*��һ��ͷ�ڵ㲻�������*/
    struct schedule *p = head->next;
    FILE *dataOutput = fopen("H:/data/Output_schedule.txt", "a+");
    char title[10][20] = {"��ȱ��", "Ͷ���ʽ�", "������", "�걨��Ŀ��",
                          "ʵ��֧����Ŀ", "������Ŀ��", "�ƻ���ʼʱ��", "�ƻ����ʱ��",
                          "������Ŀ��", "��Ŀ������Ϣ"};
    fprintf(dataOutput, "%-12s%-12s%-8s%-14s%-16s%-14s%-16s%-14s\n", title[0], title[1], title[2],
            title[3], title[4], title[5], title[6], title[7]);
    fprintf(stdout, "%-12s%-12s%-8s%-14s%-16s%-14s%-16s%-14s\n", title[0], title[1], title[2],
            title[3], title[4], title[5], title[6], title[7]);
    while (p) {
        fprintf(dataOutput, "%-12s%-12.4f%-8s%-14d%-16d%-14d%-16s%-14s\n", p->CSNo, p->fund, p->leadMan,
                p->projectNum, p->realSupProNum, p->finishProNum, p->startTime,
                p->finishTime);
        fprintf(stdout, "%-12s%-12.4f%-8s%-14d%-16d%-14d%-16s%-14s\n", p->CSNo, p->fund, p->leadMan,
                p->projectNum, p->realSupProNum, p->finishProNum, p->startTime,
                p->finishTime);
        p = p->next;
    }
    fclose(dataOutput);
}

/*�����ƻ�������*/
void printSchCollection(struct schedule **pSchedule) {
    for (int i = 0; pSchedule[i]; ++i) {
        printSchedule(pSchedule[i]);
    }
}


/*�޸Ĳ���*/
void modifySchedule(struct schedule *head) {
    struct schedule *collection[100];
    char temp_CSNo[10];
    printf("��������Ҫ�޸ĵļƻ������ȱ�ţ�\n");
    scanf("%s", temp_CSNo);
    findSchCollectionByCSNo(collection, head, temp_CSNo);
    for (int i = 0; collection[i]; ++i) {
        /*������Ҫ�޸ĵļƻ���*/
        printf("��ǰ�����ļƻ���Ϊ��\n");
        printSchedule(collection[i]);
        modifyDetailSchedule(collection[i]);
    }
    /*�޸���֮��Ӧ������*/
    sortSchedule(head);
}

void modifyDetailSchedule(struct schedule *p) {
    /*�ж�p�Ƿ�Ϊ��*/
    if (!p) {
        printf("�޸ĵļƻ���Ϊ�գ���\n");
        return;
    }

    int choice = 0;
    int tempNum = 0;
    float tempFloat = 0;
    char tempString[40];
    printf("��������Ҫ�޸������ţ�\n"
                   " 1 ��ȱ��\n"
                   " 2 Ͷ���ʽ�\n"
                   " 3 ������\n"
                   " 4 �걨��Ŀ��\n"
                   " 5 ʵ��֧����Ŀ��\n"
                   " 6 ������Ŀ��\n"
                   " 7 �ƻ���ʼʱ��\n"
                   " 8 �ƻ����ʱ��\n"
                   " 9 ��Ŀ������Ϣ\n"
                   "(input enter to continue)\n");
    scanf("%d", &choice);
    switch (choice) {
        case 1:
            printf("��������Ҫ�µ���ȱ�ţ�\n");
            scanf("%s", tempString);
            strcpy(p->CSNo, tempString);
            break;
        case 2:
            printf("�������µ�Ͷ���ʽ�\n");
            scanf("%f", &tempFloat);
            p->fund = tempFloat;
            break;
        case 3:
            printf("�������µĸ����ˣ�\n");
            scanf("%s", tempString);
            strcpy(p->leadMan, tempString);
            break;
        case 4:
            printf("�������µ��걨��Ŀ����\n");
            scanf("%d", &tempNum);
            p->projectNum = tempNum;
            break;
        case 5:
            printf("�������µ�ʵ��֧����Ŀ����\n");
            scanf("%d", &tempNum);
            p->realSupProNum = tempNum;
            break;
        case 6:
            printf("�������µĽ�����Ŀ����\n");
            scanf("%d", &tempNum);
            p->finishProNum = tempNum;
            break;
        case 7:
            printf("�������µļƻ���ʼʱ�䣺\n");
            scanf("%s", tempString);
            strcpy(p->startTime, tempString);
            break;
        case 8:
            printf("�������µļƻ�����ʱ�䣺\n");
            scanf("%s", tempString);
            strcpy(p->finishTime, tempString);
            break;
            case 9:
                //*��Ŀ�����޸�*//*
            printProTable(p->projectHead);
            modifyProject(p->projectHead);
        default:
            break;
    }
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

void sortSchedule(struct schedule *head) {
    int length = 0;
    struct schedule *p = head->next;
    while (p != NULL) {
        length++;
        p = p->next;
    }
    p = head->next;
    char temp_CSNo[length][16];
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