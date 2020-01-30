#pragma once

#include "sequence.h"

struct dis
{
double  dist;  // le champ où va etre stockées la distance entre deux séquences 
int valide;  //  le champ va prendre la valeur de 0 ou 1 (utile pour former les familles dans la partie 2)
};

struct distance
{
 struct dis ** distances; // une matrice où chaque case est unse structure de deux champs
};


typedef struct distance DISTANCE;

float calcul_distance_1(SEQUENCE s1,SEQUENCE s2);

double D2(SEQUENCE ,SEQUENCE ,int,int);

double calcul_D(char a,char b);

float minimum(float a,float b,float c);

void stocker_distance(DISTANCE *ds,char * rep,int nbr,char**);

void affiche_distances(DISTANCE ,int );
