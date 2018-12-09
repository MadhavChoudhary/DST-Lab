#include<stdio.h>
#include<stdlib.h>

typedef struct node
{
	struct node *left;
	struct node *right;
	int data;

}node;

node *createNode(int data)
{

	node *n = (node *)malloc(sizeof(node));

	n->left = NULL;
	n->right = NULL;
	n ->data = data;

	return n;
}

node *insert(node *root,int key)
{

	if(root == NULL)
		root = createNode(key);
	
	else if(key>root->data)
		root->right = insert(root->right,key);

	else if(key<root->data)
		root->left = insert(root->left,key);

	return root;
}

node *search(node *root,int key,node *temp[],int *index)
{
	temp[*index] = root;
	*index = *index+1;

	if(key>root->data)
		search(root->right,key,temp,index);

	else if(key<root->data)
		search(root->left,key,temp,index);

	else return root;
}

void inorder(node *root)
{
	//printing in inorder format
	if(root == NULL)
		return;

	inorder(root->left);
	printf("%d ",root->data);
	inorder(root->right);
}

void preorder(node *root)
{
	if(root == NULL)
		return;

	printf("%d ",root->data);
	preorder(root->left);
	preorder(root->right);

}
void postorder(node *root)
{
	if(root == NULL)
		return;

	postorder(root->left);
	postorder(root->right);
	printf("%d ",root->data);

}

void levelorder(node *root,int temp[],int n,int Hash[][n],int h)
{
	if(root == NULL)
		return;

	Hash[h][temp[h]] = root->data;
	temp[h]++; 

	levelorder(root->left,temp,n,Hash,h+1);
	levelorder(root->right,temp,n,Hash,h+1);	
}

void getPath(node *root,int path[],int index)
{	
	int i=0;

	if(root == NULL)
		return;

	else if(root->left == NULL && root->right == NULL)
	{
		path[index]=root->data;
		for(i=0;i<=index;i++)
			printf("%d ",path[i]);
		printf("\n");
		return;
	}

	path[index]=root->data;

	getPath(root->left,path,index+1);
	getPath(root->right,path,index+1);

}

int findheight(node *root)
{
	int h1,h2,h;
	
	if(root == NULL)
		return 0;

	h1 = findheight(root->left);
	h2 = findheight(root->right);
	h = (h1>h2)?h1:h2;
	h++;

	return h;

}

node *Q1(node *root,int n)
{
	int i,k;

	for(i=0;i<n;i++)
	{
		scanf("%d",&k);
		root = insert(root,k);
	}

	return root;
}

void Q2(node *root,int n)
{

	int height,i,j;

	height = findheight(root);

	int Hash[height][n];
	int temp[height];

	for(i=0;i<height;i++)
		temp[i]=0;
	
	printf("Preorder : ");
	preorder(root);
	printf("\n");

	printf("Inorder : ");
	inorder(root);
	printf("\n");

	printf("Postorder : ");
	postorder(root);
	printf("\n");

	printf("Levelorder : ");
	levelorder(root,temp,n,Hash,0);

	for(i=0;i<height;i++)
		for(j=0;j<temp[i];j++)
				printf("%d ",Hash[i][j]);

	printf("\n");

}

void Q3(node *root,int n)
{

	int path[n];
	int index = 0;

	printf("All Possible paths:\n");
	getPath(root,path,index);

}

void Q4(node *root,int n,int key1,int key2)
{

	node *temp1[n];
	node *temp2[n];
	int index1 = 0,index2 = 0;
	int i;

	search(root,key1,temp1,&index1);
	search(root,key2,temp2,&index2);

	for(i=0;;i++)
		if(i>=index1 || i>=index2 || temp1[i]->data != temp2[i]->data)
			break;
	
	printf("Common Ancestor : %d\n",temp1[i-1]->data);

}

void Q5(node *root,int n,int key)
{
	node *temp[n];
	int index = 0;
	int i,x;
	node *check;

	search(root,key,temp,&index);

	if(temp[index-1]->right != NULL)
	{
		check = temp[index-1]->right;
		while(check->left != NULL)
			check = check->left;
		printf("Next Inorder Transversal: %d\n",check->data);
	}

	else
	{
		x = temp[index-1]->data;
		index--;

		for(;index>=0;index--)
			if(temp[index]->data>x)
				break;

		if(index>=0)
			printf("Next Inorder Transversal: %d\n",temp[index]->data);
		else
			printf("There is no Inorder Transversal\n");
	}

}

int main()
{
	node *root = NULL;
	int n;
	int key;
	int key1,key2;

	scanf("%d",&n);

	root = Q1(root,n);

	scanf("%d %d",&key1,&key2);
	scanf("%d",&key);

	printf("\n");
	Q2(root,n);
	printf("\n");
	Q3(root,n);
	printf("\n");
	Q4(root,n,key1,key2);
	printf("\n");
	Q5(root,n,key);
	printf("\n");

	return 0;
}