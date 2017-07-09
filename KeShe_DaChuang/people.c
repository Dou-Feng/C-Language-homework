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

/*学号
姓名
年龄
类别
学院及专业
班级
本人特长
承担任务
联系电话
项目成员排名
*/
void addPeople(struct people *head, FILE *data) {
/*添加到链表尾，头指针不存放数据，使得每个节点都会有前一个节点指向它，方便之后的链表排序和元素交换*/
    struct people *p = head;
    struct people *prior;
    while (p->next) {
        p = p->next;
    }
    p->next = (struct people *) malloc(sizeof(struct people));
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
            fscanf(data, "%s%s%d%s%s%s%s%s%s%d", p->SNo,p->name, &p->age, p->grade, p->collegeAndMajor,
                   p->class, p->speciality, p->undertakeTask, p->phoneNum, &p->rank);
            break;
        case 2:
            /*导入方式二，键盘输入*/
            printf("请输入一系列数据，分别为：\n"
                           "学号\n"
                           "姓名\n"
                           "年龄\n"
                           "类别\n"
                           "学院及专业\n"
                           "班级\n"
                           "本人特长\n"
                           "承担任务\n"
                           "联系电话\n"
                           "项目成员排名\n");
            fscanf(stdin, "%s%s%d%s%s%s%s%s%s%d", p->SNo,p->name, &p->age, p->grade, p->collegeAndMajor,
                   p->class, p->speciality, p->undertakeTask, p->phoneNum, &p->rank);
            break;
        default:
            break;
    }
    /*next节点为NUll*/
    p->next = NULL;
    sortPeople(head);
}


