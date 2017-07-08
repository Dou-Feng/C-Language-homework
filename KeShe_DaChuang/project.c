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


/*项目编号
项目名称
经费数
参与人数
立项时间
结题时间
完成评价
负责人
负责人电话
成果形式
成果名称
*/
void addProject(struct project *head, FILE *data) {
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
    int way = 0;
    printf("请选择输入数据的方式\n"
                   "1.从文件输入\n"
                   "2.从键盘输入\n");
    scanf("%d", &way);
    switch (way) {
        case 1:
            /*导入方式一，文件导入*/
            fscanf(data, "%s%s%f%d%s%s%s%s%s%s%s", p->CNo, p->proName, &p->money, &p->member,
                p->startTime, p->finishTime, p->judgement, p->leadMan, p->leadPhoneNum,
                p->productForm, p->productName);
            break;
        case 2:
            /*导入方式二，键盘输入*/
            printf("请输入一系列数据，分别为：\n"
                           " * 项目编号\n"
                           " * 项目名称\n"
                           " * 经费数\n"
                           " * 参与人数\n"
                           " * 立项时间\n"
                           " * 结题时间\n"
                           " * 完成评价\n"
                           " * 负责人\n"
                           " * 负责人电话\n"
                           " * 成果形式\n"
                           " * 成果名称\n");
            fscanf(stdin, "%s%s%f%d%s%s%s%s%s%s%s", p->CNo, p->proName, &p->money, &p->member,
                   p->startTime, p->finishTime, p->judgement, p->leadMan, p->leadPhoneNum,
                   p->productForm, p->productName);
            break;
        default:
            break;
    }
    /*为项目创建人员表*/
    p->peopleHead = createPeople();
    /*next节点为NUll*/
    p->next = NULL;
    sortProject(head);
}



