#ifndef __FIGHT_HEADER__ 
#define __FIGHT_HEADER__

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include "common.h"
#include "spell.h"
#include "fighter.h"

void fightHandleSpell(Fighter *fighter,Spell *pSpellElement,Fighter *pTeam1, Fighter *pTeam2);

#endif