#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct node{
	char reference[20];
	char RorW;
	int pid;
	node * next;
}node;



typedef struct list {
	int size;
	node *start;
	node *end;
}list;


void listInitialize(list * l){
	l->size=0;
	l->start=NULL;
	l->end=NULL;
}

void listInsert(list *l,node * n){
	if(l->start==NULL){
		l->start=n;
		l->end=n;
		n->next=NULL;	
	}
	else{
		l->end->next=n;
		n->next=NULL;
		l->end=n;
	}
	l->size++;

}


node* returnNode(list *l){
	if(l->start!=NULL)
		return l->start;
	else
		printf("list is empty\n");

}

void nodeDestroy(list *l){
	node *temp=l->start;
	l->start=l->start->next;
	temp->next=NULL;
	free(temp);
	
	if(l->start==NULL)
		l->end=NULL;

	l->size--;
}

void listDestroy(list * l){
	while(l->start!=NULL)
		nodeDestroy(l);
}

void listPrint(list *l){
	
	node*iterator = l->start;	
	
	while(iterator!=NULL){
		printf("%s\t",iterator->reference);
		printf("%c\t",iterator->RorW);
		printf("%d\t",iterator->pid);
		printf("\n");
		iterator=iterator->next;
	}

}



////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////

node * nodeCreate(char line[],int pid){
	node *n = (node*) malloc(sizeof(node));
	int i =0;
	while(line[i]!=' '){
		n->reference[i]=line[i];
		i++;
	}
	n->reference[i] = '\0';
	i++;
	n->RorW = line[i];
	n->pid = pid;

}

/////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////

void allocate_matrix(char**** tab,int size1d,int size2d,int size_string)
{
    int iterator;
    int iterator_2;

    char*** temp = (char***) calloc(size1d,sizeof(char**));
    for (iterator = 0 ; iterator < size1d;iterator++)
    {
        *(temp+iterator) = (char**) calloc(size2d,sizeof(char*));

        for (iterator_2 = 0;iterator_2 < size2d;iterator_2++)
        {
            *(*(temp+iterator)+iterator_2) = (char*) calloc(size_string,sizeof(char));
        }
    }

    *tab = temp;
}

int checktable(char***t,int frames){
	int i;
	for(i=0;i<frames;i++){
		if(strcmp(t[i][0],"e\0")==0){
			return i;
		}
	}
	return -2;
}

char*** fwf(char*** t , int f){
	int i,j;
	for(i=0;i<f;i++){
		for(j=0;j<3;j++){
			strcpy(t[i][j],"e\0");
		}
	}
	return t;

}
