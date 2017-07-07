#include <stdio.h>
#include "schedule.h"

int main() {
    FILE *projectData = fopen("H:/data/data_keshe_project.txt", "r");
    struct project *head = createProject();
    printf("------����Ŀ��¼ϵͳ------\n");
    printProTable(head);
    int method = -1;
    while (method) {
        printf("����1������Ӳ���������2����ɾ������������3�����޸Ĳ���������4���в�ѯ����������0�˳�ϵͳ\n");
        scanf("%d", &method);
        switch (method) {
            case 1:
                addProject(head, projectData);
                break;
            case 2:
                deleteProject(head);
                break;
            case 3:
                modifyProject(head);
                break;
            case 4:
                findProject(head);
                break;
            default:
                break;
        }
        printProTable(head);
    }
    fclose(projectData);
    return 0;
}

