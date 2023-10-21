#include <stdlib.h>
#include <stdio.h>
#include "task.h"
#include "schedulers.h"
#include "list.h"
#include "cpu.h"

struct node *head;
int numTasks = 0;

void add(char *name, int priority, int burst) {
    Task *task = malloc(sizeof(Task));
    task->name = name;
    task->priority = priority;
    task->burst = burst;
    insert(&head, task);
    numTasks++;
}

void schedule() {
    struct node* curr = head;

    while (numTasks > 0 && curr != NULL) {
        Task *task = curr->task;
        int time_slice = task->burst;
        if (task->burst > 10)
            time_slice = 10;
        run(task, time_slice);
        task->burst -= time_slice;

        if(task->burst > 0)
            curr = curr->next;
        else {
            struct node* temp = curr;
            curr = curr->next;
            delete(&head, temp->task);
        }

        if(curr == NULL) {
            curr = head;
        }
    }
}

