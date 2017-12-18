#include<stdio.h>
#include<math.h>

#define MAX 64

//N->Number of Data points  D->Dimensions of each
int N,D;
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
struct list
{
	int index;

        //dist of ith point from jth point
        double dist[MAX];
};	

typedef struct list LIST;

int getData(POINT []);
int printData(POINT []);
double dist(POINT,POINT);
int populateMatrix(LIST [],POINT []);
int printList(LIST []);

int main()
{ 
	//k,e,min pts are parameters for the algorithm
	int i,j,k,e,minPts;
	scanf("%d %d %d %d %d",&N,&D,&k,&e,&minPts);
	
	//declare array to store the data points
	POINT data[N];

	//declare an array to store the dist between any 2 points
	LIST simMatrix[N];

	//input the data
        getData(data);

        //populate the similarity matrix
	populateMatrix(simMatrix,data);

	//display the data
//	printData(data);

	//display Similarity Matrix
	printList(simMatrix);

	return 0;
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

int populateMatrix(LIST a[],POINT src[])
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
int printList(LIST arr[])
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
