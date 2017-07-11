//
// Created by Famine on 2017/7/2.
//
#include <stdio.h>
#include <mem.h>
#include "schedule.h"

/*创建计划链表*/
struct schedule *createSchedule() {
    /*头指针和尾指针*/
    struct schedule *head, *tail;
    /*分配内存*/
    head = (struct schedule *) malloc(sizeof(struct schedule));
    tail = head;
    /*下一个节点指向空*/
    tail->next = NULL;
    /*前一个指针指为空*/
    tail->prior = NULL;
    return head;
    /*完成创建一个链表的头部分，先决条件为 头节点有内存分配但是不存放数据，下一个指针指向空，
     * 前一个指针指向空*/
}


/* 添加计划数据
 * 年度编号
 * 投入资金
 * 负责人
 * 申报项目数
 * 实际支持项目
 * 结题项目数
 * 计划开始时间
 * 计划完结时间
 * 优秀项目数
 * 项目基本信息*/
void addSchedule(struct schedule *head, FILE *data) {
    /*添加到链表尾，头指针不存放数据，使得每个节点都会有前一个节点指向它，方便之后的链表排序和元素交换*/
    struct schedule *p = head;
    struct schedule *prior;
    struct project *prop;
    /*遍历到链表尾部*/
    while (p->next) {
        p = p->next;
    }
    /*分配内存*/
    p->next = (struct schedule *) malloc(sizeof(struct schedule));
    /*使指向前一个指针指向p*/
    prior = p;
    /*立刻进行p的位移*/
    p = p->next;
    /*使指向前一个指针指向p的前一位*/
    p->prior = prior;
    /*为计划添加项目*/
    p->projectHead = createProject();
    /*next节点为NUll*/
    p->next = NULL;
    /*找到project的存放数据的头节点*/
    prop = p->projectHead->next;
    /*方式选择*/
    int way = 0;
    /*初始化*/
    p->projectNum = 0;
    p->realSupProNum = 0;
    p->finishProNum = 0;
    printf("请选择输入数据的方式\n"
                   "1.从文件输入\n"
                   "2.从键盘输入\n");
    scanf("%d", &way);
    switch (way) {
        case 1:
            /*导入方式一，文件导入*/
            fscanf(data, "%s%f%s%s%s", p->CSNo, &p->fund, p->leadMan,
                   p->startTime, p->finishTime);
            break;
        case 2:
            /*导入方式二，键盘输入*/
            printf("请输入一系列数据，分别为：\n"
                           " * 年度编号\n"
                           " * 投入资金\n"
                           " * 负责人\n"
                           " * 计划开始时间\n"
                           " * 计划完结时间\n");
            fscanf(stdin, "%s%f%s%s%s", p->CSNo, &p->fund, p->leadMan,
                   p->startTime, p->finishTime);
            break;
        default:
            break;
    }

    sortSchedule(head);
    /*关联数据应该是从下一级链表中获得，而不是从键盘或者文件获得*/
    /*用project的头指针开始进行遍历，逐渐的到相关数据*/
    while (prop) {
        p->projectNum++;
        if (prop->isSupported)
            p->realSupProNum++;
        if (!strstr(prop->judgement, "未能正常结题")) {
            p->finishProNum++;
        }
        prop = prop->next;
    }
}

/*用于刷新计划表中的数据*/
/*在每次更改项目信息之后进行刷新*/
void refreshSchList(struct schedule *p) {
    struct project *proP = p->projectHead->next;
    p->projectNum = 0;
    p->realSupProNum = 0;
    p->finishProNum = 0;
    /*遍历计划中的项目链表*/
    while (proP) {
        p->projectNum++;
        /*当项目为支持*/
        if (proP->isSupported)
            p->realSupProNum++;
        /*不是未能正常结题，完成项目数就可以加一*/
        if (!strstr(proP->judgement, "未能正常结题")) {
            p->finishProNum++;
        }
        proP = proP->next;
    }
}

