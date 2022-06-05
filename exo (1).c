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

int NombreDePerso=0;







Fighter constructFighter(FILE * fichier){ //function that takes the characters in the file and put them into a struct
	Fighter fighter;
	if(fichier == NULL){
		printf("Problème lors de l'ouverture du fichier");
	}
	if(fichier != NULL){
		char buffer[21];
		memset(buffer,0,21);
		// get 1st atribute: name: (1st line is the name)
		fgets(buffer, 20, fichier);
		//printf("find name: %s \n", buffer);
		buffer[strlen(buffer)-1]='\0';  // pour supprimer le retour à la ligne du nom
		memcpy(fighter.nom ,buffer,21);

		// get the others atributes
		fgets(buffer,20,fichier );
       		fighter.pvmax=atoi(buffer);
		
		fighter.pv=fighter.pvmax;
		
		fgets(buffer,20,fichier );
        	fighter.atk=atoi(buffer);

		fgets(buffer,20,fichier );
        	fighter.def=atoi(buffer);

		fgets(buffer,20,fichier );
        	fighter.agi=atoi(buffer);

		fgets(buffer,20,fichier );
        	fighter.vit=atoi(buffer);
		
		fighter.selected = 0;

		printf("[%s] \nPV  : %d \nATK : %d \nDEF : %d \nAGI : %d \nVIT : %d \n\n", fighter.nom, fighter.pvmax, fighter.atk, fighter.def, fighter.agi, fighter.vit);	
		return fighter;
	}
}

//---------------------------------------------------------------------------------------
int nombreLignes(FILE *fichier ){ //function that count the lines of a file (it allows later to understand how many characters are stored in the files)
	
	int ch = 0;
	int lines = 0;

	if(fichier == NULL){
		printf("Problème lors de l'ouverture du fichier");
		return 0;
	}
	while(!feof(fichier)){
  		ch = fgetc(fichier);
  		if(ch == '\n'){
   	 		lines++;
  		}
	}
	printf("Il y a %d lignes là\n", lines);
	return lines;
}
//---------------------------------------------------------------------------------------
// Function that make both players choose their names
void chooseName(int num, char* pBuffer, int tailleMax){
	memset(pBuffer,0,tailleMax);
	clear();
	printf("\nJoueur %d, veuillez choisir votre nom :", num);
	scanf("%s", pBuffer);
}

//---------------------------------------------------------------------------------------
// Function that just manage to print the team of both players
void printTeam(int *firstTab, int *secondTab, Fighter *pTabElement, char *playerOne, char *playerTwo){
        int index1;
        int index2;
	clear();
	printf("----------------------------------------\n");
	printf("Bienvenue dans la séléction des champions\n");
	printf("----------------------------------------\n\n\n");
	printf("+-------------------------------------------+\n");
        if((playerOne!=NULL) && (playerTwo!=NULL) ){
		char nom1[32];
		char nom2[32];
		memset(nom1,0,32);
		memset(nom2,0,32);
		memset(nom1,' ',9);
		memset(nom2,' ',9);
		int size = strlen(playerOne);
		if(size>32){
			size = 32;
		}
		memcpy(nom1,playerOne,size);

		size = strlen(playerTwo);
		if(size>32){
			size = 32;
		}
		memcpy(nom2,playerTwo,size);
		printf("| Joueur 1 : %s| Joueur 2 : %s|\n",nom1,nom2);
        }
	else{
		printf("Attention: Joueur 1 ou 2: pointer null ==> quiter la fonction %s ligne %d sans traitement\n",__FUNCTION__,__LINE__); //technique pour voir où est ce que ça crash
		return;
        }
	printf("| Équipe 1            | Équipe 2            |\n");

        for(int k=0;k<TAILLETEAM; k++){
		index1=firstTab[k];
		index2=secondTab[k];
		char nom1[32];
		char nom2[32];
		memset(nom1,0,32);
		memset(nom2,0,32);
		memset(nom1,' ',15);
		memset(nom2,32,15);
		//printf("name1 : %s\n",nom1);
		if( (index1<NombreDePerso) && (index2<NombreDePerso)){
                	int sz;
                	if( index1 != -1){
				sz=strlen(pTabElement[index1].nom);
				if(sz>32){
					sz=32; // permet de tronquer le nom si besoin 
				}
				memcpy(nom1,pTabElement[index1].nom,sz);
                    	}
			if(index2 != -1){
				sz=strlen(pTabElement[index2].nom);
				if(sz>32){
					sz=32;
				}
				memcpy(nom2,pTabElement[index2].nom,sz);
			}
			printf("| %d : %s | %d : %s |\n", k+1,nom1,k+1, nom2);
		} 
		else {
			printf("Erreur un des index ou les indexs ne sont pas bon [index1: %d index2: %d] max %d\n", index1,index2,NombreDePerso-1 );         
		}
	}
	printf("+-------------------------------------------+\n");
}

