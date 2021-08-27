#include <stdio.h>
#include <stdlib.h>
#include "header.h"
#include <string.h>

int check(majorTerm *head,char *ch)
{
	printf("i m in check");
	int i;
	for(i=0;i<strlen(head->name)&&i<strlen(ch);i++)
	{
		printf("!!%c %c!!",head->name[i],ch[i]);
		if(head->name[i]<ch[i])
			return 1;
		else if(head->name[i]>ch[i])
			return -1;
		else
			continue;
	}
	if(i<strlen(ch))
		return 1;
	else if(i<strlen(head->name))
		return -1;
	else return 0;
}

majorTerm *pos(majorTerm *head,char *ch)
{
	printf("Im in pos ");
	int n=check(head,ch);
	printf("%d %s", n,head->name);
	if(n==1)
	{
		printf("went in right\n");
		if(head->right==NULL)
		{
			head->right=malloc(sizeof(majorTerm));
			return head->right;
		}

		else {
				printf("%s",(head->right)->name);
			return pos(head->right,ch);
		}

	}
	else if(n==-1)
	{
		printf("went in left\n");
		if(head->left==NULL)
		{
			head->left=malloc(sizeof(majorTerm));
			return head->left;
		}
		else return pos(head->left,ch);
	}
	else
	{
		printf("Entered term already exists\n");
		return NULL;
	}
}

int scheck(subTerm *head,char *ch)
{
	printf("i m in scheck");
	int i;
	for(i=0;i<strlen(head->name)&&i<strlen(ch);++i)
	{
		if(head->name[i]<ch[i])
			return 1;
		else if(head->name[i]>ch[i])
			return -1;
		else
			continue;
	}
	if(i<strlen(ch))
		return 1;
	else if(i<strlen(head->name))
		return -1;
	else return 0;
}

subTerm * spos(subTerm *head,char *ch)
{
	printf("i m in spos");
	int n=scheck(head,ch);
	if(n==1)
	{
		printf("went in right\n");
		if(head->right==NULL)
		{
			head->right=malloc(sizeof(subTerm));
			return head->right;
		}
		else return spos(head->right,ch);
	}
	else if(n==-1)
	{
		printf("went in left\n");
		if(head->left==NULL)
		{
			head->left=malloc(sizeof(subTerm));
			return head->left;
		}
		else return spos(head->left,ch);
	}
	else
	{
		printf("Entered term already exists\n");
		return NULL;
	}
}

majorTerm *create(void)
{
	char ch,*name=malloc(sizeof(char)*50),ch1;
	majorTerm *mhead,*temp;
	subTerm *shead,*tmp;
	int n;
	mhead=(majorTerm *)malloc(sizeof(majorTerm));
	mhead->name="M";
	mhead->left=NULL;
	mhead->right=NULL;
	while(1)
	{
		printf("Do u want to create Major Term for your index\nY-for yes\nN-for no\nif u entered any other character program will automatically Terminate");
		scanf(" %c",&ch);
		switch(ch)
		{
			case 'Y':printf("please Enter the name of major Term :");
					 scanf("%s",name);
					 temp=pos(mhead,name);
					 while(temp==NULL)
					 {
					 	printf("please Enter the name of major Term :");
					 	scanf("%s",name);
					 	temp=pos(mhead,name);
					 }
					 printf("%d %d",temp,mhead->left);
					 printf("%d %d",temp,mhead->right);
					 temp->name=name;
					 temp->left=NULL;
					 temp->right=NULL;

					 printf("Please Enter the page number :");
					 scanf("%d",&temp->pg_no);
					 
					 printf("how many places this term has occured :");
					 scanf("%d",&n);
					 if(n!=0)
					 	temp->occured=(int *)malloc(sizeof(int)*n);
					 else
					 	temp->occured=NULL;
					 for(int i=0;i<n;++i)
					 {
					 	printf("Enter the page no. where the term has occured :");
					 	scanf("%d",&temp->occured[i]);
					 }

					 temp->next=(subTerm *)malloc(sizeof(subTerm));
					 (temp->next)->name="M";
					 (temp->next)->left=NULL;
					 (temp->next)->right=NULL;

					while(1)
					{
					 	printf("Do u want to create subterm for this major term\nY-for yes\nN-for no\nif u enetred any other character program will automatically Terminate");
					 	scanf(" %c",&ch1);
					 	switch(ch1)
					 	{
					 		case 'Y':printf("please Enter the name of subterm :");
					 				 scanf("%s",name);
					 				 tmp=spos(temp->next,name);
					 				 while(tmp==NULL)
					 				 {
					 				 	printf("please Enter the name of subterm :");
					 				 	scanf("%s",name);
					 				 	tmp=spos(temp->next,name);
					 				 }
 				 					 tmp->left=NULL;
									 tmp->right=NULL;

					 				 printf("please enter the page number :");
					 				 scanf("%d",&tmp->pg_no);

					 				 printf("how many places the term has occured :");
					 				 scanf("%d",&n);
					 				 tmp->occured=(int *)malloc(sizeof(int)*n);
					 				 for (int i = 0; i < n; ++i)
					 				 {
					 				 	printf("Enter the page number where it is occured :");
					 				 	scanf("%d",&tmp->occured[i]);
					 				 }
					 				 break;
			 				case 'N':tmp=NULL;
			 						break;
			 				default : printf("please Enter the right choice next time\n");
									continue;
						}
		 				if(ch1=='N')break;
	 				}
					break;
			case 'N':break;
			default : printf("please Enter the right choice next time\n");
						continue;
		}
		if(ch=='N')break;
	}
	return mhead;
}

void displayIndex(majorTerm *mhead)
{
	if(mhead!=NULL)
	{
		displayIndex(mhead->left);
		printf("%s\n",mhead->name);
		displayIndex(mhead->right);
	}
}