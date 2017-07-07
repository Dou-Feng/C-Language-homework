#include <stdio.h>
#include "schedule.h"

int main() {
    FILE *scheduleData = fopen("H:/data/data_keshe_schedule.txt", "r");
    struct schedule *head = createSchedule();
    struct schedule *collection[10];
    printf("------����Ŀ��¼ϵͳ------\n");
    printSchTable(head);
    int method = -1;
    while (method) {
        printf("����1������Ӳ���������2����ɾ������������3�����޸Ĳ���������4���в�ѯ����������0�˳�ϵͳ\n");
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

