//
// Created by Famine on 2017/7/2.
//

#include <malloc.h>
#include <stdio.h>
#include "project.h"

struct project *createProject() {
    struct project *head = (struct project *) malloc(sizeof(struct project));
    struct project *tail;
    tail = head;
    tail->next = NULL;
    head->prior = NULL;
    return head;
}


/*��Ŀ���
��Ŀ����
������
��������
����ʱ��
����ʱ��
�������
������
�����˵绰
�ɹ���ʽ
�ɹ�����
*/
void addProject(struct project *head, FILE *data) {
    /*��ӵ�����β��ͷָ�벻������ݣ�ʹ��ÿ���ڵ㶼����ǰһ���ڵ�ָ����������֮������������Ԫ�ؽ���*/
    struct project *p = head;
    struct project *prior;
    while (p->next) {
        p = p->next;
    }
    p->next = (struct project *) malloc(sizeof(struct project));
    prior = p;
    p = p->next;
    p->prior = prior;
    /*��ʽѡ��*/
    int way = 0;
    printf("��ѡ���������ݵķ�ʽ\n"
                   "1.���ļ�����\n"
                   "2.�Ӽ�������\n");
    scanf("%d", &way);
    switch (way) {
        case 1:
            /*���뷽ʽһ���ļ�����*/
            fscanf(data, "%s%s%f%d%s%s%s%s%s%s%s", p->CNo, p->proName, &p->money, &p->member,
                p->startTime, p->finishTime, p->judgement, p->leadMan, p->leadPhoneNum,
                p->productForm, p->productName);
            break;
        case 2:
            /*���뷽ʽ������������*/
            printf("������һϵ�����ݣ��ֱ�Ϊ��\n"
                           " * ��Ŀ���\n"
                           " * ��Ŀ����\n"
                           " * ������\n"
                           " * ��������\n"
                           " * ����ʱ��\n"
                           " * ����ʱ��\n"
                           " * �������\n"
                           " * ������\n"
                           " * �����˵绰\n"
                           " * �ɹ���ʽ\n"
                           " * �ɹ�����\n");
            fscanf(stdin, "%s%s%f%d%s%s%s%s%s%s%s", p->CNo, p->proName, &p->money, &p->member,
                   p->startTime, p->finishTime, p->judgement, p->leadMan, p->leadPhoneNum,
                   p->productForm, p->productName);
            break;
        default:
            break;
    }
    /*Ϊ��Ŀ������Ա��*/
    p->peopleHead = createPeople();
    /*next�ڵ�ΪNUll*/
    p->next = NULL;
    sortProject(head);
}



