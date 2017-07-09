//
// Created by Famine on 2017/7/2.
//

#include "people.h"
#include <malloc.h>

struct people *createPeople() {
    struct people *head, *tail;
    head = (struct people *) malloc(sizeof(struct people));
    tail = head;
    tail->next = NULL;
    tail->prior = NULL;
    return head;
}

/*ѧ��
����
����
���
ѧԺ��רҵ
�༶
�����س�
�е�����
��ϵ�绰
��Ŀ��Ա����
*/
void addPeople(struct people *head, FILE *data) {
/*��ӵ�����β��ͷָ�벻������ݣ�ʹ��ÿ���ڵ㶼����ǰһ���ڵ�ָ����������֮������������Ԫ�ؽ���*/
    struct people *p = head;
    struct people *prior;
    while (p->next) {
        p = p->next;
    }
    p->next = (struct people *) malloc(sizeof(struct people));
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
            fscanf(data, "%s%s%d%s%s%s%s%s%s%d", p->SNo,p->name, &p->age, p->grade, p->collegeAndMajor,
                   p->class, p->speciality, p->undertakeTask, p->phoneNum, &p->rank);
            break;
        case 2:
            /*���뷽ʽ������������*/
            printf("������һϵ�����ݣ��ֱ�Ϊ��\n"
                           "ѧ��\n"
                           "����\n"
                           "����\n"
                           "���\n"
                           "ѧԺ��רҵ\n"
                           "�༶\n"
                           "�����س�\n"
                           "�е�����\n"
                           "��ϵ�绰\n"
                           "��Ŀ��Ա����\n");
            fscanf(stdin, "%s%s%d%s%s%s%s%s%s%d", p->SNo,p->name, &p->age, p->grade, p->collegeAndMajor,
                   p->class, p->speciality, p->undertakeTask, p->phoneNum, &p->rank);
            break;
        default:
            break;
    }
    /*next�ڵ�ΪNUll*/
    p->next = NULL;
    sortPeople(head);
}


/*�ɰ���ѧ�������� Ժϵרҵ�� �س����е������ 4 �ֽ��в�ѯ��
���У��������� Ժϵרҵ�� �س����е����񶼿ɽ���ģ����ѯ��*/
void findPeople(struct people *head) {
    int method = 0;
    char temp_String[40];
    char temp_string1[40];
    char temp_string2[40];
    char temp_string3[40];
    struct people *p = head->next;
    int index = 0;
    struct people *collection[100];
    collection[0] = NULL;
    printf("��������Ҫ���ҵķ�ʽ��\n"
                   "1.ѧ������\n"
                   "2.Ժϵרҵ\n"
                   "3.�س�\n"
                   "4.�е�����\n"
                   "5.��ϲ���\n");
    scanf("%d", &method);
    switch (method) {
        case 1:
            printf("������ѧ��������");
            scanf("%s", temp_String);
            findPeopleByName(collection, head, temp_String);
            if (collection[0]) {
                printf("���ҽ���ǣ�\n");
                printPeoCollection(collection);
            } else {
                printf("û����ƥ��Ľ��\n");
            }
            break;
        case 2:
            printf("������Ժϵרҵ\n");
            scanf("%s", p->collegeAndMajor);
            while (p) {
                if (strstr(p->collegeAndMajor, temp_String)) {
                    collection[index++] = p;
                }
                p = p->next;
            }
            collection[index] = NULL;
            if (collection[0]) {
                printf("���ҽ���ǣ�\n");
                printPeoCollection(collection);
            } else {
                printf("û����ƥ��Ľ��\n");
            }
            break;
        case 3:
            printf("�������س�\n");
            scanf("%s", temp_String);
            while (p) {
                if (strstr(p->speciality, temp_String)) {
                    collection[index++] = p;
                }
                p = p->next;
            }
            collection[index] = NULL;
            if (collection[0]) {
                printf("���ҽ���ǣ�\n");
                printPeoCollection(collection);
            } else {
                printf("û����ƥ��Ľ��\n");
            }
            break;
        case 4:
            printf("������е�����\n");
            scanf("%s", temp_String);
            while (p) {
                if (strstr(p->undertakeTask, temp_String)) {
                    collection[index++] = p;
                }
                p = p->next;
            }
            collection[index] = NULL;
            if (collection[0]) {
                printf("���ҽ���ǣ�\n");
                printPeoCollection(collection);
            } else {
                printf("û����ƥ��Ľ��\n");
            }
            break;
        case 5:
            printf("������ѧ��������");
            scanf("%s", temp_String);
            printf("������Ժϵרҵ\n");
            scanf("%s", temp_string1);
            printf("�������س�\n");
            scanf("%s", temp_string2);
            printf("������е�����\n");
            scanf("%s", temp_string3);
            while (p) {
                if (strstr(p->name, temp_String) && strstr(p->collegeAndMajor, temp_string1)
                        && strstr(p->speciality, temp_string2) && strstr(p->undertakeTask, temp_string3)) {
                    collection[index++] = p;
                }
                p = p->next;
            }
            collection[index] = NULL;
            if (collection[0]) {
                printf("���ҽ���ǣ�\n");
                printPeoCollection(collection);
            } else {
                printf("û����ƥ��Ľ��\n");
            }
            break;
        default:
            break;
    }
}

