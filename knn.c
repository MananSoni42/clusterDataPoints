#include<stdio.h>
#define MAX 64

int N,D;

struct point
{ 
	int index;
        double dim[MAX];
};

typedef struct point POINT;

int getData(POINT []);
int printData(POINT []);

int main()
{ 
	int i,j,k,e,minPts;
	scanf("%d %d %d %d %d",&N,&D,&k,&e,&minPts);
	POINT data[N];

        getData(data);
	printData(data);

	return 0;
}

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

int printData(POINT data[])
{
	int i,j;
	for (i=0;i<N;i++)
	{   
		printf("(%2d, [",data[i].index);
		for (j=0;j<D;j++)
		{ 
			if (j==D-1)
			{ printf("%3.2lf",data[i].dim[j]); continue; }
		
			printf("%3.2lf,",data[i].dim[j]); 

		}
		printf("] )\n");
	}
}
       	
