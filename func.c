#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "header.h"

subTerm *screate(char *str) //creating the subterm
{
	int n,i;
	subTerm *shead;
	if((shead=malloc(sizeof(subTerm)))==NULL)
	{
		printf("cannot allocate memery to subTerm");
		exit(1);
	}
	strcpy(shead->name,str);
	shead->occured=NULL;

	if(*shead->name!='M' && strlen(shead->name)>1)
	{
		printf("please Enter the pg_no. for sub Term :");
		scanf("%d",&shead->pg_no);
		if(shead->pg_no<0)
		{
			printf("pg number should be positive");
			printf("please Enter the pg_no.");
			scanf("%d",&shead->pg_no);
		}

		printf("please Enter the number of page number where and all this sub term has occured :");
		scanf("%d",&n);
		shead->size=n;
		if(n>0)
		{
			if((shead->occured=malloc(sizeof(int)*n))==NULL)
			{
				printf("couldnt allocate memory");
				exit(2);
			}
			for(i=0;i<n;++i)
			{
				printf("Enter the page number :");
				scanf("%d",&shead->occured[i]);
			}
		}
	}

	shead->left=NULL;
	shead->right=NULL;
	return shead;
}

majorTerm *mcreate(char *str)  //creating the major term
{
	int n,i;
	majorTerm *mhead;
	if((mhead=malloc(sizeof(majorTerm)))==NULL)
	{
		printf("cannot allocate memory to the major term");
		exit(0);
	}
	mhead->next=screate("M");
	mhead->occured=NULL;
    strcpy(mhead->name,str);

	if(*mhead->name!='M' && strlen(mhead->name)>1)
	{
		printf("please Enter the pg_no. :");
		scanf("%d",&mhead->pg_no);
		if(mhead->pg_no<0)
		{
			printf("pg number should be positive");
			printf("please Enter the pg_no.");
			scanf("%d",&mhead->pg_no);
		}

		printf("please Enter the page number where and all this term has occured :");
		scanf("%d",&n);
		mhead->size=n;
		if(n>0)
		{	
			if((mhead->occured=malloc(sizeof(int)*n))==NULL)
			{
				printf("couldnt allocate memory");
				exit(2);
			}
			for(i=0;i<n;++i)
			{
				printf("Enter the page number :");
				scanf("%d",&mhead->occured[i]);
			}
		}
	}
	mhead->left=NULL;
	mhead->right=NULL;
	return mhead;
}

