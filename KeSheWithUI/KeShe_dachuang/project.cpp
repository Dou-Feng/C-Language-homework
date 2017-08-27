//
// Created by Famine on 2017/7/2.
//

#include <malloc.h>
#include <stdio.h>
#include "project.h"

/*������Ŀ����
�÷���
	���룺��
	�������Ŀ������ͷָ��*/
struct project *createProject() {
    struct project *head = (struct project *) malloc(sizeof(struct project));
    struct project *tail;
    tail = head;
    tail->next = NULL;
    head->prior = NULL;
    return head;
}


/*������Ŀ����
�÷���
	���룺��Ŀ����ͷָ�룬�ļ�ָ��
	�������
*/
void addProject(struct project *head, FILE *data) {
    /*���ӵ�����β��ͷָ�벻������ݣ�ʹ��ÿ���ڵ㶼����ǰһ���ڵ�ָ����������֮������������Ԫ�ؽ���*/
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
    int way = 1;
    p->member = 0;
    printf("��ѡ���������ݵķ�ʽ\n"
                   "1.���ļ�����\n"
                   "2.�Ӽ�������\n");
    scanf("%d", &way);
    switch (way) {
        case 1:
            /*���뷽ʽһ���ļ�����*/
            fscanf(data, "%s%s%f%d%s%s%s%s%s%s%s", p->CNo, p->proName, &p->money, &p->isSupported,
                p->startTime, p->finishTime, p->judgement, p->leadMan, p->leadPhoneNum,
                p->productForm, p->productName);
            break;
        case 2:
            /*���뷽ʽ������������*/
            printf("������һϵ�����ݣ��ֱ�Ϊ��\n"
                           " * ��Ŀ���\n"
                           " * ��Ŀ����\n"
                           " * ������\n"
                           " * �Ƿ�֧�֣�����1(֧��)/0����֧��)\n"
                           " * ����ʱ��\n"
                           " * ����ʱ��\n"
                           " * �������\n"
                           " * ������\n"
                           " * �����˵绰\n"
                           " * �ɹ���ʽ\n"
                           " * �ɹ�����\n");
            fscanf(stdin, "%s%s%f%d%s%s%s%s%s%s%s", p->CNo, p->proName, &p->money, &p->isSupported,
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

/*ˢ������������
������Ա����Ӧ���Ǻ���Ա���Ľڵ���������ģ�����ÿ����Ա֮��Ӧ�õ��ôκ���
�÷���	
	���룺��Ŀ�Ľڵ�ָ��
	�������*/
void refreshProList(struct project *p) {
    p->member = 0;
    struct people *people1 = p->peopleHead->next;
    while (people1) {
        p->member++;
        people1 = people1->next;
    }
}

/*������Ŀ
��װ�˺ܶ��ѯ����
�÷���
	���룺��Ŀ����ͷָ��
	�������*/
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
            printf("������ɹ����ͣ�1�������� 2�����ģ� 3����Ʒ�� 4��������\n");
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
            printf("������ɹ����ͣ�1�������� 2�����ģ� 3����Ʒ�� 4��������\n");
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

/*ͨ����Ŀ���Ʋ�����Ŀ�����ҵ�����һ����Ŀָ������
�÷���
	���룺��Ŀ���飬��Ŀͷָ�룬�ؼ���
	����������Ŀ����*/
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

/*ͨ���ʽ������Ŀ�����ҵ�����һ����Ŀָ������
�÷���
���룺��Ŀ���飬��Ŀͷָ�룬�ʽ����ֵ���ʽ���Сֵ
����������Ŀ����*/
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

/*ͨ���������۲�����Ŀ�����ҵ�����һ����Ŀָ������
�÷���
���룺��Ŀ���飬��Ŀͷָ�룬�ؼ���
����������Ŀ����*/
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


/*ͨ����Ʒ��ʽ������Ŀ�����ҵ�����һ����Ŀָ������
�÷���
���룺��Ŀ���飬��Ŀͷָ�룬�ؼ���
����������Ŀ����*/
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


/*ͨ����ƽ���Ʋ�����Ŀ�����ҵ�����һ����Ŀָ������
�÷���
���룺��Ŀ���飬��Ŀͷָ�룬�ؼ���
����������Ŀ����*/
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

/*��ϲ�ѯ
�÷���
	���룺��Ŀ���飬��Ŀ����ͷָ�룬�ʽ����ֵ���ʽ���Сֵ����Ŀ���ƣ��������ۣ���Ʒ��ʽ����Ʒ����
	����������Ŀ����*/
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


/*ɾ����������װ��ɾ��ϸ�ڣ��Ȳ�ѯ��ȷ��ɾ��
�÷���
	���룺��Ŀ����ͷָ��
	�������*/
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

/*�޸���Ŀ����װ���޸�ϸ��
�÷���
	���룺��Ŀ����ͷָ��
	�������*/
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

/*�޸���Ŀϸ��
�÷���	
	���룺��Ŀ�ڵ�ָ��
	�������*/
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
                   "11.�ɹ�����\n"
                   "12.�Ƿ�֧�ָ���Ŀ������1֧�֣�0��֧�֣�\n"
                   "13.�޸���Աϸ��\n");
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
            printf("������1/0");
            scanf("%d", &tempNum);
            p->isSupported = tempNum;
        case 13:
            printPeoTable(p->peopleHead);
            modifyPeople(p->peopleHead);
        default:
            break;
    }
}



