#include<stdio.h>

void insertion(int a[],int n)
{ int i,j,key;
  for(i=0;i<n;i++)
  { key=a[i]; j=i-1;	
    while (j>=0 && a[j]>key)
    { 
     a[j+1]=a[j];
     j--;
    }
    a[j+1]=key;
  }
}

int main()
{ int n,i;
  
  printf("How many numbers do you want to sort: "); 
  scanf("%d",&n);
  printf("\n");
  
  int a[n];
  
  for (i=0;i<n;i++)
  { printf("Enter %d Number: ",i+1); scanf("%d",&a[i]); } 
 
  printf("\n\nUnsorted Array: \n");

  for (i=0;i<n;i++)
  { printf(" %d ",a[i]); }

  insertion(a,n);

  printf("\n\nSorted Array: \n");
 
  for (i=0;i<n;i++)
  { printf(" %d ",a[i]); }
  
  printf("\n");

  return 0;
} 
