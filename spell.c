#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include "common.h"
#include "spell.h"
#include "fighter.h"

//---------------------------------------------------------------------------------------
Spell constructSpell(FILE * fichier){ //fonction qui prend les spells du .txt
	Spell spell;
	if(fichier == NULL){
		printf("Problème lors de l'ouverture du fichier des sorts");
	}
	if(fichier != NULL){
		char buffer[101];
		memset(buffer,0,101);
		// get 1st atribute: name: (1st line is the name)
		fgets(buffer, 100, fichier);
		buffer[strlen(buffer)-1]='\0';
		memcpy(spell.nom ,buffer,101);

		fgets(buffer, 100, fichier);
		buffer[strlen(buffer)-1]='\0';
		memcpy(spell.description ,buffer,101);

		// get the others atributes
		fgets(buffer,20,fichier);
       		spell.dmg=atoi(buffer);
		
		fgets(buffer,20,fichier);
        	spell.mode=atoi(buffer);

		fgets(buffer,20,fichier);
        	spell.cible=atoi(buffer);

		fgets(buffer,20,fichier);
		spell.cd=atoi(buffer);


		printf("[%s] \nDescription : %s \nDMG : %d \nMODE : %d \nCIBLE : %d \n\n", spell.nom, spell.description, spell.dmg, spell.mode, spell.cible);
		return spell;
	}
}

