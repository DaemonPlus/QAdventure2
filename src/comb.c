/* comb.c */
/* combat encounters and conversation */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "rooms.h"
#include "vars.h"
#include "func.h"
#include "comb.h"

int cResp;
int fResp;
int response;
int kFWin;
int sword1 = 0;
int cSmit = 0;

int fKnight = 0;
int ghoulD = 0;
int wizD = 0;
int draugD = 0;
int archD = 0;

/* room1 knight */

/* talk */
void talkKnight() {
	if(!cKnight && !fKnight && kFWin == 0) {
		cKnight = 1;
		txtdvd();
		printf("> \"Hello, adventurer. I see you come for the crown as well.\"\n");
		printf("> \"I would tell you to leave this place, but speaking frankly,");
		printf("I haven't been having too much luck in here. I'm stuck.\"\n");
		printf("> \"So, how about this:\"\n> \"We have a hand-to-hand duel, and if you can best me, ");
		printf("I'll give you my sword.\"\n\n");
		
		printf("1) Yes, duel the knight in hand-to-hand combat\n2) No, leave\n? ");
		cResp = getAction();
		switch(cResp) {
			case 1:
				fiteKnight();
				break;
			case 2:
				printf("> \"Very well. Perhaps you'll change your mind later.\"");
				break;
			default:
				invalid();
				break;
		}
	}
	else if(cKnight && fKnight && kFWin == 0) {
		cKnight = 1;
		txtdvd();
		printf("\"You changed your mind?\"\n\n");
		
		printf("1) Yes, duel the knight in hand-to-hand combat\n2) No, leave\n? ");
		cResp = getAction();
		switch(cResp) {
			case 1:
				fiteKnight();
				break;
			case 2:
				printf("> \"Very well. Perhaps you'll change your mind later.\"");
				break;
			default:
				invalid();
				break;
		}
	}
	else if(kFWin == 1) {
		txtdvd();
		printf("> \"Perhaps you have better luck than me. Put that sword to good use.\"\n");
		printf("1) Continue\n? ");
		kFWin = 1;
		cResp = getAction();
		switch(cResp) {
			case 1:
				break;
		}
	}
}

/* fight */
void fiteKnight() {
	txtdvd();
	if(cKnight == 1) {
		fKnight = 1;
		printf("> \"Very well. Let's begin\"\n\n");
		/* actually pointless */
		printf("1) Punch face\n2) Kick stomach\n? ");
		fResp = getAction();
		txtdvd();
		printf("> You kick the mercenary in the stomach.\n> He falls to the ground with the air knocked out of his lungs.\n> You win the battle.\n\n"); 
		printf("> \"You've bested me in battle. As promised, I give you my sword.\"\n");
		printf("> You get the sword!\n");
		kFWin = 1;
		sword1 = 1;
		cont();
				
		}
	else {
		fKnight = 1;
		printf("> The mercenary equips his sword, and stabs you through the belly.\n");
		ded = 1;
	}
}
/* kknight rematch */
void remtchKnight() {
	txtdvd();
	printf("> \"Very well. Let's begin\"\n\n");
	printf("1) Kick stomach\n? ");
	fResp = getAction();
	txtdvd();
		printf("> \"You've bested me in battle. As promised, I give you my sword.\"\n");
		printf("> \nYou get the sword!\n");
		kFWin = 1;
		sword1 = 1;
		cont();
}
/* fight ghoul1 */
void fiteGhoul() {
	txtdvd();
	if(kFWin == 1) {
		printf("> You slash at the ghoul, and manage to lop it's head clean off.\n> You've killed the ghoul.\n");
		ghoulD = 1;
		cont();
	}
	else {
		printf("> Without any proper weaponry to defend yourself with, you're quickly torn apart.\n");
		ded = 1;
	}
}

/* talk blacksmith */
void talkSmit() {
	txtdvd();
	/* honestly, my brain is fucking fried. I forgot why i named the `int` "sword1" instead of just "sword" */
	if(gold == 1) {
		printf("1) Upgrade sword - 5 gold pieces\n2) Stop talking\n? ");
		cResp = getAction();
		switch(cResp) {
			case 1:
				/* might not work */
                printf("> Sword upgraded!\n");
				sword1 = 2;
                cont();
				break;
			case 2:
				printf("> \"Alright, then. I'll be seeing you.\"\n");
                cont();
				break;
			default:
				invalid();
				break;

		}

	}
	if(cSmit == 1) {
		/* shit, hopefully this works */
		printf("> \"Hello, boy. What can I do for you?\"\n\n");
		printf("1) Stop talking\n? "); 
		/* add "talk" option l8r */
		cResp = getAction();
		switch(cResp) {
			case 1:
				printf("> \"Alright, then. I'll be seeing you.\"\n");
				break;
			default:
				invalid();
				break;
		}
	}
	else {
		printf("> \"Ack! Let me fix that rusty old sword of yours! No charge, for a seasoned adventurer!\"\n\n");
		printf("1) Yes, upgrade sword\n2) No, don't\n? ");
		/* add "talk" option l8r */
		cResp = getAction();
		switch(cResp) {
			case 1:
				/* this is super fucking ghetto and messy but I cannot be fucked to fix it kek */
				printf("\n> Sword upgraded!\n");	
				cont();
				cSmit = 1;
				break;
			case 2:
				printf("> \"Alright, then. I'll see you.\"");
				cSmit = 0;
				break;
			default:
				invalid();
				break;
		}
	}
}

/* reminder to add option to fight blacksmith */


void fiteWiz() {
	if(cSmit == 1) {
		printf("\n> You take your sword and drive it into the heart of the magician.\n> You win the fight.\n");
		wizD = 1;
		cont();
	}
	else if(sword1 == 1 && cSmit == 0) {
		printf("\n> You take your sword and stab it into the heart of the magician.\n");
		printf("> The shoddy blade bounces off of the magician's armour.\n");
		ded = 1;	
	}
	else if(sword1 == 0) {
		printf("\n> Without any proper weaponry to defend yourself with, you are unable to fight.\n");
		printf("> The magician casts a spell to turn you into a slug "/* hmmm */"and steps on you.\n");
		ded = 1;
	}
}

void fiteDraugr() {
    if(sword1 == 2) { 
        printf("\n> Your powerful blade slices through the draugr's shield like butter.\n> You make quick work of the beast.\n> You have won the battle.\n");
        draugD = 1;
        cont();
        
    }
    else {
        printf("\n\n> Your sword fails to pierce through the draugr's shield.\n> Your flimsy blade bounces off the shield and the draugr drives his sword into your abdomen.\n");
        ded = 1;
    }
}   

void fiteArch() {
    if(draugD == 0) {
        printf("\n> You begin to sprint at the archer, and before you can even get close to him, he shoots you in the heart with an arrow.\n");
        ded = 1;
    }
    if(draugD == 1) {
        printf("\n> You begin to sprint at the archer with your shield in front of you.\n> The archer tries to stop you with hs arrows, but they bounce");
        printf(" off your shield. You get close enough to the archer to attack, and you drive your sword into his heart.\n");
        printf("> You have won the battle\n");
        /* reminder to do the thing */
        archD = 1;
        cont();
    }
}
