#include <stdlib.h>
#include <stdio.h>
#include "task.h"
#include "schedulers.h"
#include "list.h"
#include "cpu.h"

struct node *head;
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

struct node* getSJ(struct node* head){
    struct node* shortest = head;
    struct node* curr = head->next;
    while(curr != NULL && curr != head){
        if(curr->task->burst < shortest->task->burst)
            shortest = curr;
        curr = curr->next;
    }
    return shortest;
}

void schedule()
{
	while(numTasks > 0)
	{
		struct node *smallest = getSJ(head);
		Task *task = smallest->task;
		run(task, task->burst);
		delete(&head, task);
		numTasks--;
	}
} 
