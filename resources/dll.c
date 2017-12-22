#include<stdio.h>
#include<stdlib.h>

int N,D;

struct node
{
	int index;
	double *data;
	struct node *next,*last;
};

typedef struct node NODE;


NODE* getNode(NODE*,int,int,double []);
NODE* addNode(NODE*,int,int,double []);
void printList(NODE*,int);
void freeList(NODE*);

int main()
{
	int i,j;
	scanf("%d %d",&N,&D);
	double inp[D];
	for (i=0;i<D;i++)
	{ inp[i]=0; }
	NODE* point=NULL;

	for (i=0;i<N;i++)
	{ 
		for(j=0;j<D;j++)
		{
			scanf("%lf",&inp[j]);
		}
		point = addNode(point,i+1,D,inp);
	}

	printList(point,D);

	freeList(point);

	return 0;
}

NODE* getNode(NODE* n,int ind,int size,double d[])
{
	n = malloc( sizeof(NODE) );
	n->next = NULL;
	n->last = NULL;
	n->index = ind;
	n->data = malloc( size*sizeof(double) );
	
	for (int i=0;i<size;i++)
	{
		*( (n->data)+i ) = d[i];
	}

	return n;
}

NODE* addNode(NODE* head,int ind,int size,double d[])
{
	NODE *new;
	new = getNode(new,ind,size,d);

	if (head==NULL)	
	{ 
		head = new; 
		return head; 
	}

	else
	{ 
		NODE *p;
		p = head;
		while ( p->next!=NULL )
		{ p = p->next; }
		p->next = new;
		new->last = p;
	}

	return head;
}

void printList(NODE* head,int size)
{
	while(head!=NULL)
	{
		printf("(%2d [ ",head->index);
		for (int i=0;i<size;i++)
		{ printf("%3.2lf ",head->data[i]); }
		printf("] )\n");
		head=head->next;
	}
}

void freeList(NODE* head)
{
	NODE* temp;
	while(head!=NULL)
	{
		temp=head;
		head=head->next;
		free(temp->data);
		free(temp);
	}
}
