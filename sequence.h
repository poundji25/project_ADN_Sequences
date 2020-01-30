#pragma once

#include <stdio.h>


typedef struct sequence
{
	char* une_sequence;
    int taille;
    
} SEQUENCE;


typedef struct sequence2
{
	double dist;
	char car;
	
} SEQUENCE2;


SEQUENCE lecture_sequence(int,char*,int,char**);

void affiche_sequence(SEQUENCE );

int compte_nbre_fic(char *);

char ** noms_seq(char *,int);
