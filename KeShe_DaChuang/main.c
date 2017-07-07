#include <stdio.h>
#include "schedule.h"

int main() {
    FILE *scheduleData = fopen("H:/data/data_keshe_schedule.txt", "r");
    struct schedule *head = createSchedule();
    struct schedule *collection[10];
    printf("------大创项目记录系统------\n");
    printSchTable(head);
    int method = -1;
    while (method) {
        printf("输入1进行添加操作，输入2进行删除操作，输入3进行修改操作，输入4进行查询操作，输入0退出系统\n");
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
            default:
                break;
        }
        printSchTable(head);
    }
    fclose(scheduleData);
    return 0;
}

