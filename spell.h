#ifndef __SPELL_HEADER__ 
#define __SPELL_HEADER__
typedef struct {
	char nom[21];
	char description[101];
	int dmg;   //atk + dmg = output
	int mode;  //statut que ça peut mettre
	int cible; //0 = soi | 1 = allié | 2 = ennemi
	int cd;//cd = cooldown = temps de rechargement
} Spell;

Spell constructSpell(FILE * fichier);

#endif