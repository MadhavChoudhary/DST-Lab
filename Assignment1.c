#include <stdio.h>

//logic in sort function for Q1
//logic in min_path function for Q2 and for only.
// for the Q2 ,the movement can only be in two directions so, there can we more than 1 possible paths
// but both will be identical and there will be no best path. only one path.

//reading array
void readarr(int arr[],int n)
{	
	int i;
	printf ("Enter the elements:\n");

	for(i=0;i<n;i++)
		scanf("%d",&arr[i]);

}

//printing array
void printarr(int arr[],int n)
{
	int i;
	for(i=0;i<n;i++)
		printf("%d ",arr[i]);

	printf("\n");
}

//reverse array function
void revarr(int arr[],int i)
{

	int temp,index=0;

	for(;index<i;index++,i--)
	{

		temp=arr[index];
		arr[index]=arr[i];
		arr[i]=temp;

	}
}

//sorting function
void sort(int arr[],int n)
{
	int i;

	//basis condition 
	if(n==1)
		return;

	//first sort 0 to n-1 elements
	sort(arr,n-2);

	//reverse the array along with the nth element
	revarr(arr,n-1);

	//compare and find the place for nth number which is now at index 0
	for(i=n-1;i>0;i--)
	{
		if(arr[i]>arr[0])
		{
			//putting it in the required place
			revarr(arr,i);

			//rearranging the left side numbers
			revarr(arr,i-1);

			break;
		}
	}

	//reverse back to get ascending order
	revarr(arr,n-1);

}

void Q1()
{
	int n,t,j;

	printf("Enter the number of test cases:");
	scanf("%d",&t);

	for(j=1;j<=t;j++)
	{
		printf("\n\n....This is test case %d....\n",j);

		printf("Enter the size of array:\n");
		scanf("%d",&n);

		int arr[n];

		readarr(arr,n);

		sort(arr,n);

		printarr(arr,n);

		printf("\n");

	}

}

//finding shortest path (trivial in given possible movements)
int min_path(int x0,int y0,int x,int y,int path[][100],int width,int height,int field[width][height])
{
	// moving out of the field 
	if(x<x0 || y<y0)
		return -1;

	//using dynamic programming for storing calculated path lenghts 
	else if(path[x][y]==0)
	{

		//starting point
		if(x==x0 && y==y0)
			path[x][y]=0;

		else
		{
			int path1,path2;

			//main logic
			path1=(field[x-1][y]==1)?min_path(x0,y0,x-1,y,path,width,height,field):-1;
			path2=(field[x][y-1]==1)?min_path(x0,y0,x,y-1,path,width,height,field):-1;

			//selection of better path
			if(path1==0 || path1==-1)
			{
				if(path2==0 || path2==-1)
				{
					path[x][y]=-1;
				}

				else
					path[x][y]=path2;
			}

			else
			{
				if(path2==0 || path2==-1)
				{
					path[x][y]=path1;
				}

				else
					path[x][y]=(path1>path2)?path2:path1;
			}
			
		}

	}

	return path[x][y]+1;

}

//printing the shortest path
//by this time we know that there is definitely a path existing
void printpath(int path[100][100],int x,int y,int x0,int y0)
{
	printf("\n");

	while(x0<=x && y0<=y)
	{
		printf("< %d %d > ",x0,y0);

		if(path[x0+1][y0]==path[x0][y0]+1)
			x0++;
		else 
			y0++;
	}

	printf("\n");
}

void Q2()
{
	int t,i,j,k,check;
	printf("Enter the number of test cases:");
	scanf("%d",&t);

	for(i=1;i<=t;i++)
	{
		printf("\n\n....This is test case %d...\n",i);

		int width,height;
		int path[100][100]={};

		printf("Enter the width,height of field\n");
		scanf("%d %d",&width,&height);

		int field[width][height];

		int a,b;

		printf("Enter the field\n");

		for(b=height-1;b>=0;b--)
		{
			for(a=0;a<width;a++)
			{
				scanf("%d",&field[a][b]);
			}
		}

		//starting and ending points for path are set
		int x=width-1,y=height-1,x0=0,y0=0;

		check=min_path(x0,y0,x,y,path,width,height,field);

		if(check==0)
			printf("There is no path\n");
		else
			printpath(path,x,y,x0,y0);

	}

}

int main()
{
	int q;

	printf("Question no?");
	scanf("%d",&q);

	switch(q)
	{
		case 1:Q1();break;
		case 2:Q2();break;
		default:printf("Enter the proper q.no");
	}

	return 0;
}