int scheck(subTerm *head,char *ch) //its checking if the subterm head is greater or less than the new term
{
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

int mcheck(majorTerm *head,char *ch) //its checking if the term is greater than the head term and returning
{
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

void addMTerm(majorTerm *mhead,majorTerm *new) //adding the major term in tree
{
	int n=mcheck(mhead,new->name);
	switch(n)
	{

	    case 1:if(mhead->right==NULL)
				{
					mhead->right= new;
				}
				else
				{
					addMTerm(mhead->right,new);
				}
				break;
		case -1:if(mhead->left==NULL)
				{
					mhead->left = new;
				}
				else
				{
					addMTerm(mhead->left,new);
				}
				break;
		default:printf("Term already exist cannot add in index\n");
	}
}

void addSTerm(subTerm *shead,subTerm *new)   //adding a sub term in the tree
{
	int n=scheck(shead,new->name);
	switch(n)
	{

	    case 1:if(shead->right==NULL)
				{
					shead->right= new;
				}
				else
				{
					addSTerm(shead->right,new);
				}
				break;
		case -1:if(shead->left==NULL)
				{
					shead->left = new;
				}
				else
				{
					addSTerm(shead->left,new);
				}
				break;
		default:printf("Term already exist cannot add in index\n");
	}
}

majorTerm *create()    //Creating the Binary tree for index
{
	char ch,ch1,name[50];
	majorTerm *mhead=mcreate("M"),*new;
	subTerm *snew;
	while(1)
	{
		printf("Do u want to create Major Term for your index\nY-for yes\nN-for no\nif u entered any other character program will automatically Terminate");
		scanf(" %c",&ch);
		switch(ch)
		{
			case 'Y':printf("\n....................................................\n");
					 printf("please Enter the name of major Term :");
					 scanf("%s",name);
					 new=mcreate(name);
					 addMTerm(mhead,new);
					while(1)
					{
					 	printf("Do u want to create subterm for this major term\nY-for yes\nN-for no\nif u enetred any other character program will automatically Terminate");
					 	scanf(" %c",&ch1);
					 	switch(ch1)
					 	{
					 		case 'Y':printf("\n....................................................\n");
					 				 printf("please Enter the name of subterm :");
					 				 scanf("%s",name);
					 				 snew=screate(name);
					 				 addSTerm(new->next,snew);
					 				 printf("\n....................................................\n");
					 				 break;
							case 'N':break;
							default:printf("please enter the correct option next Time\n");
						}
						if(ch1=='N')break;
					}
					printf("\n....................................................\n");
					break;
			case 'N':break;
			default:printf("please enter the correct option next time\n");
		}
		if(ch=='N')break;
	}
	return mhead;
}

void sdisplay(subTerm *shead)
{
	if(shead!=NULL)
	{
		sdisplay(shead->left);
		if(*shead->name!='M' && strlen(shead->name)>1)
		{
			printf("\t%s\t%d\n",shead->name,shead->pg_no);
			if(shead->occured!=NULL)
			{
				printf("Do u want to print the pages where this term has occured");
				if(getchar()=='Y')
				{
					int i=shead->size;
					while(i--)
					{
						printf("\n....................page numbers....................\n");
						printf("\t%d\n",*(shead->occured+i));
					}
				}
			}
		}
		sdisplay(shead->right);
	}
}

void mdisplayIndex(majorTerm *mhead) //displaying the major terms
{
	if(mhead!=NULL)
	{
		mdisplayIndex(mhead->left);
		if(*mhead->name!='M' && strlen(mhead->name)>1)
		{
			printf("%s\t%d\n",mhead->name,mhead->pg_no);
			if(mhead->occured!=NULL)
			{
				printf("Do u want to print the pages where this term has occured");
				if(getchar()=='Y')
				{
					int i=mhead->size;
					while(i--)
					{
						printf("\n....................page numbers....................\n");
						printf("\t%d\n",*(mhead->occured+i));
					}
				}
			}
			if((mhead->next)->left!=NULL || (mhead->next)->right!=NULL)
			{
				printf("\nDo u want to print sub term\n");
				if (getchar()=='Y')
				{
					printf("\n.............................Sub-Terms.............................\n");
					sdisplay(mhead->next);
				}
			}
		}
		mdisplayIndex(mhead->right);
	}
}

void traverse(majorTerm *mhead,char *ch)
{
	int n=mcheck(mhead,ch);
	if(mhead!=NULL)
	{
		if(n==1)traverse(mhead->right,ch);
		else if(n==-1)traverse(mhead->left,ch);
		else if(n==0)
		{
			printf("\n..........................%s\t%d..........................\n",mhead->name,mhead->pg_no);
			while(1)
			{
				printf("\n1.OverWrite the occured Term\n2.add an occured term\n3.add a Sub-Term\n4.print occured terms\n5.print sub-Term\n6.Exit");
				int ch,k;
				scanf("%d",&ch);
				switch(ch)
				{
					case 1:printf("please Enter the page number where and all this term has occured :");
							scanf("%d",&k);
							if(n>0)
							{	
								if((mhead->occured=malloc(sizeof(int)*n))==NULL)
								{
									printf("couldnt allocate memory");
									exit(2);
								}
								for(int i=0;i<n;++i)
								{
									printf("Enter the page number :");
									scanf("%d",&mhead->occured[i]);
								}
							}
							break;
					case 2:printf("how many more terms are to be added");
							scanf("%d",&k);
							mhead->occured=realloc(mhead->occured,sizeof(int)*(mhead->size));
							for(int i=1;i<=k;++i)
							{
								printf("Enter the Term");
								scanf("%d",&mhead->occured[mhead->size+i]);
							}
							mhead->size=mhead->size+k;
							break;
					case 3:printf("Enter the name of subterm");
							char name[50];
							scanf("%s",name);
							subTerm *new = screate(name);
							addSTerm(mhead->next,new);
							break;
					case 4:if(mhead->occured==NULL)
							{
								printf("please Enter Something First");
							}
							else
							{
								int i=mhead->size;
								while(i--)
								{
									printf("\n....................page numbers....................\n");
									printf("\t%d\n",*(mhead->occured+i));
								}
							}
							break;
					case 5:sdisplay(mhead->next);
							break;
					case 6:break;
					default:printf("please Enetr the right choice next time\n");

				}
				if(ch==6)break;
			}
		}
	}
}