/*����Ŀ���ơ� ���������������ۡ��ɹ����͡��ɹ����Ƶ� 5 �ַ�ʽ
���в�ѯ�����ж���Ŀ���ơ� �ɹ����ƿɽ���ģ����ѯ�� �������ɽ��������ѯ����
��þ��� 5 ��Ԫ���ڵ�������Ŀ�ȣ���ͬʱ����������Ա���Ҳ�����Ա�������� 1��
2�� 3����˳����������� ֧����ϲ�ѯ��*/
void findProject(struct project *head) {
    int method = 0;
    char temp_String[40];
    char temp_proName[40];
    char temp_productName[40];
    char temp_productForm[40];
    char temp_judgement[40];
    float temp_fund[2];
    temp_fund[0] = 0;
    temp_fund[1] = 999999999;
    struct project *collection[100];
    collection[0] = NULL;
    printf("��������Ҫ���ҵķ�ʽ��\n"
                   "1.��Ŀ����\n"
                   "2.������\n"
                   "3.��������\n"
                   "4.�ɹ�����\n"
                   "5.�ɹ�����\n"
                   "6.��ϲ���\n");
    scanf("%d", &method);
    switch (method) {
        case 1:
            printf("��������Ŀ���ƣ�");
            scanf("%s", temp_String);
            findProCollectionByProName(collection, head, temp_String);
            if (collection[0]) {
                printf("���ҽ���ǣ�\n");
                for (int i = 0; collection[i]; ++i) {
                    printProject(collection[i]);
                    printf("��Ա��Ϣ��\n");
                    printPeoByRank(collection[i]->peopleHead);
                    printf("\n");
                }
            } else {
                printf("û����ƥ��Ľ��\n");
            }
            break;
        case 2:
            printf("�����뾭�ѵ���Сֵ�����ֵ\n");
            printf("��Сֵ��");
            scanf("%f", &temp_fund[0]);
            printf("���ֵ��");
            scanf("%f", &temp_fund[1]);
            findProCollectionByMoney(collection, head, temp_fund[1], temp_fund[0]);
            if (collection[0]) {
                printf("���ҽ���ǣ�\n");
                for (int i = 0; collection[i]; ++i) {
                    printProject(collection[i]);
                    printf("��Ա��Ϣ��\n");
                    printPeoByRank(collection[i]->peopleHead);
                    printf("\n");
                }
            } else {
                printf("û����ƥ��Ľ��\n");
            }
            break;
        case 3:
            printf("������������ۣ�1.�� 2.�� 3.�� 4.�� 5.δ���������⣩\n");
            scanf("%s", temp_String);
            findProCollectionByJudgement(collection, head, temp_String);
            if (collection[0]) {
                printf("���ҽ���ǣ�\n");
                for (int i = 0; collection[i]; ++i) {
                    printProject(collection[i]);
                    printf("��Ա��Ϣ��\n");
                    printPeoByRank(collection[i]->peopleHead);
                    printf("\n");
                }
            } else {
                printf("û����ƥ��Ľ��\n");
            }
            break;
        case 4:
            printf("������ɹ����ͣ�1������� 2�����ģ� 3����Ʒ�� 4��������\n");
            scanf("%s", temp_String);
            findProCollectionByProductForm(collection, head, temp_String);
            if (collection[0]) {
                printf("���ҽ���ǣ�\n");
                printProCollection(collection);
            } else {
                printf("û����ƥ��Ľ��\n");
            }
            break;
        case 5:
            printf("������ɹ����ƣ�");
            scanf("%s", temp_String);
            findProCollectionByProductName(collection, head, temp_String);
            if (collection[0]) {
                printf("���ҽ���ǣ�\n");
                for (int i = 0; collection[i]; ++i) {
                    printProject(collection[i]);
                    printf("��Ա��Ϣ��\n");
                    printPeoByRank(collection[i]->peopleHead);
                    printf("\n");
                }
            } else {
                printf("û����ƥ��Ľ��\n");
            }
            break;
        case 6:
            printf("��������Ŀ���ƣ�");
            scanf("%s", temp_proName);
            printf("�����뾭�ѵ���Сֵ�����ֵ\n");
            printf("��Сֵ��");
            scanf("%f", &temp_fund[0]);
            printf("���ֵ��");
            scanf("%f", &temp_fund[1]);
            printf("������������ۣ�1.�� 2.�� 3.�� 4.�� 5.δ���������⣩\n");
            scanf("%s", temp_judgement);
            printf("������ɹ����ͣ�1������� 2�����ģ� 3����Ʒ�� 4��������\n");
            scanf("%s", temp_productForm);
            printf("������ɹ����ƣ�");
            scanf("%s", temp_productName);
            findProCombine(collection, head, temp_fund[0], temp_fund[1],
                temp_proName, temp_judgement, temp_productForm, temp_productName);
            if (collection[0]) {
                printf("���ҽ���ǣ�\n");
                for (int i = 0; collection[i]; ++i) {
                    printProject(collection[i]);
                    printf("��Ա��Ϣ��\n");
                    printPeoByRank(collection[i]->peopleHead);
                    printf("\n");
                }
            } else {
                printf("û����ƥ��Ľ��\n");
            }
            break;
        default:
            break;
    }
}

void findProCollectionByProName(struct project **collection,struct project *head, char *keyword) {
    struct project *p = head->next;
    int index = 0;
    while (p) {
        if (strstr(p->proName, keyword)) {
            collection[index++] = p;
        }
        p = p->next;
    }
    collection[index] = NULL;
}

void findProCollectionByMoney(struct project **collection, struct project *head, float max,float min) {
    struct project *p = head->next;
    int index = 0;
    while (p) {
        if (p->money >= min && p->money <= max) {
            collection[index++] = p;
        }
        p = p->next;
    }
    collection[index] = NULL;
}

void findProCollectionByJudgement(struct project **collection,struct project *head, char *keyword) {
    struct project *p = head->next;
    int index = 0;
    while (p) {
        if (strstr(p->judgement, keyword)) {
            collection[index++] = p;
        }
        p = p->next;
    }
    collection[index] = NULL;

}

