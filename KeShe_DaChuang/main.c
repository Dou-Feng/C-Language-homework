#include <stdio.h>
#include "schedule.h"

int main() {
    FILE *scheduleData = fopen("H:/data/data_keshe_schedule.txt", "r");
    FILE *projectData = fopen("H:/data/data_keshe_project.txt", "r");
    FILE *peopleData = fopen("H:/data/data_keshe_people.txt", "r");
    struct schedule *head = createSchedule();
    printf("                       ------����Ŀ��¼ϵͳ------\n\n");
    printSchTable(head);
    int method = -1;
    int method2 = -1;
    char temp_CSNo[12];
    struct project *targetPro;
    struct schedule *collection[100];
    while (method) {
        printf("����1������Ӳ���������2����ɾ������������3�����޸Ĳ���������4���в�ѯ����������5�鿴�ƻ�����Ŀ���飬����0�˳�ϵͳ\n");
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
                printf("��������Ҫ��ѯ��Ŀ�����ڵ���ȱ�ţ�");
                scanf("%s", temp_CSNo);
                findSchCollectionByCSNo(collection, head, temp_CSNo);
                targetPro = collection[0]->projectHead;
                printProTable(targetPro);
                while (method2) {
                    printf("����1������Ӳ���������2����ɾ������������3�����޸Ĳ���������4���в�ѯ����������5�鿴��Ŀ����Ա���飬����0�˻���һ��\n");
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
                            /*��Ա����*/
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

