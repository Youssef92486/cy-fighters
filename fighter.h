#ifndef __FIGHTER_HEADER__ 
#define __FIGHTER_HEADER__

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include "common.h"
#include "spell.h"

typedef struct {
	char nom[21];
	int pvmax;
	int pv;
	int atk;
	int def;
	int agi;
	int vit;
	int mode;
	int selected;
	int player;
	Spell spell1;
	Spell spell2;
	Spell spell3;
	Spell spell4;
} Fighter;

#endif