void findPeopleByName(struct people **collection, struct people *head, char *keyword) {
    int index = 0;
    struct people *p = head->next;
    while (p) {
        if (strstr(p->name, keyword)) {
            collection[index++] = p;
        }
        p = p->next;
        collection[index] = NULL;
    }
}

void findPeopleBySpe(struct people **collection, struct people *head, char *keyword) {
    int index = 0;
    struct people *p = head->next;
    while (p) {
        if (strstr(p->speciality, keyword)) {
            collection[index++] = p;
        }
        p = p->next;
        collection[index] = NULL;
    }
}

void deletePeople(struct people *head) {
    struct people *collection[100];
    /*��Ϊ����ȱ��ɾ���;���ɾ��*/
    int way;
    char temp_name[40];
    printf("��Ա����ɾ����1\n�س�ɾ����2\n");
    scanf("%d", &way);
    switch (way) {
        case 1:
            printf("������ѧ�����֣�");
            scanf("%s", temp_name);
            findPeopleByName(collection, head, temp_name);
            break;
        case 2:
            printf("�������س���");
            scanf("%s", temp_name);
            findPeopleBySpe(collection, head, temp_name);
            break;
        default:
            break;
    }
    /*��ӡɾ����Ϣ�������ͷ��ڴ�*/
    for (int i = 0; collection[i]; ++i) {
        struct people *temp_prior;
        struct people *temp_next;
        printf("ɾ����Ϊ��");
        printPeople(collection[i]);
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

void modifyPeople(struct people *head) {
    struct people *collection[100];
    char temp_proName[40];
    printf("��������Ҫ�޸ĵĳ�Ա���֣�");
    scanf("%s", temp_proName);
    findPeopleByName(collection, head, temp_proName);
    for (int i = 0; collection[i]; ++i) {
        /*������Ҫ�޸ĵļƻ���*/
        printf("��ǰ��������ĿΪ��\n");
        printPeople(collection[i]);
        modifyPeopleDetail(collection[i]);
    }
    /*�޸���֮��Ӧ������*/
    sortPeople(head);
}

void modifyPeopleDetail(struct people *p) {
    /*�ж�p�Ƿ�Ϊ��*/
    if (!p) {
        printf("�޸ĵ���ĿΪ�գ���\n");
        return;
    }

    int choice = 0;
    int tempNum = 0;
    char tempString[40];
    printf("��������Ҫ�޸������ţ�\n"
                   "1.ѧ��\n"
                   "2.����\n"
                   "3.����\n"
                   "4.���\n"
                   "5.ѧԺ��רҵ\n"
                   "6.�༶\n"
                   "7.�����س�\n"
                   "8.�е�����\n"
                   "9.��ϵ�绰\n"
                   "10.��Ŀ��Ա����\n");
    scanf("%d", &choice);
    switch (choice) {
        case 1:
            printf("��������Ҫ�µ�ѧ�ţ�\n");
            scanf("%s", tempString);
            strcpy(p->SNo, tempString);
            break;
        case 2:
            printf("�������µ�������\n");
            scanf("%s", tempString);
            strcpy(p->name, tempString);
            break;
        case 3:
            printf("�������µ����䣺\n");
            scanf("%d", &tempNum);
            p->age = tempNum;
            break;
        case 4:
            printf("�������µ����(1���������� 2���о����� 3����ʿ���� 4��ָ����ʦ)\n");
            scanf("%s", tempString);
            strcpy(p->grade, tempString);
            break;
        case 5:
            printf("�������µ�ѧԺ��רҵ��\n");
            scanf("%s", tempString);
            strcpy(p->collegeAndMajor, tempString);
            break;
        case 6:
            printf("�������µİ༶��\n");
            scanf("%s", tempString);
            strcpy(p->class, tempString);
            break;
        case 7:
            printf("�������µı����س���\n");
            scanf("%s", tempString);
            strcpy(p->speciality, tempString);
            break;
        case 8:
            printf("�������µĳе�����\n");
            scanf("%s", tempString);
            strcpy(p->undertakeTask, tempString);
            break;
        case 9:
            printf("�������µ���ϵ�绰��\n");
            scanf("%s", tempString);
            strcpy(p->phoneNum, tempString);
            break;
        case 10:
            printf("�������µ���Ŀ��Ա������\n");
            scanf("%d", &tempNum);
            p->rank = tempNum;
            break;
        default:
            break;
    }
}


void exchangePeople(struct people *head, int chg1, int chg2) {
    struct people *prior1 = head, *prior2 = head, *aftarget1, *aftarget2, *target1, *target2;
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

void sortPeople(struct people *head) {
    int length = 0;
    struct people *p = head->next;
    while (p != NULL) {
        length++;
        p = p->next;
    }
    p = head->next;
    char temp_SNo[length][16];
    for (int i = 0; i < length; ++i) {
        strcpy(temp_SNo[i], p->SNo);
        p = p->next;
    }
    char temp[16];
    for (int i = 0; i < length; ++i) {
        for (int j = i; j < length; ++j) {
            if (strcmp(temp_SNo[i], temp_SNo[j]) > 0) {
                strcpy(temp, temp_SNo[i]);
                strcpy(temp_SNo[i], temp_SNo[j]);
                strcpy(temp_SNo[j], temp);
                exchangePeople(head, i + 1, j + 1);
            }
        }
    }
}

/*ѧ��
����
����
���
ѧԺ��רҵ
�༶
�����س�
�е�����
��ϵ�绰
��Ŀ��Ա����
*/
void printPeople(struct people *p) {
    FILE *dataOutput = fopen("H:/data/Output_people_temp.txt", "a+");
    fprintf(dataOutput, "%-14s%-10s%-8d%-10s%-30s%-16s%-20s%-20s%-14s%-8d\n", p->SNo, p->name, p->age, p->grade, p->collegeAndMajor,
            p->class, p->speciality, p->undertakeTask, p->phoneNum, p->rank);
    fprintf(stdout, "%-14s%-10s%-8d%-10s%-30s%-16s%-20s%-20s%-14s%-8d\n", p->SNo, p->name, p->age, p->grade, p->collegeAndMajor,
            p->class, p->speciality, p->undertakeTask, p->phoneNum, p->rank);
    fclose(dataOutput);
}

void printPeoCollection(struct people **collection) {
    for (int i = 0; collection[i]; ++i) {
        printPeople(collection[i]);
    }
}

void printPeoTable(struct people *head) {
    /*��һ��ͷ�ڵ㲻�������*/
    struct people *p = head->next;
    FILE *dataOutput = fopen("H:/data/Output_people.txt", "a+");
    char title[10][20] = {"ѧ��", "����", "����", "���",
                          "ѧԺ��רҵ", "�༶", "�����س�",
                          "�е�����", "��ϵ�绰", "��Ŀ��Ա����"};
    fprintf(dataOutput, "%-14s%-10s%-8s%-10s%-30s%-16s%-20s%-20s%-14s%-8s\n", title[0], title[1], title[2],
            title[3], title[4], title[5], title[6], title[7], title[8],title[9]);
    fprintf(stdout, "%-14s%-10s%-8s%-10s%-30s%-16s%-20s%-20s%-14s%-8s\n", title[0], title[1], title[2],
            title[3], title[4], title[5], title[6], title[7], title[8],title[9]);

    while (p) {
        fprintf(dataOutput, "%-14s%-10s%-8d%-30s%-20s%-16s%-20s%-20s%-14s%-8d\n", p->SNo, p->name, p->age, p->grade, p->collegeAndMajor,
                p->class, p->speciality, p->undertakeTask, p->phoneNum, p->rank);
        fprintf(stdout, "%-14s%-10s%-8d%-10s%-30s%-16s%-20s%-20s%-14s%-8d\n", p->SNo, p->name, p->age, p->grade, p->collegeAndMajor,
                p->class, p->speciality, p->undertakeTask, p->phoneNum, p->rank);
        p = p->next;
    }
    fclose(dataOutput);
}

void printPeoByRank(struct people *head) {
    int rankArray[1000];
    int temp = 0;
    struct people *p = head->next;
    int index = 0;
    while (p) {
        rankArray[index++] = p->rank;
        p = p->next;
    }
    for (int i = 0; i < index; ++i) {
        for (int j = i + 1; j < index; ++j) {
            if (rankArray[i] > rankArray[j]) {
                temp = rankArray[i];
                rankArray[i] = rankArray[j];
                rankArray[j] = temp;
                exchangePeople(head, i + 1, j + 1);
            }
        }
    }
    printPeoTable(head);
    sortPeople(head);
}