//---------------------------------------------------------------------------------------
int choisiPerso(Fighter *pTabElement, int nmbPerso, int player){ //function make player pick a character among the list
	int choix;  //choix va contenir le numéro du perso voulu
	char mybuffer[128]; 
	int a = 0;  //booléen
	memset(mybuffer,0,128);
	while(a == 0){	
		printf("Joueur %d, veuillez écrire le numéro du personnage que vous voulez : \n", player);
		printf("Parmi :\n");
		for(int j=0;j<nmbPerso;j++){
				if(pTabElement[j].selected == 0){
					printf("%d - %s\n", j+1, pTabElement[j].nom);
				}
		}
		scanf("%s", mybuffer);
		choix = atoi(mybuffer);
		for(int j=1;j<nmbPerso+1;j++){ //vérifie que le chiffre est dans la liste
				if((j==choix) && (pTabElement[choix-1].selected == 0)){
					a+=1;
				}
		}
	}
	printf("Vous avez choisi : [%s]", pTabElement[choix-1].nom);
	pTabElement[choix-1].selected = 1;
	pTabElement[choix-1].player = player;
	//sleep(1);
	printf("\n\n\n\n\n\n");
	clear();
	return choix-1;
}

//---------------------------------------------------------------------------------------
// fonction qui permet de faire choisir les personnages aux joueurs, elle prend en paramètre les tableaux des 2 équipes (d'entiers) à compléter, avec le nom des joueurs
int champSelectPVP(int mode, Fighter *pTabElement, int nmbPerso, char *playerOne, char *playerTwo, int *Tab1, int *Tab2, int sizeTab1){
	

	//int firstTab[4]={-1,-1,-1,-1};
	//int secondTab[4]={-1,-1,-1,-1};
	printTeam(Tab1, Tab2, pTabElement, playerOne, playerTwo);
	for(int i=0;i<sizeTab1;i++){		
		Tab1[i] = choisiPerso(pTabElement, nmbPerso,1);
		printTeam(Tab1, Tab2, pTabElement, playerOne, playerTwo);
		Tab2[i] = choisiPerso(pTabElement, nmbPerso,2);
		printTeam(Tab1, Tab2, pTabElement, playerOne, playerTwo);
	}
	return 0;
}

//---------------------------------------------------------------------------------------
//allow to create the teams by using the int choosed by the players earlier
void createTeam(Fighter *pTabElement, int *Tab1, int *Tab2, Fighter *Team1, Fighter *Team2){
	for(int i=0;i<TAILLETEAM;i++){
               //printf("Index1 %d index2 %d \n",Tab1[i],Tab2[i]);
		Team1[i] = pTabElement[Tab1[i]];
		Team2[i] = pTabElement[Tab2[i]];
               //printf("Team1[%d]: %s  \n",i,Team1[i].nom);Team2[i] = pTabElement[Tab2[i]];
               //printf("Team2[%d]: %s  \n",i,Team2[i].nom);
	}
}


//---------------------------------------------------------------------------------------
//---------------------------------------------------------------------------------------

void speed_test(Fighter *pSpeed_Order){ //organise the list of all fighters of the fight to decide who attack first depending of the speed stat
	Fighter buffer;

	for(int i=0;i<((TAILLETEAM*2)-1);i++){
		for(int j=i+1;j<(TAILLETEAM*2);j++){
			if(pSpeed_Order[i].vit < pSpeed_Order[j].vit ){
            			buffer = pSpeed_Order[i];
            			pSpeed_Order[i] = pSpeed_Order[j];
				pSpeed_Order[j] = buffer;
			}
		}
        }
		
}