/*��ӡ��Ŀ
�÷���
	���룺��Ŀ�ڵ�ָ��
	�������ӡ��Ŀϸ��*/
void printProject(struct project *p) {
    FILE *dataOutput = fopen("H:/data/Output_project_temp.txt", "a+");
    fprintf(dataOutput, "%-10s%-40s%-10.4f%-10d%-10s%-10s%-12s%-8s%-15s%-10s%-16s\n", p->CNo, p->proName, p->money, p->member,
            p->startTime, p->finishTime, p->judgement, p->leadMan,
            p->leadPhoneNum, p->productForm, p->productName);
    fprintf(stdout, "%-10s%-40s%-10.4f%-10d%-10s%-10s%-12s%-8s%-15s%-10s%-16s\n", p->CNo, p->proName, p->money, p->member,
            p->startTime, p->finishTime, p->judgement, p->leadMan,
            p->leadPhoneNum, p->productForm, p->productName);
    fclose(dataOutput);
}


/*��ӡ��Ŀ����
�÷���
	���룺��Ŀ����ͷָ��
	�������Ŀ����ϸ����Ϣ*/
void printProTable(struct project *head) {
    /*��һ��ͷ�ڵ㲻�������*/
    struct project *p = head->next;
    FILE *dataOutput = fopen("H:/data/Output_project.txt", "a+");
    char title[12][20] = {"��Ŀ���", "��Ŀ����", "������(Ԫ)", "��������",
                          "����ʱ��", "����ʱ��", "�������", "������",
                          "�����˵绰", "�ɹ���ʽ", "�ɹ�����", "�Ƿ�֧��"};
    fprintf(dataOutput, "%-10s%-40s%-12s%-10s%-10s%-10s%-14s%-8s%-15s%-10s%-16s%-10s\n", title[0], title[1], title[2],
            title[3], title[4], title[5], title[6], title[7], title[8],title[9], title[10], title[11]);
    fprintf(stdout, "%-10s%-40s%-12s%-10s%-10s%-10s%-14s%-8s%-15s%-10s%-16s%-10s\n", title[0], title[1], title[2],
            title[3], title[4], title[5], title[6], title[7], title[8],title[9], title[10], title[11]);

    while (p) {
        char support[2][3] = {"��", "��"};
        int way = 0;
        if (p->isSupported)
            way= 1;
        fprintf(dataOutput, "%-10s%-40s%-12.2f%-10d%-10s%-10s%-14s%-8s%-15s%-10s%-16s%-10s\n", p->CNo, p->proName, p->money, p->member,
                p->startTime, p->finishTime, p->judgement, p->leadMan,
                p->leadPhoneNum, p->productForm, p->productName, support[way]);
        fprintf(stdout, "%-10s%-40s%-12.2f%-10d%-10s%-10s%-14s%-8s%-15s%-10s%-16s%-10s\n", p->CNo, p->proName, p->money, p->member,
                p->startTime, p->finishTime, p->judgement, p->leadMan,
                p->leadPhoneNum, p->productForm, p->productName, support[way]);
        p = p->next;
    }
    fclose(dataOutput);
}


/*��ӡ��Ŀ����
�÷���
	���룺��Ŀָ������*/
void printProCollection(struct project **collection) {
    for (int i = 0; collection[i]; ++i) {
        printProject(collection[i]);
    }
}

/*������Ŀ�ڵ�
�÷���
	���룺��Ŀͷָ�룬�ڵ�1��λ�ã��ڵ�2��λ��*/
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

/*����Ŀ��������
�÷���
	���룺��Ŀͷָ��
	�������*/
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