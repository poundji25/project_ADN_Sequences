#include "distance.h"
#include "sequence.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

float minimum(float a,float b,float c) //fonction qui calcule le minimum de 3 entiers
{
    float mini; 
    if(a<b && a<c)
    {mini=a;}
	else
	{
	if(b<a && b<c)
    {mini=b;}
    else
    {mini=c;}
	}
	return mini;
}

void affiche_distances(DISTANCE ds,int nbr)  // fonction qui affiche tous les distancesde pairs de séquences possibles
{
printf("\nLES DISTANCES : \n\n");

for(int i=0;i<nbr;i++)
{
	printf("<%d> : ",i);
	if(ds.distances[i][0].valide==1)
	{
	for(int j=0;j<nbr;j++)
	{	
	 if(ds.distances[i][j].valide==1 && j!=0)
	 printf(" %.1f ",ds.distances[i][j].dist);
	 }
	}
	printf("\n\n");
}

}

float calcul_distance_1(SEQUENCE s1,SEQUENCE s2)
{
   int min,max;
   double a,somme=0;
	
		if(s1.taille==0&&s2.taille==0)
			{return 0;}
		if(s1.taille==0&&s2.taille>0)
		{
			min =0;
			max= s2.taille;
		}
		
		if(s2.taille==0&&s1.taille>0)
		{
			min =0;
			max= s1.taille;
		}

		if(s1.taille>=s2.taille)
		{
			min=s2.taille;
			max=s1.taille;
		}
			else 
			{
				max=s2.taille;
				min=s1.taille;
			}

    for(int i=0;i<min;i++)
    {
        a=calcul_D(s1.une_sequence[i],s2.une_sequence[i]);
       if(a == -1)
    {
        printf("ERREUR distance 1\n");
        return -1;
    }
       somme=somme+a;
    }

    for(int i=min;i<max;i++)
    {
        somme=somme + 1.5;
    }

	return somme;
}

double calcul_D(char a,char b) //fonction qui calcule la distance d'edition entre deux caractéres
{

    if(a=='-' || b=='-')
     {
        return 1.5;}

    if(a==b)
        {return 0;}

    if(a=='A')
    {
        switch(b)
        {
            case 'C' : return 2;
            case 'G' : return 1;
            case 'T' : return 2;
        }
    }
     else if(a=='C')
     {
      switch(b)
      {
          case 'A': return 2;
          case 'T': return 1;
          case 'G': return 2;
      }
     }
     else if(a=='G')
     {
        switch(b)
        {
            case 'A': return 1;
            case 'C': return 2;
            case 'T': return 2;
        }
     }
     else if(a=='T')
     {
         switch(b)
         {
             case 'A': return 2;
             case 'G': return 2;
             case 'C': return 1;
         }
     }
     return -1;
}

void stocker_distance(DISTANCE *ds,char * rep,int nbr,char ** noms)
{

SEQUENCE s1,s2;
for(int i=0;i<nbr;i++)
{

	s1=lecture_sequence(i,rep,nbr,noms);
	
	for(int j=0;j<nbr;j++)
	{
		s2=lecture_sequence(j,rep,nbr,noms);
		if(i<j)
		{
			 ds->distances[i][j].dist=D2(s1,s2,s1.taille,s2.taille);
             ds->distances[i][j].valide=1;
        }
        else
        {
			if(j==0)
			{ds->distances[i][j].valide=1;ds->distances[i][j].dist=0;}
			else
			{
				ds->distances[i][j].valide=0;
				ds->distances[i][j].dist=0;
			}
		}
    }

}	
}

double D2(SEQUENCE s1,SEQUENCE s2,int i,int j) {

    double T[s1.taille+1][s2.taille+1];
    T[0][0] = 0;

    char* c1 = s1.une_sequence; char* c2 = s2.une_sequence;

    for (int k = 1; k < s1.taille; k++) 
    {
        T[k][0] = T[k-1][0] + 1.5; //intialisation de la colonne 0 dans tous les lignes de la matrice
    }
    for (int l = 1; l < s2.taille + 1; l++) 
    {
        T[0][l] = T[0][l-1] + 1.5; // intialisation de la ligne 0 dans tous les colonnes
    }


    for (int a = 1;a< s1.taille+1; a++) 
    {
        for (int b= 1;b< s2.taille+1; b++)
         {

            float diagonale = T[a-1][b-1] + calcul_D(c1[a-1], c2[b-1]);
            float haut = T[a-1][b] + 1.5;
            float gauche = T[a][b-1] + 1.5;

            T[a][b]=minimum(diagonale,haut,gauche); // on trouve le minimum entre les trois cas possible et on le sauvgarde
        }
    }

    return T[s1.taille][s2.taille];
}	
