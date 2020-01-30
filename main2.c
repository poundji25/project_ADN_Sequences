#include "distance.h"
#include <stdio.h>
#include <stdlib.h>
#include "famille.h"


int main(int argc, char **argv)
{
	int nbre_2_fic=0; // variable où va etre stocker le nombre de fichiers
	char** noms;  // tableau de chaines de caractéres qui va représenter le repertoire des séquences

	nbre_2_fic=compte_nbre_fic(argv[1]); // le nombre de fichiers
	
	noms=noms_seq(argv[1],nbre_2_fic); // les noms de séquences
	
	printf("\nLE REPERTOIRE %s CONTIENT %d FICHIERS :\n\n",argv[1],nbre_2_fic);
    
    for(int i=0;i<nbre_2_fic;i++)
    {
		printf("séquence %2d  : %s\n",i+1,noms[i]);
	}
	printf("\n\n");
	
	//Intialiser la structure de données DISTANCE (distance & l'entier valide)
	 
	DISTANCE ds;
	ds.distances=calloc(sizeof(struct dis*),(nbre_2_fic)); 
	
	for(int i=0;i<nbre_2_fic;i++)
	{
			ds.distances[i]=(struct dis*)calloc(sizeof(struct dis),nbre_2_fic);	
	}
	
	stocker_distance(&ds,argv[1],nbre_2_fic,noms); //stocker les distances des pairs de séquences possibles
	
    affiche_distances(ds,nbre_2_fic); // afficher les distances stockées dans DISTANCE 
	
	
	
	
	// Initialiser la structure de données FAMILLES 
	
	FAMILLES F;
	F.familless=malloc(sizeof(FAMILLE)*nbre_2_fic);
	F.indice_i=0;
	
	
	
	for(int i=0;i<nbre_2_fic;i++) // intailiser la matrices de FAMILLES
	{
		F.familless[i].membres=calloc(sizeof(int),nbre_2_fic);
		F.familless[i].indice_j=0;
		for(int j=0;j<nbre_2_fic;j++)
		{
		 F.familless[i].membres[j]=0;
		}
	}
		
		
	F=creer_familles(F,ds,nbre_2_fic);  // créer les familles et on les stocke dans FAMILLES
	
	affiche_familles(F,nbre_2_fic);    // affiche les familles stockées
	
	creer_rep(F,argv[1],noms);
	
	//supprimer_rep(F);  // la fonction supprimer_rep supprime les repertoire où les familles sont stocker
		
	return 0;
}