/*按项目名称、 经费数、结题评价、成果类型、成果名称等 5 种方式
进行查询。其中对项目名称、 成果名称可进行模糊查询， 经费数可进行区间查询（如
获得经费 5 万元以内的所有项目等）。同时输出参与的人员，且参与人员按照排名 1、
2、 3…的顺序依次输出。 支持组合查询。*/
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
    printf("请输入你要查找的方式：\n"
                   "1.项目名称\n"
                   "2.经费数\n"
                   "3.结题评价\n"
                   "4.成果类型\n"
                   "5.成果名称\n"
                   "6.组合查找\n");
    scanf("%d", &method);
    switch (method) {
        case 1:
            printf("请输入项目名称：");
            scanf("%s", temp_String);
            findProCollectionByProName(collection, head, temp_String);
            if (collection[0]) {
                printf("查找结果是：\n");
                for (int i = 0; collection[i]; ++i) {
                    printProject(collection[i]);
                    printf("人员信息：\n");
                    printPeoByRank(collection[i]->peopleHead);
                    printf("\n");
                }
            } else {
                printf("没有相匹配的结果\n");
            }
            break;
        case 2:
            printf("请输入经费的最小值和最大值\n");
            printf("最小值：");
            scanf("%f", &temp_fund[0]);
            printf("最大值：");
            scanf("%f", &temp_fund[1]);
            findProCollectionByMoney(collection, head, temp_fund[1], temp_fund[0]);
            if (collection[0]) {
                printf("查找结果是：\n");
                for (int i = 0; collection[i]; ++i) {
                    printProject(collection[i]);
                    printf("人员信息：\n");
                    printPeoByRank(collection[i]->peopleHead);
                    printf("\n");
                }
            } else {
                printf("没有相匹配的结果\n");
            }
            break;
        case 3:
            printf("请输入结题评价（1.优 2.良 3.中 4.差 5.未能正常解题）\n");
            scanf("%s", temp_String);
            findProCollectionByJudgement(collection, head, temp_String);
            if (collection[0]) {
                printf("查找结果是：\n");
                for (int i = 0; collection[i]; ++i) {
                    printProject(collection[i]);
                    printf("人员信息：\n");
                    printPeoByRank(collection[i]->peopleHead);
                    printf("\n");
                }
            } else {
                printf("没有相匹配的结果\n");
            }
            break;
        case 4:
            printf("请输入成果类型（1：软件， 2：论文， 3：作品， 4：其他）\n");
            scanf("%s", temp_String);
            findProCollectionByProductForm(collection, head, temp_String);
            if (collection[0]) {
                printf("查找结果是：\n");
                printProCollection(collection);
            } else {
                printf("没有相匹配的结果\n");
            }
            break;
        case 5:
            printf("请输入成果名称：");
            scanf("%s", temp_String);
            findProCollectionByProductName(collection, head, temp_String);
            if (collection[0]) {
                printf("查找结果是：\n");
                for (int i = 0; collection[i]; ++i) {
                    printProject(collection[i]);
                    printf("人员信息：\n");
                    printPeoByRank(collection[i]->peopleHead);
                    printf("\n");
                }
            } else {
                printf("没有相匹配的结果\n");
            }
            break;
        case 6:
            printf("请输入项目名称：");
            scanf("%s", temp_proName);
            printf("请输入经费的最小值和最大值\n");
            printf("最小值：");
            scanf("%f", &temp_fund[0]);
            printf("最大值：");
            scanf("%f", &temp_fund[1]);
            printf("请输入结题评价（1.优 2.良 3.中 4.差 5.未能正常解题）\n");
            scanf("%s", temp_judgement);
            printf("请输入成果类型（1：软件， 2：论文， 3：作品， 4：其他）\n");
            scanf("%s", temp_productForm);
            printf("请输入成果名称：");
            scanf("%s", temp_productName);
            findProCombine(collection, head, temp_fund[0], temp_fund[1],
                temp_proName, temp_judgement, temp_productForm, temp_productName);
            if (collection[0]) {
                printf("查找结果是：\n");
                for (int i = 0; collection[i]; ++i) {
                    printProject(collection[i]);
                    printf("人员信息：\n");
                    printPeoByRank(collection[i]->peopleHead);
                    printf("\n");
                }
            } else {
                printf("没有相匹配的结果\n");
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


/*删除操作*/
void deleteProject(struct project *head) {
    struct project *collection[100];
    /*分为从年度编号删除和经费删除*/
    int way;
    char CNoTemp[40];
    float fundTemp = 0;
    printf("按项目名称删除按1\n从经费删除按2\n");
    scanf("%d", &way);
    switch (way) {
        case 1:
            printf("请输入项目名称：");
            scanf("%s", CNoTemp);
            findProCollectionByProName(collection, head, CNoTemp);
            break;
        case 2:
            printf("请输入经费：");
            scanf("%f", &fundTemp);
            findProCollectionByMoney(collection, head, fundTemp, fundTemp);
            break;
        default:
            break;
    }
    /*打印删除信息，并且释放内存*/
    for (int i = 0; collection[i]; ++i) {
        struct project *temp_prior;
        struct project *temp_next;
        printf("删除项为：");
        printProject(collection[i]);
        int configure = 0;
        printf("确定删除？（按1确定，按0取消）\n");
        scanf("%d", &configure);
        if (configure) {
            temp_prior = collection[i]->prior;
            temp_next = collection[i]->next;
            temp_prior->next = temp_next;
            /*防止越界访问*/
            if (temp_next)
                temp_next->prior = temp_prior;
            free(collection[i]);
        }
    }
}


void modifyProject(struct project *head) {
    struct project *collection[100];
    char temp_proName[40];
    printf("请输入你要修改的项目名称：\n");
    scanf("%s", temp_proName);
    findProCollectionByProName(collection, head, temp_proName);
    for (int i = 0; collection[i]; ++i) {
        /*查找需要修改的计划表*/
        printf("当前操作的项目为：\n");
        printProject(collection[i]);
        modifyProDetail(collection[i]);
    }
    /*修改完之后应该排序*/
    sortProject(head);
}

void modifyProDetail(struct project *p) {
    /*判定p是否为空*/
    if (!p) {
        printf("修改的项目为空！！\n");
        return;
    }

    int choice = 0;
    int tempNum = 0;
    float tempFloat = 0;
    char tempString[40];
    printf("请输入你要修改项的序号：\n"
                   "1.项目编号\n"
                   "2.项目名称\n"
                   "3.经费数\n"
                   "4.参与人数\n"
                   "5.立项时间\n"
                   "6.结题时间\n"
                   "7.完成评价\n"
                   "8.负责人\n"
                   "9.负责人电话\n"
                   "10.成果形式\n"
                   "11.成果名称\n");
    scanf("%d", &choice);
    switch (choice) {
        case 1:
            printf("请输入需要新的项目编号：\n");
            scanf("%s", tempString);
            strcpy(p->CNo, tempString);
            break;
        case 2:
            printf("请输入新的项目名称：\n");
            scanf("%s", tempString);
            strcpy(p->proName, tempString);
            break;
        case 3:
            printf("请输入新的经费数：\n");
            scanf("%f", &tempFloat);
            p->money = tempFloat;
            break;
        case 4:
            printf("请输入新的参与人数：\n");
            scanf("%d", &tempNum);
            p->member = tempNum;
            break;
        case 5:
            printf("请输入新的立项时间：\n");
            scanf("%s", tempString);
            strcpy(p->startTime, tempString);
            break;
        case 6:
            printf("请输入新的结题时间：\n");
            scanf("%s", tempString);
            strcpy(p->finishTime, tempString);
            break;
        case 7:
            printf("请输入新的完成评价：\n");
            scanf("%s", tempString);
            strcpy(p->judgement, tempString);
            break;
        case 8:
            printf("请输入新的负责人：\n");
            scanf("%s", tempString);
            strcpy(p->leadMan, tempString);
            break;
        case 9:
            printf("请输入新的负责人电话：\n");
            scanf("%s", tempString);
            strcpy(p->leadPhoneNum, tempString);
            break;
        case 10:
            printf("请输入新的成果形式：\n");
            scanf("%s", tempString);
            strcpy(p->productForm, tempString);
            break;
        case 11:
            printf("请输入新的成果名称：\n");
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



/*项目编号
项目名称
经费数
参与人数
立项时间
结题时间
完成评价
负责人
负责人电话
成果形式
成果名称*/
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
    /*第一个头节点不存放数据*/
    struct project *p = head->next;
    FILE *dataOutput = fopen("H:/data/Output_project.txt", "w+");
    char title[11][20] = {"项目编号", "项目名称", "经费数", "参与人数",
                          "立项时间", "结题时间", "完成评价", "负责人",
                          "负责人电话", "成果形式", "成果名称"};
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