void findProCollectionByProductForm(struct project **collection,struct project *head, char *keyword) {
    struct project *p = head->next;
    int index = 0;
    while (p) {
        if (strstr(p->productForm, keyword)) {
            collection[index++] = p;
        }
        p = p->next;
    }
    collection[index] = NULL;

}

void findProCollectionByProductName(struct project **collection,struct project *head, char *keyword) {
    struct project *p = head->next;
    int index = 0;
    while (p) {
        if (strstr(p->productName, keyword)) {
            collection[index++] = p;
        }
        p = p->next;
    }
    collection[index] = NULL;

}

void findProCombine(struct project **collection, struct project *head, float max, float min,
        char *proName, char *judgement, char *productForm, char *productName) {
    struct project *p = head->next;
    int index = 0;
    while (p) {
        if (strstr(p->productName, productName) && strstr(p->productForm, productForm) &&
                strstr(p->judgement, judgement) && p->money >= min && p->money <= max &&
                strstr(p->proName, proName)) {
            collection[index++] = p;
        }
        p = p->next;
    }
    collection[index] = NULL;
}


/*ɾ������*/
void deleteProject(struct project *head) {
    struct project *collection[100];
    /*��Ϊ����ȱ��ɾ���;���ɾ��*/
    int way;
    char CNoTemp[40];
    float fundTemp = 0;
    printf("����Ŀ����ɾ����1\n�Ӿ���ɾ����2\n");
    scanf("%d", &way);
    switch (way) {
        case 1:
            printf("��������Ŀ���ƣ�");
            scanf("%s", CNoTemp);
            findProCollectionByProName(collection, head, CNoTemp);
            break;
        case 2:
            printf("�����뾭�ѣ�");
            scanf("%f", &fundTemp);
            findProCollectionByMoney(collection, head, fundTemp, fundTemp);
            break;
        default:
            break;
    }
    /*��ӡɾ����Ϣ�������ͷ��ڴ�*/
    for (int i = 0; collection[i]; ++i) {
        struct project *temp_prior;
        struct project *temp_next;
        printf("ɾ����Ϊ��");
        printProject(collection[i]);
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


void modifyProject(struct project *head) {
    struct project *collection[100];
    char temp_proName[40];
    printf("��������Ҫ�޸ĵ���Ŀ���ƣ�\n");
    scanf("%s", temp_proName);
    findProCollectionByProName(collection, head, temp_proName);
    for (int i = 0; collection[i]; ++i) {
        /*������Ҫ�޸ĵļƻ���*/
        printf("��ǰ��������ĿΪ��\n");
        printProject(collection[i]);
        modifyProDetail(collection[i]);
    }
    /*�޸���֮��Ӧ������*/
    sortProject(head);
}

void modifyProDetail(struct project *p) {
    /*�ж�p�Ƿ�Ϊ��*/
    if (!p) {
        printf("�޸ĵ���ĿΪ�գ���\n");
        return;
    }

    int choice = 0;
    int tempNum = 0;
    float tempFloat = 0;
    char tempString[40];
    printf("��������Ҫ�޸������ţ�\n"
                   "1.��Ŀ���\n"
                   "2.��Ŀ����\n"
                   "3.������\n"
                   "4.��������\n"
                   "5.����ʱ��\n"
                   "6.����ʱ��\n"
                   "7.�������\n"
                   "8.������\n"
                   "9.�����˵绰\n"
                   "10.�ɹ���ʽ\n"
                   "11.�ɹ�����\n");
    scanf("%d", &choice);
    switch (choice) {
        case 1:
            printf("��������Ҫ�µ���Ŀ��ţ�\n");
            scanf("%s", tempString);
            strcpy(p->CNo, tempString);
            break;
        case 2:
            printf("�������µ���Ŀ���ƣ�\n");
            scanf("%s", tempString);
            strcpy(p->proName, tempString);
            break;
        case 3:
            printf("�������µľ�������\n");
            scanf("%f", &tempFloat);
            p->money = tempFloat;
            break;
        case 4:
            printf("�������µĲ���������\n");
            scanf("%d", &tempNum);
            p->member = tempNum;
            break;
        case 5:
            printf("�������µ�����ʱ�䣺\n");
            scanf("%s", tempString);
            strcpy(p->startTime, tempString);
            break;
        case 6:
            printf("�������µĽ���ʱ�䣺\n");
            scanf("%s", tempString);
            strcpy(p->finishTime, tempString);
            break;
        case 7:
            printf("�������µ�������ۣ�\n");
            scanf("%s", tempString);
            strcpy(p->judgement, tempString);
            break;
        case 8:
            printf("�������µĸ����ˣ�\n");
            scanf("%s", tempString);
            strcpy(p->leadMan, tempString);
            break;
        case 9:
            printf("�������µĸ����˵绰��\n");
            scanf("%s", tempString);
            strcpy(p->leadPhoneNum, tempString);
            break;
        case 10:
            printf("�������µĳɹ���ʽ��\n");
            scanf("%s", tempString);
            strcpy(p->productForm, tempString);
            break;
        case 11:
            printf("�������µĳɹ����ƣ�\n");
            scanf("%s", tempString);
            strcpy(p->productName, tempString);
            break;
            case 12:
            printPeoTable(p->peopleHead);
            modifyPeople(p->peopleHead);
        default:
            break;
    }
}



/*��Ŀ���
��Ŀ����
������
��������
����ʱ��
����ʱ��
�������
������
�����˵绰
�ɹ���ʽ
�ɹ�����*/
void printProject(struct project *p) {
    FILE *dataOutput = fopen("H:/data/Output_project.txt", "w+");
    fprintf(dataOutput, "%-10s%-40s%-10.4f%-10d%-10s%-10s%-8s%-8s%-15s%-10s%-16s\n", p->CNo, p->proName, p->money, p->member,
            p->startTime, p->finishTime, p->judgement, p->leadMan,
            p->leadPhoneNum, p->productForm, p->productName);
    fprintf(stdout, "%-10s%-40s%-10.4f%-10d%-10s%-10s%-8s%-8s%-15s%-10s%-16s\n", p->CNo, p->proName, p->money, p->member,
            p->startTime, p->finishTime, p->judgement, p->leadMan,
            p->leadPhoneNum, p->productForm, p->productName);
    fclose(dataOutput);
}

void printProTable(struct project *head) {
    /*��һ��ͷ�ڵ㲻�������*/
    struct project *p = head->next;
    FILE *dataOutput = fopen("H:/data/Output_project.txt", "w+");
    char title[11][20] = {"��Ŀ���", "��Ŀ����", "������", "��������",
                          "����ʱ��", "����ʱ��", "�������", "������",
                          "�����˵绰", "�ɹ���ʽ", "�ɹ�����"};
    fprintf(dataOutput, "%-10s%-40s%-10s%-10s%-10s%-10s%-10s%-8s%-15s%-10s%-16s\n", title[0], title[1], title[2],
            title[3], title[4], title[5], title[6], title[7], title[8],title[9], title[10]);
    fprintf(stdout, "%-10s%-40s%-10s%-10s%-10s%-10s%-10s%-8s%-15s%-10s%-16s\n", title[0], title[1], title[2],
            title[3], title[4], title[5], title[6], title[7], title[8],title[9], title[10]);

    while (p) {
        fprintf(dataOutput, "%-10s%-40s%-10.4f%-10d%-10s%-10s%-10s%-8s%-15s%-10s%-16s\n", p->CNo, p->proName, p->money, p->member,
                p->startTime, p->finishTime, p->judgement, p->leadMan,
                p->leadPhoneNum, p->productForm, p->productName);
        fprintf(stdout, "%-10s%-40s%-10.4f%-10d%-10s%-10s%-10s%-8s%-15s%-10s%-16s\n", p->CNo, p->proName, p->money, p->member,
                p->startTime, p->finishTime, p->judgement, p->leadMan,
                p->leadPhoneNum, p->productForm, p->productName);
        p = p->next;
    }
    fclose(dataOutput);
}

void printProCollection(struct project **collection) {
    for (int i = 0; collection[i]; ++i) {
        printProject(collection[i]);
    }
}

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

void sortProject(struct project *head) {
    int length = 0;
    struct project *p = head->next;
    while (p != NULL) {
        length++;
        p = p->next;
    }
    p = head->next;
    char temp_CNo[length][16];
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