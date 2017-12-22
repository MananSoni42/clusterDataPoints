#include<stdio.h>

void selection(int a[],int n)
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

int main()
{ int n,i;
  printf("How many numbers do you want to sort: "); 
  scanf("%d",&n);
  printf("\n");

  int a[n];
  
  for (i=0;i<n;i++)
  { 
    printf("Enter %d Number: ",i+1); 
    scanf("%d",&a[i]);
  } 
 
  printf("\n\nUnsorted Array: \n");

  for (i=0;i<n;i++)
  { printf(" %d ",a[i]); }

  selection(a,n);

  printf("\n\nSorted Array: \n");
 
  for (i=0;i<n;i++)
  { printf(" %d ",a[i]); }
  

  return 0;
}
