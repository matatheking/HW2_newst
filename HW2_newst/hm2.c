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



void printAll(WorkerList* head);
void printWorker(Worker* w, int format);
Worker* createWorker();
WorkerList* addWorker(WorkerList* head, Worker* w);
int index(WorkerList* head, long id);
int indexRe(WorkerList* head, long id);
void update_worker(WorkerList* head, float present);
void free_workers(WorkerList* head);
WorkerList* deleteWorstWorker(WorkerList* head);
WorkerList* reverse(WorkerList* head);



void main()
{
	Worker* w;
	WorkerList* head = NULL;

	for (int i = 0; i < 4; i++)
	{
		w = createWorker();

		head = addWorker(head, w);
	}

	printf("\n");
	printf(" the list is :\n");
	printAll(head);
	printf("%d\n", index(head, 123123));
	printf("%d\n", indexRe(head, 123123));
	
	
	

	update_worker(head, 1.5);
	printf("\nthe list after raising the salaries: is :\n");
	printAll(head);


	head = reverse(head);
	printf("\nreverse list is : \n");
	printAll(head);


	head = deleteWorstWorker(head);
	printf("\nlist after we fired the worst worker :\n");
	printAll(head);
	

	

	free_workers(head);
	free(head);

}






Worker* createWorker() {
	Worker* w = (Worker*)malloc(sizeof(Worker));
	printf("enter worker id:\n");
	scanf("%ld", &(w->id));
	printf("enter worker salary:\n");
	scanf("%ld", &(w->salary));
	char tmp[100];
	printf("enter worker name:\n");
	fseek(stdin, 0, SEEK_END);
	gets(tmp);
	w->name = (char*)malloc(strlen(tmp));
	if (!w->name) { puts("allocation failed\n"); exit(1); }
	strcpy(w->name, tmp);
	printf("enter starting year format (0 for numbers 1 for letters)\n");
	int num;
	scanf("%d", &num);
	if (num == 0) {
		printf("enter starting year (in numbers)\n");
		scanf("%ld", &(w->startyear.yearnum));
	}
	else {
		printf("enter starting year (in letters)\n");
		fseek(stdin, 0, SEEK_END);
		gets(tmp);
		strcpy(w->startyear.yearstring, tmp);
	}
	return w;
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

	WorkerList* new_node = (WorkerList*)malloc(sizeof(WorkerList));
	if (new_node == NULL)
	{
		printf("allocation faild\n");
		exit(1);
	}

	new_node->data = w;
	new_node->next = NULL;

	if (head == NULL)   //if the list is empty  initialize the first part of the list. 
	{
		head = new_node;
		return head;
	}


	WorkerList* current = head;


	if (new_node->data->salary > current->data->salary)// if the new node bigger then the first node
	{
		new_node->next = current;
		head = new_node;
		return head;
	}


	WorkerList* prev =  NULL;
	WorkerList* scouter = NULL;



	while (current!=NULL && current->data->salary >= new_node->data->salary)
	{
		prev = current;
		current = current->next;
		
	}
	
	
	prev->next = new_node;
	new_node->next = current;
	
	return head;
	

}




int index(WorkerList* head, long id) {
	//if not found return -1 
	//if found return index
	int index = 0;
	WorkerList* p = head;
	while (p != NULL) {
		if (p->data->id == id) return index;
		index++;
		p = p->next;
	}
	return -1;
}
int indexRe(WorkerList* head, long id) {
	int index = 0;
	WorkerList* p = head;
	if (p == NULL) {
		return -1;
	}
	if (p->data->id == id) {
		return index;
	}
	else index++;
	index += indexRe(p->next, id);
	return index;
}
void update_worker(WorkerList* head, float precent) {
	WorkerList* p = head;
	while (p != NULL) {
		p->data->salary += (p->data->salary / 100) * precent;
		p = p->next;
	}
}
void free_workers(WorkerList* head) {
	WorkerList* p = head->next;
	while (head != NULL) {
		free(head->data);
		head = p;
		if (p == NULL) return;
		p = p->next;
	}
}






WorkerList* deleteWorstWorker(WorkerList* head)
{
	if (head == NULL)
	{
		return NULL;
	}

	WorkerList* current = head;
	WorkerList* scouter = current->next;

	head = scouter;

	free(current);

	return head;

	/*while (scouter != NULL) // in case we didnt reversed the list. 
	{
		prev = current;
		current = current->next;
		scouter = current->next;

	}
	
	free(prev->next);

	return head;*/

}



WorkerList* reverse(WorkerList* head)
{
	WorkerList* current = head;
	WorkerList* ptr = NULL;
	WorkerList* prev = NULL;


	while (current != NULL)
	{
		ptr = current->next;
		current->next = prev;
		prev = current;
		current = ptr;
	}

	head = prev;

	return head;


}


void printAll(WorkerList* head) {

	WorkerList* current = head;

	while (current != NULL)
	{
		printWorker(current->data, 0);

		current = current->next;

	}

}



