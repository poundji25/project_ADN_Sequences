#include "distance.h"
#include "sequence.h"
#include <string.h>
#include <stdlib.h>


int main(int argc, char **argv)
{
	int nbre_2_fic=0;// variable où va etre stocké le nombre de fichiers
	char ** noms; // tableau de chaines de caractéres qui va représenter le repertoire des séquences

	nbre_2_fic=compte_nbre_fic(argv[1]); // le nombre de fichiers
	
	noms=noms_seq(argv[1],nbre_2_fic); // les noms des séquences 
	
	printf("\nLE REPERTOIRE %s CONTIENT %d FICHIERS :\n\n",argv[1],nbre_2_fic);
    
    for(int i=0;i<nbre_2_fic;i++)
    {
		printf("séquence %2d  : %s\n",i+1,noms[i]);
	}
	printf("\n\n");
	
	
	
	printf("EXEMPLES DE LECTURE ET D'AFFICHAGE DE SÉQUENCES : \n\n"); 
	
    SEQUENCE s1=lecture_sequence(1,argv[1],nbre_2_fic,noms);
    printf("LA SÉQUENCE 1  :   ");
    affiche_sequence(s1); 
    
    SEQUENCE s2=lecture_sequence(4,argv[1],nbre_2_fic,noms);
    printf("LA SÉQUENCE 4  :   ");
    affiche_sequence(s2);
	
	printf("\n\n");
	
	
	printf("EXEMPLES de calcul de distance\n\n");
	

       if(calcul_distance_1(s1,s2)<0)
            printf("ERREUR\n");
        else
        {
            printf("la distance est %.1f (D1)\n",calcul_distance_1(s1,s2));
        }

     
			printf("la distance est %.1f  (D2)\n\n",D2(s1,s2,s1.taille,s2.taille));



	//Intialiser la structure de données DISTANCE 
    
	DISTANCE ds;
	ds.distances=calloc(sizeof(struct dis*),(nbre_2_fic));
	
	for(int i=0;i<nbre_2_fic;i++)
	{
			ds.distances[i]=(struct dis*)calloc(sizeof(struct dis),nbre_2_fic);	
	}
	
	  stocker_distance(&ds,argv[1],nbre_2_fic,noms); //stocker les distances des pairs de séquences possibles
      
      affiche_distances(ds,nbre_2_fic);  // afficher les distances stockées dans DISTANCE 

	  return 0;
}
