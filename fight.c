
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include "common.h"
#include "spell.h"
#include "fighter.h"
#include "fight.h"

void fightHandleSpell(Fighter *fighter,Spell *pSpellElement,Fighter *pTeam1, Fighter *pTeam2)
{
//on verifie le sort

	int choix2 = 0;
	char mybuffer[128];
	memset(mybuffer,0,128);
	//sleep(10);

	if ( pSpellElement->cible == 0){  //verif type de sort (là ça vise soit)
		fighter->pv +=  pSpellElement->dmg;
		if(fighter->pv > fighter->pvmax){
			fighter->pv = fighter->pvmax;
		}
	} 
    else if( pSpellElement->cible == 1){ //verif type de sort (là ça vise mate)
        printf("+-------------------------------------------+\n");
        printf("| Vos alliés sont :\n");
        printf("| 1 : [%s] [%d]/[%d]\n",pTeam1[0].nom, pTeam1[0].pv,pTeam1[0].pvmax);
        printf("| 2 : [%s] [%d]/[%d]\n",pTeam1[1].nom, pTeam1[1].pv,pTeam1[1].pvmax);
        printf("| 3 : [%s] [%d]/[%d]\n",pTeam1[2].nom, pTeam1[2].pv,pTeam1[2].pvmax);
        printf("+-------------------------------------------+\n");
        while((choix2!=1) && (choix2!=2) && (choix2!=3)){
            printf("| Veuillez saisir le numéro de votre cible\n");
            scanf("%s", mybuffer);
            choix2= atoi(mybuffer);
        }
        if(choix2==1){
            printf("+-------------------------------------------+\n");
            printf("| %s %s\n", pSpellElement->description, pTeam1[0].nom);
            printf("| %s récupère %d PV\n",pTeam1[0].nom,  pSpellElement->dmg);
            printf("+-------------------------------------------+\n");
        }
        else if(choix2==2){
            printf("+-------------------------------------------+\n");
            printf("| %s %s\n", pSpellElement->description, pTeam1[1].nom);
            printf("| %s récupère %d PV\n",pTeam1[0].nom,  pSpellElement->dmg);
            printf("+-------------------------------------------+\n");
        }
        else if(choix2==3){
            printf("+-------------------------------------------+\n");
            printf("| %s %s\n", pSpellElement->description, pTeam1[2].nom);
            printf("| %s récupère %d PV\n",pTeam1[0].nom,  pSpellElement->dmg);
            printf("+-------------------------------------------+\n");
        }
	      
          
          
    } else { 
            printf("+-------------------------------------------+\n");
            printf("| Vos ennemis sont :\n");
            printf("| 1 : [%s] [%d]/[%d]\n",pTeam2[0].nom, pTeam2[0].pv,pTeam2[0].pvmax);
            printf("| 2 : [%s] [%d]/[%d]\n",pTeam2[1].nom, pTeam2[1].pv,pTeam2[1].pvmax);
            printf("| 3 : [%s] [%d]/[%d]\n",pTeam2[2].nom, pTeam2[2].pv,pTeam2[2].pvmax);
            printf("+-------------------------------------------+\n");
            while(choix2!=1 && choix2!=2 && choix2!=3){
                printf("| Veuillez saisir le numéro de votre cible\n");
                scanf("%s", mybuffer);
                choix2= atoi(mybuffer);
            }
            switch (choix2)
            {
            case 1:
                printf("+-------------------------------------------+\n");
                printf("| %s %s\n", pSpellElement->description, pTeam2[0].nom);
                printf("| %s subit %d dégâts\n",pTeam2[0].nom,  (pSpellElement->dmg+fighter->atk));
                pTeam2[0].pv -= (pSpellElement->dmg+fighter->atk);
                printf("+-------------------------------------------+\n");
                break;
            case 2:
                printf("+-------------------------------------------+\n");
                printf("| %s %s\n", pSpellElement->description, pTeam2[1].nom);
                printf("| %s subit %d dégâts\n",pTeam2[1].nom,  (pSpellElement->dmg+fighter->atk));
                pTeam2[1].pv -= (pSpellElement->dmg+fighter->atk);
                printf("+-------------------------------------------+\n");
                break;
            case 3:
                printf("+-------------------------------------------+\n");
                printf("| %s %s\n", pSpellElement->description, pTeam2[2].nom);
                printf("| %s subit %d dégâts\n",pTeam2[2].nom, (pSpellElement->dmg+fighter->atk));
                pTeam2[2].pv -= (pSpellElement->dmg+fighter->atk);
                printf("+-------------------------------------------+\n");
                break;

            default:
                break;
            }
	}
    
}
