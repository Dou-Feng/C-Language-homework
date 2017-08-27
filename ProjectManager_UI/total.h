#include "schedule.h"


typedef struct data {
    char scheduleNo[10];
    int registeredProjectNum;
    int supportedProjectNum;
    float fund;
    float supportingRate;
    float passingRate;
    float excellentRate;
    float qualifiedRate;
    float unfinishedRate;
    int studentNum;

}Data;



void getInTimeSch(struct schedule **collection, struct schedule *, char *, char *);

struct data *getSchData(struct schedule *);

void sortDataByregisteredProjectNum(struct data **collectionData, struct schedule **collectionSch);

void sortDataBySupportingRate(struct data **collectionData, struct schedule **collectionSch);

void sortDataByPassingRate(struct data **collectionData, struct schedule **collectionSch);

void sortDataBySupportedNum(struct data **collectionData, struct schedule **collectionSch);

void sortDataByFund(struct data **collectionData, struct schedule **collectionSch);

void fullDataCollection(struct data **collectionData, struct schedule **collectionSch);
