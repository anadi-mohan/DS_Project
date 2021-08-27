#include <stdlib.h>
#include <stdio.h>
#include "header.h"

int main()
{
	int ch;
	char name[50];
	majorTerm *mhead=NULL,*new=NULL;
	subTerm *shead=NULL,*snew=NULL;
	while(1)
	{
		printf("\n********************************************************************************\n");
		printf("1.create the index\n2.display the index\n3.add a major Term\n4.Traverse through the index\n5.Exit\nEnter your choice :");
		scanf("%d",&ch);
		switch(ch)
		{
			case 1:mhead=create();
				break;
			case 2:mdisplayIndex(mhead);
					break;
			case 3: if(mhead!=NULL)
					{
						printf("\n....................................................\n");
						printf("Enter the name for major Term");
						scanf("%s",name);
						new=mcreate(name);
						addMTerm(mhead,new);
						printf("\n....................................................\n");
					}	
					break;
			case 4:if(mhead!=NULL)
					{
						printf("Enter the term to traverse to");
						scanf("%s",name);
						traverse(mhead,name);
					}
					break;
			case 5:exit(0);
		}
	}
}