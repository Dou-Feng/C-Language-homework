//
// Created by Famine on 2017/7/2.
//


#include <malloc.h>
#include "project.h"

struct project *createProject() {
    struct project *head, *tail;
    head = (struct project *) malloc(sizeof(struct project));
    tail = head;
    tail->next = NULL;
    return head;
}
