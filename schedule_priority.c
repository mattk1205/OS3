#include <stdlib.h>
#include "task.h"
#include "schedulers.h"
#include "list.h"
#include "cpu.h"

struct node *head = NULL;
int numTasks = 0;

void add(char *name, int priority, int burst)
{
	Task *tmp = malloc(sizeof(Task));
	tmp->name = name;
	tmp->priority = priority;
	tmp->burst = burst;
	insert(&head, tmp);
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
	//Priority
	while(numTasks > 0)
	{
		struct node *priority = getMaxPriority(head);
		Task *tmp = priority->task;
		run(tmp,tmp->burst);
		delete(&head, tmp);
		numTasks--;
	}
}
