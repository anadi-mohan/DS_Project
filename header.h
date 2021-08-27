#include<stdio.h>
#include<stdlib.h>

typedef struct sterm
{
	int pg_no;
	int size;
	char name[50];
	int *occured;
	struct sterm *left;
	struct sterm *right;
}subTerm;

typedef struct term
{
	int pg_no;
	int size;
	char name[50];
	int *occured;
	subTerm *next;
	struct term *left;
	struct term *right;
}majorTerm;

majorTerm *create(void);
majorTerm *mcreate(char *);
subTerm *screate(char *);
void addMTerm(majorTerm *,majorTerm *);
void addSTerm(subTerm *,subTerm *);
int scheck(subTerm *,char *);
int mcheck(majorTerm *,char *);
void mdisplayIndex(majorTerm *);