void turn(Fighter fighter,Fighter *pTeam1, Fighter *pTeam2, char *playerOne, char *playerTwo){
	//function that make a character use one action
	int choix = 0;
	char mybuffer[128];
	int ChoiceIsRequested=1;
	memset(mybuffer,0,128);
	if(fighter.player==1){
		while (ChoiceIsRequested == 1){
			//clear();
			printf("+-------------------------------------------+\n");
			printf("| En face : %s\n",playerTwo);
			printf("| 1 : [%s] [%d]/[%d]\n",pTeam2[0].nom, pTeam2[0].pv,pTeam2[0].pvmax);
			printf("| 2 : [%s] [%d]/[%d]\n",pTeam2[1].nom, pTeam2[1].pv,pTeam2[1].pvmax);
			printf("| 3 : [%s] [%d]/[%d]\n",pTeam2[2].nom, pTeam2[2].pv,pTeam2[2].pvmax);
			printf("+-------------------------------------------+\n");
			printf("| Que souhaitez vous que %s fasse ?\n", fighter.nom);
			printf("+------------------\n");
			printf("| [%s]\n",fighter.spell1.nom);
			printf("| -%s\n",fighter.spell1.description);
			printf("| -Inflige %d dégât(s)\n",fighter.spell1.dmg);
			printf("| Cooldown : %d\n",fighter.spell1.cd);
			//for(int i=0;i<fighter.spell1.cd;i++){
			//	printf("□");
			//}

			printf("+------------------\n");
			printf("| [%s]\n",fighter.spell2.nom);
			printf("| -%s\n",fighter.spell2.description);
			printf("| -Inflige %d dégât(s)\n",fighter.spell2.dmg);
			printf("| Cooldown : %d\n",fighter.spell2.cd);
			printf("+------------------\n");
			printf("| [%s]\n",fighter.spell3.nom);
			printf("| -%s\n",fighter.spell3.description);
			printf("| -Inflige %d dégât(s)\n",fighter.spell3.dmg);
			printf("| Cooldown : %d tour(s)\n",fighter.spell3.cd);
			printf("+------------------\n");
			printf("| [%s]\n",fighter.spell4.nom);
			printf("| -%s\n",fighter.spell4.description);
			printf("| -Inflige %d dégât(s)\n",fighter.spell4.dmg);
			printf("| Cooldown : %d\n",fighter.spell4.cd);
			printf("+------------------\n");
			printf("Veuillez saisir le numero de votre ataque entre 1 et 4:\n" ">");
			scanf("%s", mybuffer);
			ChoiceIsRequested=0;

			    choix = atoi(mybuffer);
				switch (choix)
				{
				case 1:
					fightHandleSpell(&fighter, &fighter.spell1,pTeam1,pTeam2);
					break;
				case 2:
					fightHandleSpell(&fighter, &fighter.spell2,pTeam1,pTeam2);
					break;
				
				case 3:
					fightHandleSpell(&fighter, &fighter.spell3,pTeam1,pTeam2);
					break;
				
				case 4:
					fightHandleSpell(&fighter, &fighter.spell4,pTeam1,pTeam2);
					break;
				
				
				default:
				printf("Attaque non disponible. Veuillez choisir une autre ataque:\n>");
				    ChoiceIsRequested=1;
					break;
				}
				

			
			
	
		}//else{}
	}sleep(1);
	
}

//---------------------------------------------------------------------------------------
//function that organise the fight, it will first check the speed of the currents fighters, then it will make the fastest fighter decide of the action, then it'll ask the second, then the third ...
//until one of the team don't have health points anymore
void fight(Fighter *pTeam1, Fighter *pTeam2, Fighter *pSpeed_Order, char *playerOne, char *playerTwo){
	int j=0;
	int index=0;
	for(int i=0;i<TAILLETEAM;i++){ //on remplit Speed_order pour qui nous permettre les personnages les plus rapides plus tard
		//printf("[%s] hum\n", pTeam1[j].nom);
		//printf("[%s] a [%d] de vitesse\n", pTeam1[j].nom, pTeam1[j].vit);
		pSpeed_Order[index] = pTeam1[j];
		index++;
		//printf("[%s] a [%d] de vitesse\n", pTeam2[j].nom, pTeam2[j].vit);
		pSpeed_Order[index] = pTeam2[j];
		index++;
		j++;
	}
	speed_test(pSpeed_Order);
	while( ((pTeam1[0].pv > 0) && (pTeam1[1].pv > 0) && (pTeam1[2].pv > 0)) && ((pTeam2[0].pv > 0) && (pTeam2[1].pv > 0) && (pTeam2[2].pv > 0)) ){
		speed_test(pSpeed_Order);
		for(int k=0;k<(2*TAILLETEAM);k++){		
			turn(pSpeed_Order[k], pTeam1, pTeam2, playerOne, playerTwo);
			
				
		
		}

	}
	if ( (pTeam1[0].pv > 0) && (pTeam1[1].pv > 0) && (pTeam1[2].pv > 0)){
		printf("Victoire de l'équipe 1");
	}
	else{
		printf("Victoire de l'équipe 2");
	}
	
}
	



