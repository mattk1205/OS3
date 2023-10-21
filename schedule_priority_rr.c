#include <stdio.h>
#include <stdlib.h>
#include "task.h"
#include "list.h"
#include "cpu.h"

struct node *head = NULL;

int numTasks = 0;

void add(char *name, int priority, int burst)
{
    Task *task = malloc(sizeof(Task));
    task->name = name;
    task->priority = priority;
    task->burst = burst;
    insert(&head, task);
    numTasks++;
}

struct node* getMaxPriority(struct node* head){
    struct node* max = head;
    struct node* curr = head->next;
    while(curr != NULL && curr != head){
        if(curr->task->priority > max->task->priority)
            max = curr;
        curr = curr->next;
    }
    return max;
}

void schedule()
{
    struct node* curr = head;
    while (numTasks > 0)
    {
        curr = getMaxPriority(head);
        Task *task = curr->task;
        if (task->burst > 10)
        {
            run(task, 10);
            task->burst = task->burst - 10;
        }
        else
        {
            int time_Remaining = task->burst;
            run(task, time_Remaining);
            task->burst = task->burst - time_Remaining;
            curr = curr->next == head ? NULL : curr->next;
            delete(&head, task);
            numTasks--;
        }
        if(head == NULL)
            return;
    }
}