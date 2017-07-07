#include <stdio.h>
#include "schedule.h"

int main() {
    FILE *projectData = fopen("H:/data/data_keshe_project.txt", "r");
    struct project *head = createProject();
    printf("------大创项目记录系统------\n");
    printProTable(head);
    int method = -1;
    while (method) {
        printf("输入1进行添加操作，输入2进行删除操作，输入3进行修改操作，输入4进行查询操作，输入0退出系统\n");
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

