#include "sequence.h"
#include "distance.h"

struct famille
{
	int* membres;
	int indice_j; // indice des colonnes (les membres de la famille indice_i)
};
typedef struct famille FAMILLE;

 struct familles {
	
	FAMILLE* familless;  
	int indice_i; // indice des lignes (les familles)
};
typedef struct familles FAMILLES;
	

float Dmin(DISTANCE,int);

FAMILLES creer_familles(FAMILLES,DISTANCE,int);

void affiche_familles(FAMILLES Fa,int nbr);

void creer_rep(FAMILLES,char*,char**);

void supprimer_rep(FAMILLES);
