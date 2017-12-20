#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define MAX 64

//N->Number of Data points  D->Dimensions of each
//k,e,min pts are parameters for the algorithm
int N,D,k,e,minPts;
float inf=1.0/0.0;	

struct node
{
	int index;
	double *data;
	struct node *next,*last;
};

typedef struct node NODE;

int getData(NODE**,int);

NODE* getNode(NODE*,int,int,double []);
NODE* addNode(NODE*,int,int,double []);
void printList(NODE*,int);
void freeList(NODE*);

int main()
{ 
	int i,j;
	scanf("%d %d %d %d %d",&N,&D,&k,&e,&minPts);
	
	//declare DLL to store the data points
	NODE *point=NULL; int p_size=D;

	//declare DLL to store the dist between any 2 points(Similarity Matrix)
	NODE *m; int m_size=N;

	//input the data
        getData(&point,p_size);

	//print the data
	printList(point,p_size);

	//free memory
	freeList(point);
/*
        //populate the similarity matrix
	populateMatrix(m,data);

	int Neighbour[N][k];

	//display the data
	printf("\nData: \n");
	printData(data);
	
	//display Similarity Matrix
	printf("\nOriginal Similarity Matrix: \n");
	printList(m);
        
	//find the k-nearest neighbours
	kNearest(m,k,Neighbour);

	//display Similarity Matrix
	printf("\nSimilarity Matrix: \n");
	printList(m);

	//display k-nearest neighbours
	printf("\nk-Nearest Neigbhours: \n");
	printNeighbours(k,Neighbour);
*/
	printf("\n"); return 0;
}

//get Data from File 
//Format: N sets each consists of D space seperated values
int getData(NODE** p,int size)
{
	int i,j;
	double inp[size];
        
	for (i=0;i<N;i++)
	{ 
		for(j=0;j<size;j++)
		{
			scanf("%lf",&inp[j]);
		}
		*p = addNode(*p,i+1,D,inp);
	}
}

/*
//print the list 
int printData(POINT data[])
{
	int i,j;
	for (i=0;i<N;i++)
	{   
		//print the index
		printf("(%2d, [",data[i].index);
		for (j=0;j<D;j++)
		{ 
			//print the last value and omit the ,
			if (j==D-1)
			{ printf("%3.2lf",data[i].dim[j]); continue; }
		
			//print the data
			printf("%3.2lf,",data[i].dim[j]); 

		}
		printf("] )\n");
	}

}

//calculate the distance between any two POINTS
double dist(POINT a,POINT b)
{ 	
	long double d=0.0; double dist=0.0;
	
	//find the euclidian distance between the two points
	for (int i=0;i<D;i++)
	{ 
		d = d + pow((a.dim[i]-b.dim[i]),2);
	}
        dist = sqrt(d);

	return dist;
}	

//compute the Similarity Matrix
int populateMatrix(MATRIX a[],POINT src[])
{
	int i,j;
        for (i=0;i<N;i++)
	{
		a[i].index=i+1;
		for (j=0;j<N;j++)
		{ 
			if (i==j)
			{ a[i].dist[j]=inf; }
			else
			{ a[i].dist[j]=dist(src[i],src[j]); }
		}
	}
}

//print the list containing distance of two points
int printList(MATRIX arr[])
{
	int i,j;
	for (i=0;i<N;i++)
	{ 
		//print index
		printf("( %2d [ ",arr[i].index);
		for (j=0;j<N;j++)
		{
			//print data
			printf("%3.2lf ",arr[i].dist[j]);
		}
		printf("] )\n");
	}
}

int kNearest(MATRIX a[],int k,int n[][k])
{ 
	int i,j,min;
  	float temp;

	for (int l=0;l<N;l++)
	{ 
	  for(i=0;i<k;i++)
          { 
		  min=i;
                  for (j=i;j<N;j++)
		  { 
			  if (a[l].dist[j]<=a[l].dist[min])
		          { min=j; }
		  }
                  n[l][i]=min+1;
	          temp=a[l].dist[min];
	          a[l].dist[min]=a[l].dist[i];
	          a[l].dist[i]=temp;
          }
	}
}


int kNearest(int k,int arr[][k],MATRIX src[])
{
	int i,j;
	for (i=0;i<N;i++)
	{
		for (j=0;j<k;j++)
		{ 
			arr[i][j]=src[i].index[j];
		}
	}
}


int printNeighbours(int k,int arr[][k])
{ 
	int i,j;
	for (i=0;i<N;i++)
	{      
		for (j=0;j<k;j++)
		{ printf("%d ",arr[i][j]); }
		printf("\n");
	}
}
*/

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
