#include <stdio.h>
#include "sequence.h"
#include "distance.h"
#include <string.h>
#include <stdlib.h>
#include "famille.h"

float Dmin(DISTANCE T,int nbr)
{
	int k=0,h=0;double mini=-1;
	
	while(k<nbr) 
	{
		if(T.distances[k][0].valide==1)
		{
		while(h<nbr)
		{
			if(T.distances[k][h].valide==1 && k<h)
			{
			 mini=T.distances[k][h].dist;h=nbr;k=nbr;
			}
			h++;
		 }
	    }
		k++;
	}
if(mini==-1)
{return -2.0;} // on retourne -2.0 si tous les séquences sont dans une famille 

	for(int i=0;i<nbr;i++)
	{
		if(T.distances[i][0].valide==1)
		{
		for(int j=0;j<nbr;j++)
		{ 
			
		   if((T.distances[i][j].dist) < mini && i<j && T.distances[i][j].valide==1)
		   {
				mini=T.distances[i][j].dist;
			}
		}
	    }
	}
	return mini;
}

FAMILLES creer_familles(FAMILLES Fa,DISTANCE d,int nbr_fic)
{

	double mini; // la distance minimum 
	int compteur,max=-1,indice_sequence;
	int i,j;
	 
while(max!=0) // la boucle s'arrete quand tous les séquences appartiennent à une famille
{
		Fa.familless[Fa.indice_i].indice_j=0;
		mini=Dmin(d,nbr_fic);
		if(mini==-2.0)
		{break;}
		
		
		max=0;
		
		indice_sequence=0;
		for(i=0;i<nbr_fic-1;i++) // boucle qui va changer l'indice des lignes(des séquences) de la matrice et vas trouver la sequence qui va former la famille
	   {
		 
		  if(d.distances[i][0].valide==1)
		 {
			 compteur=1; // car on peut trouver une famille qui contient une seule séquence
		 for(j=0;j<nbr_fic;j++)
			{
					                                
						if(d.distances[i][j].dist==mini && d.distances[i][j].valide && i<j) // cette condition veut dire "la distance = la Dmin calculée"
						{
							compteur++;
						}

			}
				
		 }
			 if(compteur>max) // deuxième terme de la condition est utile dans le cas où il on a trouvé toutes les familles possible <=> compteur==0
			 {
				max=compteur;  // a chaque fois on trouve la séquence qui a le plus de Dmin
				indice_sequence=i; // on sauvgarde l'indice de la ligne de la séquence
			 }	
		  
		}
		
		
		 
		if(max!=0)
	   {
		 Fa.familless[Fa.indice_i].membres[Fa.familless[Fa.indice_i].indice_j]=indice_sequence+1;  Fa.familless[Fa.indice_i].indice_j++;        // ici on stocke le numéro de la ligne (la séquence) qui forme la famille (k est l'indice de la colonne, il va etre incrémenter pendant que l'on trouve les autres membres de la famille)
		
		for(int j=0;j<nbr_fic;j++)
		{	
			if(indice_sequence<j && d.distances[indice_sequence][j].dist==mini && d.distances[indice_sequence][j].valide==1) //&& verifi(Fa,j)
			{
				Fa.familless[Fa.indice_i].membres[Fa.familless[Fa.indice_i].indice_j]=j+1;  Fa.familless[Fa.indice_i].indice_j++;
				
				 d.distances[j][0].valide=0;
				
				for(int k=0;k<nbr_fic-1;k++)
				{
					d.distances[k][j].valide=0;
					d.distances[k][indice_sequence].valide=0;
				}
				
			}
			
			d.distances[indice_sequence][j].valide=0;   // on mets tous a 0 (meme ceux qui ne font pas partie de la famille formé car sinon la fonction minimum va les considérer --> éventuelle erreur
		    
	    }
		Fa.indice_i++; // on incrémente pour passer a une nouvelle ligne (nouvelle famille)
       }	   
       

}
	
	return Fa;
}

void affiche_familles(FAMILLES Fa,int nbr)
{
printf("\nLES FAMILLES : \n\n");

for(int i=0;i<nbr;i++)
	{
		if(Fa.familless[i].membres[0])
		 {printf("F%d :",i+1);}
		for(int j=0;j<nbr;j++)
		{
			if(Fa.familless[i].membres[j])
			printf("  séquence %2d ",Fa.familless[i].membres[j]);
		}
		if(Fa.familless[i].membres[0])
		printf("\n\n");
	}	
	
}


void creer_rep(FAMILLES F,char* rep,char** noms)
{
		char* tmp=calloc(sizeof(char),30);
		char* tmp2=calloc(sizeof(char),30);
		
		for(int i=0;i<F.indice_i;i++)
		{
			sprintf(tmp,"mkdir F%d",i+1);
		
			system (tmp);
		}	
		
	for(int i=0;i<F.indice_i;i++)
	{	
		sprintf(tmp2,"F%d",i+1);
		printf("le repertoire de la famille %d (%s) a été créer et remplit\n",i+1,tmp2);
		for(int j=0;j<F.familless[i].indice_j;j++)
		{
			sprintf(tmp,"cp %s/%s %s",rep,noms[F.familless[i].membres[j]-1],tmp2);
			
			system(tmp);
			
		}
	}
	printf("\nPOUR SUPPRIMER LES REPERTOIRES APPELLER LA FONCTION supprimer-rep IMPLEMENTER DANS famille.c\n\n");	
}

void supprimer_rep(FAMILLES F)
{
char* tmp=calloc(sizeof(char),10);
		
	for(int i=0;i<F.indice_i;i++)
	{
			sprintf(tmp,"rm -Rf F%d",i+1);
			system (tmp);
			printf("le repertoire de la famille %d a été supprimer\n",i+1);
			
	}	
	
}
