#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<stdbool.h>

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

struct gr
{
	int index,size;
	int *pnt,*wght;
	struct gr *next,*last;
};

typedef struct gr GRAPH;

int getData(NODE**,int,int);
int populateMatrix(NODE**,int,int,NODE*,int,int);
int kNearest(NODE**,int,int,NODE*,int,int);
int selection(double [],int);
int findWeight(NODE*,NODE*,int);
int sortGraph(int [],int [],int);
int populateGraph(GRAPH**,int,NODE*,int,int);

NODE* getNode(NODE*,int,int,double []);
NODE* addNode(NODE*,int,int,double []);
void printList(NODE*,int);
void freeList(NODE*);

GRAPH* getGraph(GRAPH*,int,int,int [],int []);
GRAPH* addGraph(GRAPH*,int,int,int [],int []);
void printGraph(GRAPH*);
void freeGraph(GRAPH*);

int main()
{
	int i,j,N,D,K,E,minPts;
	scanf("%d %d %d %d %d",&N,&D,&K,&E,&minPts);

	//declare DLL to store the data points
	NODE *point=NULL; int pSize=N,pDataSize=D;

	//declare DLL to store the dist between any 2 points(Similarity Matrix)
	NODE *m=NULL; int mSize=N,mDataSize=N;

	//declare DLL to store neighbours;
	NODE *nbr=NULL; int nbrSize=N,nbrDataSize=K;

	//declare graph G(DLL)
	GRAPH* g=NULL; int gSize=N;

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
	kNearest(&nbr,nbrSize,nbrDataSize,m,mSize,mDataSize);

        //print k-Nearest Neighbours
	printf("\nk-Nearest Neighbours: \n");
	printList(nbr,nbrDataSize);

	//Create the Graph
	populateGraph(&g,gSize,nbr,nbrSize,nbrDataSize);

	//print the graph
	printf("\nGraph: \n");
	printGraph(g);

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
			//dist is inf for P(i,i)
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

//find the K-Nearest Neighbours for the given Similarity Matrix
int kNearest(NODE** n,int nSize,int nData,NODE* m,int mSize,int mData)
{
	int i,j,k,min,c;
  	float temp;
	double nbr[nData],arr[mData];

	for (i=0;i<nSize;i++)
	{
		for (k=0;k<mData;k++)
		{ arr[k]=m->data[k]; }

		//similar to Selection Sort but only runs for 'K' iterations
		for (j=0;j<nData;j++)
		{
			//find minimum
			min = j;
			if (min==inf)
			{	c=j;
				min=c;
				if (c==mData)
				{ break; }
				c++;

			}

			for (k=0;k<mData;k++)
			{

				if ( arr[k] <= arr[min] )
				{ min=k; }
			}

			//nbr is min node's index
			nbr[j] = min+1;

			//replace with max+1
			arr[min]=inf;
		}

		//sort the neighbours according to index
		selection(nbr,nData);

		*n=addNode(*n,i+1,nData,nbr);
		//next element
		m=m->next;
	}

}

//find the total common Data points between nodes p and q
int findWeight(NODE* p,NODE* q,int nData)
{
	int sum=0,i,j;
	int a1[nData],a2[nData];
	
	//copy data values to be compared
	for (i=0;i<nData;i++)
	{ 
		a1[i]=(int)(p->data[i]);
		a2[i]=(int)(q->data[i]);
	}

	//check for total number of data that is same in both
	for (i=0;i<nData;i++)
	{
		for (j=0;j<nData;j++)
		{
			if (a1[i] == a2[j])
			{ sum++; break; }
		}
	}

	return sum;
}

int sortGraph(int p[],int w[],int size)
{
	int i,j,temp1,temp2;
	for (i=0;i<size;i++)
	{	
		for (j=0;j<size;j++)
		{
			//sort according to weight
			if ( w[j]<w[i] )
			{
				temp1=w[j]; temp2=p[j];
				w[j]=w[i];  p[j]=p[i];	
				w[i]=temp1; p[i]=temp2;
			}

			//if weights are equal
			else if (w[j]==w[i] && i!=j)
			{
				//sort according to index
				if ( p[j]>p[i] )
				{
					temp1=w[j]; temp2=p[j];
					w[j]=w[i];  p[j]=p[i];	
					w[i]=temp1; p[i]=temp2;
				}
			}
		}
	}
}
//create the graph g given data(KNN) n
int populateGraph(GRAPH** g,int gSize,NODE* n,int nSize,int nData)
{
	int i,j,k,size=0,a=0,prr[nData],wrr[nData],ind;
	NODE *p=n,*q=n;
	int flag=false;
	
	for (i=0;i<gSize;i++)
	{
		for (k=0;k<nData;k++)
		{ prr[k]=0; wrr[k]=0; }

		a=0;

		for (j=0;j<nData;j++)
		{
			//find index (data of KNN) in jth node(nbr)
			ind = (int)(p->data[j]);	
			
			//go to the index found above	
			q=n;
			while(q->index!=ind)
			{ q=q->next; }	
		
			//check if the node at that index contains the 'jth' node as its index
			flag=false;
			for (k=0;k<nData;k++)
			{
				if ( (int)(q->data[k])==p->index )
				{ flag=true; break; }
			}

			//if found add to zeroed array(prr,wrr) respectively
			if (flag==true)
			{
				prr[a]=ind;
				wrr[a]=findWeight(p,q,nData);
				a++;
			}
		}

		p=p->next;

		sortGraph(prr,wrr,a);
		*g=addGraph(*g,i+1,a,prr,wrr);
	}	
}

//return node with specified values (initialize it)
NODE* getNode(NODE* n,int ind,int size,double d[])
{
	n = malloc( sizeof(NODE) );
	n->next = NULL;
	n->last = NULL;
	n->index = ind;
	n->data = malloc( size*sizeof(double) );

	for (int i=0;i<size;i++)
	{
		n->data[i] = d[i];
	}

	return n;
}

//Add a Node to DLL head with index i and data(d) of specified size
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

//print given List
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

//free given List
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

//return GRAPH with specified values (initialize it)
GRAPH* getGraph(GRAPH* n,int ind,int size,int p[],int w[])
{
	n = malloc( sizeof(GRAPH) );
	n->next = NULL;
	n->last = NULL;
	n->index = ind;
	n->size = size;
	n->pnt = malloc( size*sizeof(int) );
	n->wght = malloc( size*sizeof(int) );

	for (int i=0;i<size;i++)
	{
		n->pnt[i] = p[i];
		n->wght[i] = w[i];
	}

	return n;
}

//Add a graph node to DLL head with index i and data-point(p) and weight(w) of specified size
GRAPH* addGraph(GRAPH* head,int ind,int dataSize,int d[],int w[])
{
	GRAPH *new;
	new = getGraph(new,ind,dataSize,d,w);

	if (head==NULL)
	{
		head = new;
		return head;
	}

	else
	{
		GRAPH *p;
		p = head;
		while ( p->next!=NULL )
		{ p = p->next; }
		p->next = new;
		new->last = p;
	}

	return head;
}

//print given GRAPH
void printGraph(GRAPH* head)
{
	while(head!=NULL)
	{
		printf("(%2d [ ",head->index);
		for (int i=0;i<head->size;i++)
		{ printf("(%d,%d) ",head->pnt[i],head->wght[i]); }
		printf("] )\n");
		head=head->next;
	}
}

//deallocate memory for the GRAPH
void freeGraph(GRAPH* head)
{
	GRAPH* temp;
	while(head!=NULL)
	{
		temp=head;
		head=head->next;
		free(temp->pnt);
		free(temp->wght);
		free(temp);
	}
}

//selection sort
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
