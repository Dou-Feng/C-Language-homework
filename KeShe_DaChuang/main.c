#include <stdio.h>
#include "schedule.h"

int main() {
    FILE *scheduleData = fopen("H:/data/data_keshe_schedule.txt", "r");
    FILE *projectData = fopen("H:/data/data_keshe_project.txt", "r");
    FILE *peopleData = fopen("H:/data/data_keshe_people.txt", "r");
    struct schedule *head = createSchedule();
    printf("                       ------大创项目记录系统------\n\n");
    printSchTable(head);
    int method = -1;
    int method2 = -1;
    char temp_CSNo[12];
    struct project *targetPro;
    struct schedule *collection[100];
    while (method) {
        printf("输入1进行添加操作，输入2进行删除操作，输入3进行修改操作，输入4进行查询操作，输入5查看计划的项目详情，输入0退出系统\n");
        scanf("%d", &method);
        switch (method) {
            case 1:
                addSchedule(head, scheduleData);
                break;
            case 2:
                deleteSchedule(head);
                break;
            case 3:
                modifySchedule(head);
                break;
            case 4:
                findSchedule(head);
                break;
            case 5:
                printf("请输入你要查询项目表所在的年度编号：");
                scanf("%s", temp_CSNo);
                findSchCollectionByCSNo(collection, head, temp_CSNo);
                targetPro = collection[0]->projectHead;
                printProTable(targetPro);
                while (method2) {
                    printf("输入1进行添加操作，输入2进行删除操作，输入3进行修改操作，输入4进行查询操作，输入5查看项目的人员详情，输入0退回上一级\n");
                    scanf("%d", &method2);
                    switch (method2) {
                        case 1:
                            addProject(targetPro, projectData);
                            break;
                        case 2:
                            deleteProject(targetPro);
                            break;
                        case 3:
                            modifyProject(targetPro);
                            break;
                        case 4:
                            findProject(targetPro);
                            break;
                        case 5:
                            /*人员操作*/
                            break;
                        default:
                            break;
                    }
                    printProTable(targetPro);
                }
                method2 = -1;
            default:
                break;
        }
        printSchTable(head);
    }
    fclose(projectData);
    fclose(scheduleData);
    return 0;
}

