#include <stdio.h>
#include "studentTable.h"


int main() {
    FILE *scheduleData = fopen("H:/data/data_keshe_schedule.txt", "r");
    FILE *projectData = fopen("H:/data/data_keshe_project.txt", "r");
    FILE *peopleData = fopen("H:/data/data_keshe_people.txt", "r");
    struct schedule *head = createSchedule();
    printf("                       ------����Ŀ��¼ϵͳ------\n\n");
    printSchTable(head);
    int method = -1;
    int method2 = -1;
    int method3 = -1;
    char temp_CSNo[12];
    char temp_CNo[40];
    struct project *targetPro;
    struct people *targetPeo;
    struct schedule *collectionSch[100];
    struct schedule *collectionSch_data[100];
    struct project *collectionPro[100];
    struct data *collection_data[100];
    char *collection_name[200];
    memset(collection_name, 0, sizeof(char *) * 200);
    struct student *collection_student[100];
    addSchedule(head, scheduleData);
    addSchedule(head, scheduleData);
    addProject(head->next->projectHead, projectData);
    addProject(head->next->projectHead, projectData);
    addPeople(head->next->projectHead->next->peopleHead, peopleData);
    addPeople(head->next->projectHead->next->peopleHead, peopleData);
    refreshSchList(head->next);
    refreshProList(head->next->projectHead->next);
    printSchTable(head);
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
                findSchCollectionByCSNo(collectionSch, head, temp_CSNo);
                if (!collectionSch[0])
                    break;
                targetPro = collectionSch[0]->projectHead;
                printProTable(targetPro);
                while (method2) {
                    printf("����1������Ӳ���������2����ɾ������������3�����޸Ĳ���������4���в�ѯ����������5�鿴��Ŀ����Ա���飬����0�˻���һ��\n");
                    scanf("%d", &method2);
                    switch (method2) {
                        case 1:
                            addProject(targetPro, projectData);
                            refreshSchList(collectionSch[0]);
                            break;
                        case 2:
                            deleteProject(targetPro);
                            break;
                        case 3:
                            modifyProject(targetPro);
                            refreshSchList(collectionSch[0]);
                            break;
                        case 4:
                            findProject(targetPro);
                            break;
                        case 5:
                            printf("��������Ҫ��ѯ��Ա���ڵ���Ŀ���ƣ�");
                            scanf("%s", temp_CNo);
                            findProCollectionByProName(collectionPro, targetPro, temp_CNo);
                            if (!collectionPro[0])
                                break;
                            targetPeo = collectionPro[0]->peopleHead;
                            printPeoTable(targetPeo);
                            while (method3) {
                                printf("����1������Ӳ���������2����ɾ������������3�����޸Ĳ���������4���в�ѯ����������0�˻���һ��\n");
                                scanf("%d", &method3);
                                switch (method3) {
                                    case 1:
                                        addPeople(targetPeo, peopleData);
                                        refreshProList(collectionPro[0]);
                                        break;
                                    case 2:
                                        deletePeople(targetPeo);
                                        break;
                                    case 3:
                                        modifyPeople(targetPeo);
                                        break;
                                    case 4:
                                        findPeople(targetPeo);
                                        break;
                                    default:
                                        break;
                                }
                                printf("\n");
                                printPeoTable(targetPeo);
                            }
                            method3 = -1;
                            break;
                        default:
                            break;
                    }
                    printf("\n");
                    printProTable(targetPro);
                }
                method2 = -1;
                break;
            default:
                break;
        }
        printf("\n");
        printSchTable(head);
        getAllName(collection_name, head);
        getStudentCollection(collection_student, collection_name, head);
        printStudentCollection(collection_student);
    }
    fclose(projectData);
    fclose(scheduleData);
    fclose(peopleData);
    return 0;
}

