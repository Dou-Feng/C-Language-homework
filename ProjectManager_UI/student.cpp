

#include "student.h"
#include <string.h>

struct student *getStudent(char *name, struct schedule *head, char *startTime, char *finishTime) {
    int index = 0;
    char SNo[20];
    struct project *collection[1000];
    struct schedule *p_schedule = head->next;
    while (p_schedule) {
        struct project *p_project = p_schedule->projectHead->next;
        while (p_project) {
            struct people *p_people = p_project->peopleHead->next;

            while (p_people && strcmp(p_project->startTime, startTime) >= 0 &&
                   strcmp(p_project->finishTime, finishTime) <= 0) {

                if (strcmp(p_people->name, name) == 0) {
                    collection[index++] = p_project;
                    strcpy(SNo, p_people->SNo);

                    break;
                }

                p_people = p_people->next;
            }

            p_project = p_project->next;
        }

        p_schedule = p_schedule->next;
    }

    collection[index] = NULL;
    return getStudentData(name, SNo, collection);
}


struct student *getStudentData(char *name, char *SNo, struct project **p) {
    struct student *stu = (struct student *) malloc(sizeof(struct student));
    int index;
    memset(stu, 0, sizeof(struct student));
    for (index = 0; p[index]; ++index) {
        stu->collection_project[index] = p[index];
        if (strcmp(p[index]->judgement, "未能正常结题")) {
            stu->passingRate += 1;
        } else {
            stu->unfinishedRate += 1;
        }
        if (strcmp(p[index]->judgement, "优")  == 0 || strcmp(p[index]->judgement, "良")  == 0) {
            stu->excellentAndGoodRate += 1;
        }
    }
    stu->collection_project[index] = NULL;
    stu->project_number = index;
    stu->excellentAndGoodRate /= stu->project_number;
    stu->passingRate /= stu->project_number;
    strcpy(stu->name, name);
    strcpy(stu->SNo, SNo);
    stu->unfinishedRate /= stu->project_number;
    return stu;
}


