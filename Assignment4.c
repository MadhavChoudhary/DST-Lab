#include<stdio.h>
#include<math.h>
#include<time.h>
#include<stdlib.h>

#define NMAX 1000

typedef struct photo
{
	int id;
	int rat;
}photo;

photo heap[NMAX];
int heapSize;
int IDX[NMAX];
int pht=0;

void init();
void makeHeap();
void moveDOWN(int );
void moveUP(int );
void upVote(int *);
void downVote(int *);
void insert(int *);
void delete(int *);
void currentState();
void swap(int ,int );
int eval(char [],char [],int *);


int main()
{
	int *id;
	char ans[100];
	srand(time(NULL));

	printf("Enter the initial number of photos.\n");
	scanf("%d",&heapSize);

	init();
	makeHeap();

	printf("What do you want to do? Press heap --help to see options...\n");

	while(1)
	{
		currentState();

		scanf("%s",ans);

		if(eval(ans,"insert",id))
			insert(id);

		else if(eval(ans,"upVote",id))
			upVote(id);

		else if(eval(ans,"downVote",id))
			downVote(id);

		else if(eval(ans,"delete",id))
			delete(id);

		else if(eval(ans,"quit",id))
			break;

		else
		{
			printf("\n\nThese are the functions:\n");
			printf("insert(photorating)\n");
			printf("upVote(photoid)\n");
			printf("downVote(photoid)\n");
			printf("delete(photoid)\n");
			printf("quit\n\n\n");
		}

	 }
		return 0;	
}

void init()
{
	int i;

	for(i=0;i<heapSize;i++)
	{
		heap[i].id = pht++;
		heap[i].rat = rand()%11;
	}

	for(i=0;i<heapSize;i++)
	{
		IDX[heap[i].id] = i;
	}

}

void makeHeap()
{
	int i = heapSize/2-1;

	for(;i>=0;i--)
	{
		moveDOWN(i);
	}
}

void moveDOWN(int i)
{
	if(i>heapSize/2-1)
		return;

	int l = 2*i + 1;
	int r = 2*i + 2;
	int max = i;

	if(l<heapSize && heap[l].rat>heap[max].rat)
		max = l;
	if(r<heapSize && heap[r].rat>heap[max].rat)
		max = r;

	if(max!=i)
	{
		swap(i,max);
		moveDOWN(max);
	}

}

void moveUP(int i)
{
	int p = (i-1)/2;

	if(p>=0 && heap[i].rat>heap[p].rat)
	{	
		swap(p,i);
		moveUP(p);
	}

}

void upVote(int *id)
{
	int i = IDX[*id];
	heap[i].rat++;
	moveUP(i);
}

void downVote(int *id)
{
	int i = IDX[*id];
	if(heap[i].rat>0)
		heap[i].rat--;
	moveDOWN(i);
}

void insert(int *rat)
{
	heapSize++;
	heap[heapSize-1].id = pht++;
	heap[heapSize-1].rat = *rat;
	IDX[heap[heapSize-1].id] = heapSize-1;
	moveUP(heapSize-1);

}

void delete(int *id)
{
	int i = IDX[*id];

	if(i != -1)
	{
		swap(i,heapSize-1);

		IDX[*id] = -1;

		heapSize--;
		moveDOWN(i);
	}
}

void currentState()
{
	int i;

	printf("Current Heap (%d nodes used)\n",heapSize);
	for(i=0;i<heapSize;i++)
		printf("%d ( %d %d )  ",i,heap[i].id,heap[i].rat);

	printf("\n");

	printf("Current Hash (%d cells used)\n",pht);
	for(i=0;i<pht;i++)
			printf("%d ( %d )  ",i,IDX[i]);

	printf("\n\n");

}

void swap(int i,int j)
{
	photo temp;

	IDX[heap[i].id] = j;
	IDX[heap[j].id] = i;

	temp = heap[i];
	heap[i] = heap[j];
	heap[j] = temp;

}

int eval(char str1[],char str2[],int *id)
{
	int i;
	int l=0;

	while(str2[l]!='\0')
		l++;

	for(i=0;i<l;i++)
		 if(str1[i] != str2[i])
			break;

	*id = str1[i+1];
	*id = *id - 48;

	return i == l;

}