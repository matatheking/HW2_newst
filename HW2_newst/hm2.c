#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
typedef struct Worker {
	long id;
	char* name;
	long salary;
	union {
		long yearnum;
		char yearstring[7];
	}startyear;
}Worker;



typedef struct WorkerList
{
	Worker* data;
	struct WorkerList* next;
} WorkerList;




void printWorker(Worker* w, int format);
Worker* createWorker();
WorkerList* addWorker(WorkerList* head, Worker* w);









void main() {
	Worker* s;
	s = createWorker();
	WorkerList* head = NULL;
	//printWorker(s, 1);
	WorkerList* lst;;
	lst = addWorker(head, s);

	for (int i = 0; i < strlen(s->name); i++)
	{
		/*free((s->name+i))*/;
	}

}
Worker* createWorker() {
	Worker w;
	printf("enter worker id:\n");
	scanf("%ld", &w.id);
	printf("enter worker salary:\n");
	scanf("%ld", &w.salary);
	char tmp[100];
	printf("enter worker name:\n");
	fseek(stdin, 0, SEEK_END);
	gets(tmp);
	w.name = (char*)malloc(strlen(tmp));
	if (!w.name) { puts("allocation failed\n"); exit(1); }
	strcpy(w.name, tmp);
	printf("enter starting year format (0 for numbers 1 for letters)\n");
	int num;
	scanf("%d", &num);
	if (num == 0) {
		printf("enter starting year (in numbers)\n");
		scanf("%ld", &w.startyear.yearnum);
	}
	else {
		printf("enter starting year (in letters)\n");
		fseek(stdin, 0, SEEK_END);
		gets(tmp);
		strcpy(w.startyear.yearstring, tmp);
	}
	return &w;
}
void printWorker(Worker* w, int format) {
	printf("id: %ld\n", w->id);
	printf("name: %s\n", w->name);
	printf("salary: %ld\n", w->salary);
	if (format == 0)
		printf("starting year: %ld\n", w->startyear.yearnum);
	else
		printf("starting year: %s\n", w->startyear.yearstring);
}


WorkerList* addWorker(WorkerList* head, Worker* w)
{
	WorkerList* node = (WorkerList*)calloc(1, sizeof(WorkerList));//pointer to a new 
																 // junction. 
	if (node)
		exit(0);

	WorkerList* temp = (WorkerList*)calloc(1, sizeof(WorkerList));
	if (temp)
		exit(0);


	if (!head)   //if the list is empty  initialize the first part of the list. 
	{
		node->data = w;
		head = node;
		return head;
	}





	while (!head->next)
	{
		if (head->data->salary < w->salary) //condition to orgenaized the list from the biggest salary to the smallest
		{                                   // if w-> salary is bigger then the prev one ,switch them.


			node->data = w;
			temp->data = head->data;
			head->next = temp;
			node->next = temp;
			head->next = node;



			node->next = head->next;
			head->next = node;
		}
	}






}






