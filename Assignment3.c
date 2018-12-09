#include<stdio.h>

void Q1();
void Q2();
int mergesort(int [],int ,int ,int );
int merge(int [],int ,int ,int ,int );
int mod(int );

int main()
{
	int q;

	//selecting based on question number
	printf("Enter the question no.\n");
	scanf("%d",&q);

	switch(q)
	{
		case 1:Q1();break;
		case 2:Q2();break;
		default:printf("Enter a valid question.\n");break;
	}

	return 0;
}

void Q2()
{
	//there are many methods to do this.
	//method 1 is to do linear search comparing amplitudes which takes 0(n*k)
	//method 2 is to sort and search which takes 0(nlogn)
	//method 3 is to use minheap(heapsort) of differences which takes n or klogn (whichever is smaller)
	//method 4 is to use very simple hash table and takes 0(n+m) where m is maxelement.
	//doing in method 4 because we are dealing with intergers only and not decimals.

	int i,j,k,key,n;

	printf("Enter n:\n");
	scanf("%d",&n);

	int list[n];

	printf("Enter values:\n");
	//taking input
	for(i=0;i<n;i++)
		scanf("%d",&list[i]);

	//finding max magnitude element
	int max=0;

	for(i=0;i<n;i++)
		if(max<mod(list[i]))
			max=mod(list[i]);

	int hash[2*max+1];

	//filling hash array with zeroes
	for(i=0;i<2*max+1;i++)
		hash[i]=0;

	//filling hash array with frequency of elements
	for(i=0;i<n;i++)
		hash[max+list[i]]++;

	printf("Enter key and k:\n");
	scanf("%d %d",&key,&k);

	i=max+key;
	j=i;

	//checking for close numbers in hash array linearly
	//this actually takes 0(k) time if observed carefully
	while(1)
	{
		while(hash[i]!=0 && i>=0 && k>0)
		{
			printf("%d ",i-max);
			hash[i]--;
			k--;
		}

		while(hash[j]!=0 && j<2*max+1 && k>0)
		{
			printf("%d ",j-max);
			hash[j]--;
			k--;
		}

		if(k<=0) break;

		i--;
		j++;

	}

	printf("\n");
}

int mod(int x)
{
	if(x<0)
		return -x;
	else
		return x;
}

void Q1()
{
	//doing by changing mergesort original ,takes 0(nlogn)
	int n,i;

	printf("Enter n:\n");
	scanf("%d",&n);

	int arr[n];

	printf("Enter the values:\n");

	for(i=0;i<n;i++)
	{
		scanf("%d",&arr[i]);
	}

	printf("No of inversions: %d\n",mergesort(arr,0,n-1,n));

}

int mergesort(int arr[],int start,int end,int size){

	
	int count=0;

	if(start>=end)
		return 0;

	int middle=(start+end)/2;

	//returned values of no of inversions
	count=mergesort(arr,start,middle,size);
	count+=mergesort(arr,middle+1,end,size);

	count+=merge(arr,start,middle,end,size);

	return count;
}

int merge(int arr[],int start,int middle,int end,int n){

	int size1,size2,count=0;
	int i=0,j=0,k=0;

	size1=middle-start+1;
	size2=end-middle;

	int a1[size1],a2[size2];

	for(i=0;i<size1;i++)
		a1[i]=arr[start+i];
	for(i=0;i<size2;i++)
		a2[i]=arr[middle+1+i];
	i=0;k=start;

	while(i<size1 && j<size2){

		if(a1[i]<=a2[j])
		arr[k++]=a1[i++];

		//this is the modification
		else
		{
			arr[k++]=a2[j++];
			//if this number is greater, the all numbers to the right of this number
			//in the left array will be greater since the array is in ascending order

			//so total inversions will be size of right array - index 
			count+=(size1-i);			
		}

	}

	if(i>=size1)
		while(j<size2)
			arr[k++]=a2[j++];

	else if(j>=size2)
		while(i<size1)
			arr[k++]=a1[i++];

	return count;

}