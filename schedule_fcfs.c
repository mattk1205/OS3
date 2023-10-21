#include <stdlib.h>
#include <stdio.h>
#include "task.h"
#include "schedulers.h"
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

void schedule() {
    struct node* curr = head;
	while(curr != NULL)
	{
		Task *task = curr->task;
		run(task, task->burst);
		delete(&head, task);
		numTasks--;
        curr = curr->next;
	}
}