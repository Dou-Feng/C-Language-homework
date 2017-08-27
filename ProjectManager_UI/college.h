#include "total.h"




typedef struct college {
    char collegeName[20];
    int projectNum;
    float passingRate;
    float excellentAndGoodRate;
    float unfinishedRate;
}Coll;

struct college *getCollege(struct schedule *, char *, char *, char *);

void getCollegeCollection(struct college **college_collection, char **name_collection, struct schedule *head, char *startTime, char *endTime);

void getCollegeName(char **, struct schedule *, char *, char *);

void sortCollegedentByProjectNum(struct college **collection);

void sortCollegeByPassingRate(struct college **collection);

void sortCollegeByexcellentRate(struct college **collection);

void sortCollegeByunfinishedRate(struct college **collection);