/*可按照学生姓名、 院系专业、 特长、承担任务等 4 种进行查询。
其中，对姓名、 院系专业、 特长、承担任务都可进行模糊查询。*/
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
    printf("请输入你要查找的方式：\n"
                   "1.学生姓名\n"
                   "2.院系专业\n"
                   "3.特长\n"
                   "4.承担任务\n"
                   "5.组合查找\n");
    scanf("%d", &method);
    switch (method) {
        case 1:
            printf("请输入学生姓名：");
            scanf("%s", temp_String);
            findPeopleByName(collection, head, temp_String);
            if (collection[0]) {
                printf("查找结果是：\n");
                printPeoCollection(collection);
            } else {
                printf("没有相匹配的结果\n");
            }
            break;
        case 2:
            printf("请输入院系专业\n");
            scanf("%s", p->collegeAndMajor);
            while (p) {
                if (strstr(p->collegeAndMajor, temp_String)) {
                    collection[index++] = p;
                }
                p = p->next;
            }
            collection[index] = NULL;
            if (collection[0]) {
                printf("查找结果是：\n");
                printPeoCollection(collection);
            } else {
                printf("没有相匹配的结果\n");
            }
            break;
        case 3:
            printf("请输入特长\n");
            scanf("%s", temp_String);
            while (p) {
                if (strstr(p->speciality, temp_String)) {
                    collection[index++] = p;
                }
                p = p->next;
            }
            collection[index] = NULL;
            if (collection[0]) {
                printf("查找结果是：\n");
                printPeoCollection(collection);
            } else {
                printf("没有相匹配的结果\n");
            }
            break;
        case 4:
            printf("请输入承担任务\n");
            scanf("%s", temp_String);
            while (p) {
                if (strstr(p->undertakeTask, temp_String)) {
                    collection[index++] = p;
                }
                p = p->next;
            }
            collection[index] = NULL;
            if (collection[0]) {
                printf("查找结果是：\n");
                printPeoCollection(collection);
            } else {
                printf("没有相匹配的结果\n");
            }
            break;
        case 5:
            printf("请输入学生姓名：");
            scanf("%s", temp_String);
            printf("请输入院系专业\n");
            scanf("%s", temp_string1);
            printf("请输入特长\n");
            scanf("%s", temp_string2);
            printf("请输入承担任务\n");
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
                printf("查找结果是：\n");
                printPeoCollection(collection);
            } else {
                printf("没有相匹配的结果\n");
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
    /*分为从年度编号删除和经费删除*/
    int way;
    char temp_name[40];
    printf("成员名字删除按1\n特长删除按2\n");
    scanf("%d", &way);
    switch (way) {
        case 1:
            printf("请输入学生名字：");
            scanf("%s", temp_name);
            findPeopleByName(collection, head, temp_name);
            break;
        case 2:
            printf("请输入特长：");
            scanf("%s", temp_name);
            findPeopleBySpe(collection, head, temp_name);
            break;
        default:
            break;
    }
    /*打印删除信息，并且释放内存*/
    for (int i = 0; collection[i]; ++i) {
        struct people *temp_prior;
        struct people *temp_next;
        printf("删除项为：");
        printPeople(collection[i]);
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

void modifyPeople(struct people *head) {
    struct people *collection[100];
    char temp_proName[40];
    printf("请输入你要修改的成员名字：");
    scanf("%s", temp_proName);
    findPeopleByName(collection, head, temp_proName);
    for (int i = 0; collection[i]; ++i) {
        /*查找需要修改的计划表*/
        printf("当前操作的项目为：\n");
        printPeople(collection[i]);
        modifyPeopleDetail(collection[i]);
    }
    /*修改完之后应该排序*/
    sortPeople(head);
}

void modifyPeopleDetail(struct people *p) {
    /*判定p是否为空*/
    if (!p) {
        printf("修改的项目为空！！\n");
        return;
    }

    int choice = 0;
    int tempNum = 0;
    char tempString[40];
    printf("请输入你要修改项的序号：\n"
                   "1.学号\n"
                   "2.姓名\n"
                   "3.年龄\n"
                   "4.类别\n"
                   "5.学院及专业\n"
                   "6.班级\n"
                   "7.本人特长\n"
                   "8.承担任务\n"
                   "9.联系电话\n"
                   "10.项目成员排名\n");
    scanf("%d", &choice);
    switch (choice) {
        case 1:
            printf("请输入需要新的学号：\n");
            scanf("%s", tempString);
            strcpy(p->SNo, tempString);
            break;
        case 2:
            printf("请输入新的姓名：\n");
            scanf("%s", tempString);
            strcpy(p->name, tempString);
            break;
        case 3:
            printf("请输入新的年龄：\n");
            scanf("%d", &tempNum);
            p->age = tempNum;
            break;
        case 4:
            printf("请输入新的类别：(1：本科生， 2：研究生， 3：博士生， 4：指导老师)\n");
            scanf("%s", tempString);
            strcpy(p->grade, tempString);
            break;
        case 5:
            printf("请输入新的学院及专业：\n");
            scanf("%s", tempString);
            strcpy(p->collegeAndMajor, tempString);
            break;
        case 6:
            printf("请输入新的班级：\n");
            scanf("%s", tempString);
            strcpy(p->class, tempString);
            break;
        case 7:
            printf("请输入新的本人特长：\n");
            scanf("%s", tempString);
            strcpy(p->speciality, tempString);
            break;
        case 8:
            printf("请输入新的承担任务：\n");
            scanf("%s", tempString);
            strcpy(p->undertakeTask, tempString);
            break;
        case 9:
            printf("请输入新的联系电话：\n");
            scanf("%s", tempString);
            strcpy(p->phoneNum, tempString);
            break;
        case 10:
            printf("请输入新的项目成员排名：\n");
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

/*学号
姓名
年龄
类别
学院及专业
班级
本人特长
承担任务
联系电话
项目成员排名
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
    /*第一个头节点不存放数据*/
    struct people *p = head->next;
    FILE *dataOutput = fopen("H:/data/Output_people.txt", "a+");
    char title[10][20] = {"学号", "姓名", "年龄", "类别",
                          "学院及专业", "班级", "本人特长",
                          "承担任务", "联系电话", "项目成员排名"};
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

