#include<stdio.h>

//a new structure point
typedef struct point
{
	float X;
	float Y;
	float Slope;
}point;

//bottommost point is global variable
point bottom;

void mergesort(point arr[],int start,int end,int size);
void merge(point arr[],int start,int middle,int end,int n);
int comp(point ,point );

int main()
{
	int n,i;
	point temp;

	printf("Enter the numbers of set points:\n");
	scanf("%d",&n);

	point Array[n];

	printf("Enter the points:\n");

	//scanning the points
	for(i=0;i<n;i++)
	{
		scanf("%f %f",&Array[i].X,&Array[i].Y);
	}

	temp = Array[0];

	int index=0;

	//finding the bottommost point and its index
	for(i=1;i<n;i++)
	{
		if(Array[i].Y<temp.Y)
		{
			temp = Array[i];
			index=i;			
		}

		else if(Array[i].Y==temp.Y)
		{
			if(Array[i].X<temp.X)
			{
				temp = Array[i];
				index=i;
			}
				
		}

	}

	//swapping
	temp=Array[0];
	Array[0]=Array[index];
	Array[index]=temp;
	bottom=Array[0];

	//sort w.r.t to slope
	mergesort(Array,1,n-1,n);

	printf("The convex Hull points are:\n");

	point list[n];
	int top=-1;
	float turn;

	//stack array
	list[++top]=bottom;
	list[++top]=Array[1];

	for(i=2;i<n;)
	{

		turn=(list[top].Y-list[top-1].Y)*(Array[i].X-list[top].X)
				-(list[top].X-list[top-1].X)*(Array[i].Y-list[top].Y);

		if(turn<0)
		{
			list[++top]=Array[i];
			i++;
		}
		else if(turn>0)
		{
			top--;
		}

		else
		{
			list[top]=Array[i];
			i++;
		}
	}

	for(i=top;i>=0;i--)
	{
		printf("<%.2f %.2f>  ",list[i].X,list[i].Y);
	}

	printf("\n");

	return 0;

}

void mergesort(point arr[],int start,int end,int size)
{

	if(start>=end)
		return;

	int middle=(start+end)/2;

	mergesort(arr,start,middle,size);
	mergesort(arr,middle+1,end,size);

	merge(arr,start,middle,end,size);
}

void merge(point arr[],int start,int middle,int end,int n)
{

	int size1,size2;
	int i=0,j=0,k=0;

	size1=middle-start+1;
	size2=end-middle;

	point a1[size1],a2[size2];

	for(i=0;i<size1;i++)
		a1[i]=arr[start+i];
	for(i=0;i<size2;i++)
		a2[i]=arr[middle+1+i];
	i=0;k=start;

	while(i<size1 && j<size2)
	{

		if(comp(a1[i],a2[j])==0)
		arr[k++]=a1[i++];

		else if(comp(a1[i],a2[j])==1)
		arr[k++]=a2[j++];

		else
		arr[k++]=(a1[i].X<a2[j].X)?a1[i++]:a2[j++];
	}

	if(i>=size1)
		while(j<size2)
			arr[k++]=a2[j++];

	else if(j>=size2)
		while(i<size1)
			arr[k++]=a1[i++];

}

int comp(point a,point b)
{
	float turn=(a.Y-bottom.Y)*(b.X-a.X)
				-(a.X-bottom.X)*(b.Y-a.Y);

	if(turn <0)
		return 0;
	else if(turn >0)
		return 1;
	else return 2;

}