//---------------------------------------------------------------------------------------
int main(){
	Fighter fighter;
	FILE * fichier = NULL;
	FILE * fileSpell = NULL;
	char *filePath="exemple.txt";   
	char *filePath_spell="spells.txt";
        //char *pTemp;

	char playerOne[128] ;
	char playerTwo [128]; 
        memset(playerOne,0,128);
        memset(playerTwo,0,128);
	chooseName(1,playerOne,128); 
	chooseName(2,playerTwo,128); 


	int firstTab[3]={-1,-1,-1};
	int secondTab[3]={-1,-1,-1};
            

	fichier = fopen(filePath,"r+");
	fileSpell = fopen(filePath_spell, "r+");




	if(fichier==NULL){
		printf("Erreur fatale. impossible d'ouvrir le fichier %s \n", filePath);
	}
	else if(fileSpell==NULL){
		printf("Erreur fatale. Impossible d'ouvrir %s \n", filePath_spell);}
	

	Fighter *pTabElement;
	Fighter* tabFighter = NULL;
	int nmbPerso = nombreLignes(fichier)/NOMBRESTAT;
        NombreDePerso=nmbPerso;
	printf("Il y a %d personnages\n", nmbPerso);
	tabFighter = malloc(nmbPerso * sizeof(Fighter));
	// carefull, here we allocate a tab of n fithers but there names are not allocated
	// but its fine we allocate it later

	Spell  *pTabSpell;
	Spell* tabSpell = NULL;

	int nmbSpell = nombreLignes(fileSpell)/NOMBRESTATSORT;
	tabSpell = malloc(nmbSpell * sizeof(Spell));

	if(tabFighter == NULL || tabSpell == NULL){
        	printf("Erreur allocation du tableau\n");
        	exit(1);
	}

	pTabElement = tabFighter;	//repointe au bon endroit
	pTabSpell = tabSpell;		//pareil

	fseek(fichier,0,SEEK_SET);
 	for(int i=0;i<nmbPerso;i++){
		printf("Personnage numéro %d\n", i+1);
        	*pTabElement= constructFighter(fichier);
		//printf("[%s]\n", pTabElement[0].nom);
        	pTabElement++;
	}

	
	fseek(fileSpell,0,SEEK_SET);
	/*for(int i=0;i<nmbSpell;i++){
		printf("Sort numéro %d\n", i+1);
		*pTabSpell= constructSpell(fileSpell);
		pTabSpell++;
	}*/

	pTabElement= tabFighter;
	for(int i=0;i<(nmbSpell/4);i++){
		pTabElement[i].spell1= constructSpell(fileSpell);
		pTabElement[i].spell2= constructSpell(fileSpell);
		pTabElement[i].spell3= constructSpell(fileSpell);
		pTabElement[i].spell4= constructSpell(fileSpell);
		printf("On est là : %s\n",pTabElement[i].spell4.nom);
	}
		

        pTabElement= tabFighter;
	pTabSpell = tabSpell;

	Fighter  Team1[3];
	Fighter  Team2[3];

	champSelectPVP(0, pTabElement, nmbPerso, playerOne, playerTwo, firstTab, secondTab, TAILLETEAM);
	createTeam(pTabElement,firstTab,secondTab,Team1,Team2);
	Fighter * pTeam1;
	Fighter * pTeam2;
        pTeam1=&Team1[0]; 
	pTeam2=&Team2[0]; //ou juste Teamclear()2 marche aussi
	
	
	Fighter Speed_Order[6];
	Fighter * pSpeed_Order;
	pSpeed_Order = Speed_Order;

        pTeam1=&Team1[0];
	pTeam2=&Team2[0];
	fight(pTeam1,pTeam2,pSpeed_Order,playerOne,playerTwo);
	
	//displaytabFighter(tabFighter, nmbFighter);
	return 0;
}

