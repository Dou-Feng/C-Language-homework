//
// Created by Famine on 2017/7/2.
//

#include "people.h"
#include <malloc.h>

struct people *createPeople() {
    struct people *head, *tail;
    head = (struct people *) malloc(sizeof(struct people));
    tail = head;
    tail->next = NULL;
    tail->prior = NULL;
    return head;
}