#include "distance.h"
#include "sequence.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <dirent.h>

int compte_nbre_fic(char * rep)// fonction qui trouve le nombre de fichiers dans le repertoire 
{
DIR * d=opendir(rep);
int nbre_2_fic=0;
struct dirent * a=readdir(d);

while(a!=NULL)
{
	nbre_2_fic++; // trouver le nombre de fichier dans le repertoire où sont stocker les séquences 
	a=readdir(d);
}
return nbre_2_fic-2;  // on soustrait 2 car readdir prends on considération le "." et le ". ." 

}

char ** noms_seq(char * rep,int nbr) //fonction qui fait un répertoire de séquences 
{
	DIR * d=opendir(rep);
	struct dirent * a=readdir(d);
	char** noms=calloc(sizeof(char*),nbr);
	int j=0;
	
	while(a!=NULL)
{
	if((strcmp(a->d_name,".")!=0)&&(strcmp(a->d_name,"..")!=0))
{
		noms[j]=calloc(sizeof(char),strlen(a->d_name));
	
	for(int i=0;i<strlen(a->d_name);i++)
	{noms[j][i]=a->d_name[i];}
	 
	 j++;
}
	
	a=readdir(d);
}
return noms;
	
}

SEQUENCE lecture_sequence(int num,char * rep,int nbr,char ** noms)
{
		if(num<=0 && num>nbr)
		 {
			 printf("ERREUR : lecture \n");
			 exit(1);
		 }
		
		
SEQUENCE s1; s1.taille=0;	
if(num>=nbr||num>=1)
{

FILE* f;
char * s2=malloc(sizeof(char)*25);
sprintf(s2,"%s/%s",rep,noms[num-1]);


f=fopen(s2,"r");

char* n=malloc(sizeof(char)*20);
if(n==NULL)
{exit(1); printf("erreur allocation mémoire dans lecture sequence\n");}
char c;
int i=0;
while((c=fgetc(f))!=EOF)
{
	n[i]=c;
	i++;
}

s1.une_sequence=n;
s1.taille=i;
}
return s1;
}

void affiche_sequence(SEQUENCE s)
{
for(int i=0;i<s.taille;i++)
{
 printf(" %c ",s.une_sequence[i]);
}
printf("\n");
}



