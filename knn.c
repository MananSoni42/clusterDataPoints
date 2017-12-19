#include<stdio.h>
#include<stdlib.h>
#include<math.h>

#define MAX 64

//N->Number of Data points  D->Dimensions of each
//k,e,min pts are parameters for the algorithm
int N,D,k,e,minPts;
float inf=1.0/0.0;

//data is stored with an index and its dimensions
struct point
{ 
	int index;

	//dimensions (D-tuples of points)
	double dim[MAX];
};

typedef struct point POINT;

//similarity matrix for given data
struct mat
{
	int index;

        //dist of ith point from jth point(N such points)
        double dist[MAX];
};	

typedef struct mat MATRIX;


int getData(POINT []);
int printData(POINT []);
double dist(POINT,POINT);
int populateMatrix(MATRIX [],POINT []);
int printList(MATRIX []);
int kNearest(MATRIX [],int ,int [][k]);
int printNeighbours(int,int [][k]);


int main()
{ 
	int i,j;
	scanf("%d %d %d %d %d",&N,&D,&k,&e,&minPts);
	
	//declare array to store the data points
	POINT data[N];

	//declare an array to store the dist between any 2 points
	MATRIX m[N];

	//input the data
        getData(data);

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

	printf("\n"); return 0;
}

//get Data from File 
//Format: N sets each consists of D space seperated values
int getData(POINT data[])
{
        int i,j;	
	for (i=0;i<N;i++)
	{	
	       data[i].index=i+1;	
	       for (j=0;j<D;j++)
	       {
		       scanf("%lf",&data[i].dim[j]);

	       }  
	}
}

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

/*
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
*/

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
