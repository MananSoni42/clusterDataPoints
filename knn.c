#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define MAX 64

//N->Number of Data points  D->Dimensions of each
//k,e,min pts are parameters for the algorithm

float inf=1.0/0.0;	

struct node
{
	int index;
	double *data;
	struct node *next,*last;
};

typedef struct node NODE;

int getData(NODE**,int,int);
int populateMatrix(NODE**,int,int,NODE*,int,int);
int kNearest(NODE**,int,int,NODE*,int,int);
int selection(double [],int);

NODE* getNode(NODE*,int,int,double []);
NODE* addNode(NODE*,int,int,double []);
void printList(NODE*,int);
void freeList(NODE*);

int main()
{ 
	int i,j,N,D,K,E,minPts;
	scanf("%d %d %d %d %d",&N,&D,&K,&E,&minPts);
	
	//declare DLL to store the data points
	NODE *point=NULL; int pSize=N,pDataSize=D;

	//declare DLL to store the dist between any 2 points(Similarity Matrix)
	NODE *m=NULL; int mSize=N,mDataSize=N;

	//declare DLL to store neighbours;
	NODE *nbr=NULL; int nbrsize=N,nbrDataSize=K;

	//input the data
        getData(&point,pSize,pDataSize);

	//fill Similarity Matrix
	populateMatrix(&m,mSize,mDataSize,point,pSize,pDataSize);
        
	//print the data
	printf("Points: \n");
	printList(point,pDataSize);
	
	//print matrix
	printf("\nSimilarity Matrix: \n");
	printList(m,mDataSize);

	//calculate k-nearest Neighbours
	kNearest(&nbr,nbrsize,nbrDataSize,m,mSize,mDataSize);

        //print k-Nearest Neighbours
	printf("\nk-Nearest Neighbours: \n");
	printList(nbr,nbrDataSize);
        
	//free memory
	freeList(point);
	freeList(m);
	freeList(nbr);
	
	printf("\n"); return 0;
}

//get Data from File 
//Format: 'size' sets each consists of 'dataSize' space seperated values
int getData(NODE** p,int s,int d_s)
{
	int i,j;
	double inp[d_s];
        
	for (i=0;i<s;i++)
	{ 
		for(j=0;j<d_s;j++)
		{
			scanf("%lf",&inp[j]);
		}
		*p = addNode(*p,i+1,d_s,inp);
	}
}

//calculate the distance between any two POINTS
double getDistance(NODE* a,NODE* b,int d_s)
{ 	
	long double d=0.0; double dist=0.0;
	
	//find the euclidian distance between the two points
	for (int i=0;i<d_s;i++)
	{ 
		d = d + pow( (a->data[i] - b->data[i]),2 );
	}
        dist = sqrt(d);

	return dist;
}	

//compute the Similarity Matrix
int populateMatrix(NODE** m,int sM,int mData,NODE* p,int sP,int pData)
{
	int i=0,j;
	double dist[mData];
	NODE *ai=p,*aj=p;

        for (i=0;i<sM;i++)
	{
		aj=p;
		for (j=0;j<mData;j++)
		{ 
			if (i==j)
			{ dist[j]=inf;  }
			else
			{ dist[j]=getDistance(ai,aj,pData); }
			aj=aj->next;
		}

		*m=addNode(*m,i+1,mData,dist);
		ai=ai->next;
	}
}


int kNearest(NODE** n,int nSize,int nData,NODE* m,int mSize,int mData)
{ 
	int i,j,k,min;
	NODE *p,*q;
  	float temp;
	double nbr[nData];

	for (i=0;i<nSize;i++)
	{
		p=m; q=m;
		for (j=0;j<nData;j++)
		{       
			min = j;
			for (k=j;k<mData;k++)
			{
				if ( (q->data)[k] <= (q->data)[min] )
				{ min=k; }
			}

			nbr[j] = min+1;

			temp = (q->data)[min];
			
			(q->data)[min] = (q->data)[j];
			
			(q->data)[j] = temp;
		}
		selection(nbr,nData);

		*n=addNode(*n,j+1,nData,nbr);
		m=m->next;
	}

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

NODE* addNode(NODE* head,int ind,int dataSize,double d[])
{
	NODE *new;
	new = getNode(new,ind,dataSize,d);

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

void printList(NODE* head,int d_s)
{
	while(head!=NULL)
	{
		printf("(%2d [ ",head->index);
		for (int i=0;i<d_s;i++)
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

int selection(double a[],int n)
{ int i,j,min,temp;
  for(i=0;i<n;i++)
  { min=i;
    for (j=i;j<n;j++)
    { if (a[j]<=a[min])
      { min=j; }
    }
    temp=a[min];
    a[min]=a[i];
    a[i]=temp;
  }
}