/*删除操作*/
void deleteSchedule(struct schedule *head) {
    struct schedule *collection[100];
    /*分为从年度编号删除和负责人删除*/
    int way;
    char CSNoTemp[40];
    float fundTemp = 0;
    printf("从年度编号删除按1\n从经费删除按2\n");
    scanf("%d", &way);
    switch (way) {
        case 1:
            printf("请输入年度编号\n");
            scanf("%s", CSNoTemp);
            findSchCollectionByCSNo(collection, head, CSNoTemp);
            break;
        case 2:
            printf("请输入经费\n");
            scanf("%f", &fundTemp);
            findSchCollectionByFundMax(collection, head, fundTemp, fundTemp);
            break;
        default:
            break;
    }
    /*打印删除信息，并且释放内存*/
    for (int i = 0; collection[i]; ++i) {
        struct schedule *temp_prior;
        struct schedule *temp_next;
        printf("删除项为：");
        printSchedule(collection[i]);
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


/* 查找操作
 * 通过年度编号查找（迷糊查找）
 * 通过资金查找（支持范围查找）
 * 通过支持项目查找（支持范围查找）
 * 混合查找*/
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
    printf("请输入你要查找的方式：\n"
                   "1.年度编号查找\n"
                   "2.资金查找\n"
                   "3.支持项目数查找\n"
                   "4.混合查找\n");
    scanf("%d", &method);
    switch (method) {
        case 1:
            printf("请输入年度编号：");
            scanf("%s", temp_CSNo);
            findSchCollectionByCSNo(collection, head, temp_CSNo);
            if (collection[0]) {
                printf("查找结果是：\n");
                printSchCollection(collection);
            } else {
                printf("没有相匹配的结果\n");
            }
            break;
        case 2:
            printf("请输入资金的最小值和最大值\n");
            printf("最小值：");
            scanf("%f", &temp_fund[0]);
            printf("最大值：");
            scanf("%f", &temp_fund[1]);
            findSchCollectionByFundMax(collection, head, temp_fund[1], temp_fund[0]);
            if (collection[0]) {
                printf("查找结果是：\n");
                printSchCollection(collection);
            } else {
                printf("没有相匹配的结果\n");
            }
            break;
        case 3:
            printf("请输入支持项目数的最小值和最大值\n");
            printf("最小值：");
            scanf("%d", &temp_sup[0]);
            printf("最大值：");
            scanf("%d", &temp_sup[1]);
            findSchCollectionBySupMax(collection, head, temp_sup[1], temp_sup[0]);
            if (collection[0]) {
                printf("查找结果是：\n");
                printSchCollection(collection);
            } else {
                printf("没有相匹配的结果\n");
            }
            break;
        case 4:
            printf("请输入年度编号：");
            scanf("%s", temp_CSNo);
            printf("请输入资金的最小值和最大值\n");
            printf("最小值：");
            scanf("%d", &temp_sup[0]);
            printf("最大值：");
            scanf("%d", &temp_sup[1]);
            printf("请输入支持项目数的最小值和最大值\n");
            printf("最小值：");
            scanf("%d", &temp_sup[0]);
            printf("最大值：");
            scanf("%d", &temp_sup[1]);
            findSchCollectionCombine(collection, head, temp_CSNo, temp_fund[1],
                                     temp_fund[0], temp_sup[1], temp_sup[0]);
            if (collection[0]) {
                printf("查找结果是：\n");
                printSchCollection(collection);
            } else {
                printf("没有相匹配的结果\n");
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


/* 打印计划数据
 * 年度编号
 * 投入资金
 * 负责人
 * 申报项目数(关联项目数量）
 * 实际支持项目 （关联isSupported)
 * 结题项目数  (关联结题评价）
 * 计划开始时间
 * 计划完结时间
 * 项目基本信息*/
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
    /*第一个头节点不存放数据*/
    struct schedule *p = head->next;
    FILE *dataOutput = fopen("H:/data/Output_schedule.txt", "a+");
    char title[10][20] = {"年度编号", "投入资金", "负责人", "申报项目数",
                          "实际支持项目", "结题项目数", "计划开始时间", "计划完结时间",
                          "优秀项目数", "项目基本信息"};
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

/*遍历计划表容器*/
void printSchCollection(struct schedule **pSchedule) {
    for (int i = 0; pSchedule[i]; ++i) {
        printSchedule(pSchedule[i]);
    }
}


/*修改操作*/
void modifySchedule(struct schedule *head) {
    struct schedule *collection[100];
    char temp_CSNo[10];
    printf("请输入你要修改的计划表的年度编号：\n");
    scanf("%s", temp_CSNo);
    findSchCollectionByCSNo(collection, head, temp_CSNo);
    for (int i = 0; collection[i]; ++i) {
        /*查找需要修改的计划表*/
        printf("当前操作的计划表为：\n");
        printSchedule(collection[i]);
        modifyDetailSchedule(collection[i]);
    }
    /*修改完之后应该排序*/
    sortSchedule(head);
}

void modifyDetailSchedule(struct schedule *p) {
    /*判定p是否为空*/
    if (!p) {
        printf("修改的计划表为空！！\n");
        return;
    }

    int choice = 0;
    int tempNum = 0;
    float tempFloat = 0;
    char tempString[40];
    printf("请输入你要修改项的序号：\n"
                   " 1 年度编号\n"
                   " 2 投入资金\n"
                   " 3 负责人\n"
                   " 4 申报项目数\n"
                   " 5 实际支持项目数\n"
                   " 6 结题项目数\n"
                   " 7 计划开始时间\n"
                   " 8 计划完结时间\n"
                   " 9 项目基本信息\n"
                   "(input enter to continue)\n");
    scanf("%d", &choice);
    switch (choice) {
        case 1:
            printf("请输入需要新的年度编号：\n");
            scanf("%s", tempString);
            strcpy(p->CSNo, tempString);
            break;
        case 2:
            printf("请输入新的投入资金：\n");
            scanf("%f", &tempFloat);
            p->fund = tempFloat;
            break;
        case 3:
            printf("请输入新的负责人：\n");
            scanf("%s", tempString);
            strcpy(p->leadMan, tempString);
            break;
        case 4:
            printf("请输入新的申报项目数：\n");
            scanf("%d", &tempNum);
            p->projectNum = tempNum;
            break;
        case 5:
            printf("请输入新的实际支持项目数：\n");
            scanf("%d", &tempNum);
            p->realSupProNum = tempNum;
            break;
        case 6:
            printf("请输入新的结题项目数：\n");
            scanf("%d", &tempNum);
            p->finishProNum = tempNum;
            break;
        case 7:
            printf("请输入新的计划开始时间：\n");
            scanf("%s", tempString);
            strcpy(p->startTime, tempString);
            break;
        case 8:
            printf("请输入新的计划结束时间：\n");
            scanf("%s", tempString);
            strcpy(p->finishTime, tempString);
            break;
            case 9:
                //*项目具体修改*//*
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