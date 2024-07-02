
#include <gba_console.h>
#include <gba_video.h>
#include <gba_interrupt.h>
#include <gba_systemcalls.h>
#include <gba_input.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include "sprites.h"

/*COLOR's*/
#define CLR_PURPLE      0xF88F
#define CLR_MY_CYAN		0xF180
#define CLR_BLACK       0x0000
#define CLR_RED         0x001F
#define CLR_LIME        0x03E0
#define CLR_YELLOW      0x03FF
#define CLR_BLUE        0x7C00
#define CLR_MAG         0x7C1F
#define CLR_CYAN        0x7FE0
#define CLR_WHITE       0x7FFF
//---------

#define MEM_VRAM 0x06000000
#define SCREEN_WIDTH 240
#define SCREEN_HEIGHT 160

typedef u16 M3LINE[SCREEN_WIDTH];
#define m3_mem ((M3LINE*)MEM_VRAM)


struct rect {
	int x;
	int y;
	int width;
	int height;
	int velY;
	int velX;
	int PrevX;
	int PrevY;
};

void DrawPixelAt(int x, int y, int color){
	m3_mem[y][x] = color;
}

void DrawRectAt(struct rect*cRect, int color) {
	//define i igual a X de rect enquanto for menor que a largura
	// mesmo se aplica para Y
	for (int i = cRect->x; i < cRect->x + cRect->width; i++) {
		for (int j = cRect->y; j < cRect->y + cRect->height; j++) {
			DrawPixelAt(i, j, color);
		}
	}
}

void ClearAt(struct rect*cRect, int color) {
	//define i igual a X de rect enquanto for menor que a largura
	// mesmo se aplica para Y
	for (int i = cRect->PrevX; i < cRect->PrevX + cRect->width; i++) {
		for (int j = cRect->PrevY; j < cRect->PrevY + cRect->height; j++) {
			DrawPixelAt(i, j, color);
		}
	}
}


void printChar(bool characterArray[25], int x, int y) {
    for (int i=0; i<5; i++) {
        for (int j=0; j<5; j++) {
            int color = CLR_BLACK;
            if (characterArray[i*5+j] == 1) { color = CLR_WHITE; };
            m3_mem[y + i][x + j] = color;
        }
    }
}

void DrawSprite(struct rect*cRect, int sprt[8][8]) {
	int x = cRect->x;
	int y = cRect->y;
	for (int i = x; i < x + cRect->width; i++) {
		for (int j = y; j < y + cRect->height; j++) {
			if (sprt[j-y][i-x] != -1){
				DrawPixelAt(i, j, sprt[j-y][i-x]);
			}
		}
	}
}

bool CollisionVerify(struct rect*cRect, struct rect*cRect2){
	/*obj 1*/
	int x1 = cRect->x;
	int y1 = cRect->y;
	int height1 = cRect->height;
	int width1 = cRect->width;
	/*obj 2*/
	int x2 = cRect2->x;
	int y2 = cRect2->y;
	int height2 = cRect2->height;
	int width2 = cRect2->width;
	
	if(
	(x2 >= x1 && x2 <= height1 + x1 && y2 >= y1 && y2 <= width1 + y1) ||
	(x2 >= x1 && x2 <= height1 + x1 && y2 + width2 >= y1 && y2 + width2 <= width1 + y1) ||
	(x2 + height2 >= x1 && x2 + height2 <= height1 + x1 && y2 >= y1 && y2 <= width1 + y1) ||
	(x2 + height2 >= x1 && x2 + height2 <= height1 + x1 && y2 + width2 >= y1 && y2 + width2 <= width1 + y1)
	) {
			return true;
	}
	
	return false;
}

int main(void) {
	int time_seed_factor = 0;
	int pts = 0;
	int Xoo = pts / 100;
	int oXo = (pts - (Xoo * 100)) / 10;
	int ooX = pts - (Xoo * 100) - (oXo * 10);
	int sprite[8][8];
	memcpy(&sprite, &player_up, sizeof(sprite));
	
	struct rect Background;
	Background.x = 0;
	Background.y = 0;
	Background.width = SCREEN_WIDTH;
	Background.height = SCREEN_HEIGHT;
	DrawRectAt(&Background, CLR_LIME);
	
	/* teste de colisao
	struct rect CollTest;
	CollTest.x = 0;
	CollTest.y = 0;
	CollTest.width = 25;
	CollTest.height = 25;
	*/
	
	srand(time(NULL));
	struct rect Grass0;
	Grass0.x = rand() % (SCREEN_WIDTH - 8);
	Grass0.y = (rand() % (SCREEN_HEIGHT - 18));
	Grass0.width = 8;
	Grass0.height = 8;
	DrawSprite(&Grass0, grass);
	
	struct rect Grass1;
	Grass1.x = rand() % (SCREEN_WIDTH - 8);
	Grass1.y = (rand() % (SCREEN_HEIGHT - 18));
	Grass1.width = 8;
	Grass1.height = 8;
	DrawSprite(&Grass1, grass);
	
	struct rect Grass2;
	Grass2.x = rand() % (SCREEN_WIDTH - 8);
	Grass2.y = (rand() % (SCREEN_HEIGHT - 18));
	Grass2.width = 8;
	Grass2.height = 8;
	DrawSprite(&Grass2, grass);
	
	struct rect Grass3;
	Grass3.x = rand() % (SCREEN_WIDTH - 8);
	Grass3.y = (rand() % (SCREEN_HEIGHT - 18));
	Grass3.width = 8;
	Grass3.height = 8;
	DrawSprite(&Grass3, grass);
	
	struct rect Grass4;
	Grass4.x = rand() % (SCREEN_WIDTH - 8);
	Grass4.y = (rand() % (SCREEN_HEIGHT - 18));
	Grass4.width = 8;
	Grass4.height = 8;
	DrawSprite(&Grass4, grass);
	
	struct rect Grass5;
	Grass5.x = rand() % (SCREEN_WIDTH - 8);
	Grass5.y = (rand() % (SCREEN_HEIGHT - 18));
	Grass5.width = 8;
	Grass5.height = 8;
	DrawSprite(&Grass5, grass);
	
	struct rect Grass6;
	Grass6.x = rand() % (SCREEN_WIDTH - 8);
	Grass6.y = (rand() % (SCREEN_HEIGHT - 18));
	Grass6.width = 8;
	Grass6.height = 8;
	DrawSprite(&Grass6, grass);
	
	struct rect Grass7;
	Grass7.x = rand() % (SCREEN_WIDTH - 8);
	Grass7.y = (rand() % (SCREEN_HEIGHT - 18));
	Grass7.width = 8;
	Grass7.height = 8;
	DrawSprite(&Grass7, grass);
	
	struct rect Grass8;
	Grass8.x = rand() % (SCREEN_WIDTH - 8);
	Grass8.y = (rand() % (SCREEN_HEIGHT - 18));
	Grass8.width = 8;
	Grass8.height = 8;
	DrawSprite(&Grass8, grass);
	
	struct rect Grass9;
	Grass9.x = rand() % (SCREEN_WIDTH - 8);
	Grass9.y = (rand() % (SCREEN_HEIGHT - 18));
	Grass9.width = 8;
	Grass9.height = 8;
	DrawSprite(&Grass9, grass);
	
	struct rect Hud;
	Hud.x = 0;
	Hud.y = SCREEN_HEIGHT - 10;
	Hud.width = SCREEN_WIDTH;
	Hud.height = 10;
	DrawRectAt(&Hud, 0xF093);
	
	irqInit();
	irqEnable(IRQ_VBLANK);

	//GBA Mode set to 3
	SetMode(MODE_3 | BG2_ON);
	
	struct rect Player;
	Player.x = 15;
	Player.y = 15;
	Player.width = 8;
	Player.height = 8;
	Player.velX = 0;
	Player.velY = 0;
	Player.PrevX = Player.x;
	Player.PrevY = Player.y;
	
	/*
	consoleDemoInit();
	// /x1b[line;columnH
	iprintf("\x1b[1;1HPoints: %d \n", pts);
	iprintf("\x1b[2;1HPoints Xoo: %d \n", Xoo);
	iprintf("\x1b[3;1HPoints oXo: %d \n", oXo);
	iprintf("\x1b[4;1HPoints ooX: %d \n", ooX);
	*/
	
	while (1) {
		VBlankIntrWait();
		scanKeys();
		
		/*INPUTS*/
		
		int key_pressed = keysDown();
		int key_released = keysUp();
		
		
		
		if((key_pressed &KEY_UP)) {
			Player.velY = -2;
			memcpy(&sprite, &player_up, sizeof(sprite));
		}
		if((key_pressed &KEY_DOWN)) {
			Player.velY = 2;
			memcpy(&sprite, &player_down, sizeof(sprite));
		}
		
		if((key_released &KEY_UP)||(key_released &KEY_DOWN)){
			Player.velY = 0;
		}
		
		if((key_pressed &KEY_LEFT)) {
			Player.velX = -2;
			memcpy(&sprite, &player_left, sizeof(sprite));
		}
		if((key_pressed &KEY_RIGHT)) {
			Player.velX = 2;
			memcpy(&sprite, &player_right, sizeof(sprite));
		}
		
		if((key_released &KEY_RIGHT)||(key_released &KEY_LEFT)){
			Player.velX = 0;
		}
		
		/*action for inputs*/
		Player.y += Player.velY;
		Player.x += Player.velX;
		
		if (Player.y > 0) {
			Player.y = Player.y % (SCREEN_HEIGHT - 12);
		} else {
			Player.y = SCREEN_HEIGHT - 12 - fabs(Player.y);
		}
		Player.x = Player.x % SCREEN_WIDTH;
		
		/* TESTE DE COLISAO
		if(CollisionVerify(&CollTest, &Player)){
			DrawRectAt(&CollTest, CLR_RED);
		} else {
			DrawRectAt(&CollTest, CLR_BLACK);
		}
		*/
		
		if(CollisionVerify(&Grass0, &Player)){
			pts += 1;
			Grass0.x = rand() % (SCREEN_WIDTH - 8);
			Grass0.y = (rand() % (SCREEN_HEIGHT - 18));
			DrawSprite(&Grass0, grass);
		}
		if(CollisionVerify(&Grass1, &Player)){
			pts += 1;
			Grass1.x = rand() % (SCREEN_WIDTH - 8);
			Grass1.y = (rand() % (SCREEN_HEIGHT - 18));
			DrawSprite(&Grass1, grass);
		}
		if(CollisionVerify(&Grass2, &Player)){
			pts += 1;
			Grass2.x = rand() % (SCREEN_WIDTH - 8);
			Grass2.y = (rand() % (SCREEN_HEIGHT - 18));
			DrawSprite(&Grass2, grass);
		}
		if(CollisionVerify(&Grass3, &Player)){
			pts += 1;
			Grass3.x = rand() % (SCREEN_WIDTH - 8);
			Grass3.y = (rand() % (SCREEN_HEIGHT - 18));
			DrawSprite(&Grass3, grass);
		}
		if(CollisionVerify(&Grass4, &Player)){
			pts += 1;
			Grass4.x = rand() % (SCREEN_WIDTH - 8);
			Grass4.y = (rand() % (SCREEN_HEIGHT - 18));
			DrawSprite(&Grass4, grass);
		}
		if(CollisionVerify(&Grass5, &Player)){
			pts += 1;
			Grass5.x = rand() % (SCREEN_WIDTH - 8);
			Grass5.y = (rand() % (SCREEN_HEIGHT - 18));
			DrawSprite(&Grass5, grass);
		}
		if(CollisionVerify(&Grass6, &Player)){
			pts += 1;
			Grass6.x = rand() % (SCREEN_WIDTH - 8);
			Grass6.y = (rand() % (SCREEN_HEIGHT - 18));
			DrawSprite(&Grass6, grass);
		}
		if(CollisionVerify(&Grass7, &Player)){
			pts += 1;
			Grass7.x = rand() % (SCREEN_WIDTH - 8);
			Grass7.y = (rand() % (SCREEN_HEIGHT - 18));
			DrawSprite(&Grass7, grass);
		}
		if(CollisionVerify(&Grass8, &Player)){
			pts += 1;
			Grass8.x = rand() % (SCREEN_WIDTH - 8);
			Grass8.y = (rand() % (SCREEN_HEIGHT - 18));
			DrawSprite(&Grass8, grass);
		}
		if(CollisionVerify(&Grass9, &Player)){
			pts += 1;
			Grass9.x = rand() % (SCREEN_WIDTH - 8);
			Grass9.y = (rand() % (SCREEN_HEIGHT - 18));
			DrawSprite(&Grass9, grass);
		}
		
		ClearAt(&Player, CLR_LIME);
		DrawSprite(&Player, sprite);
		
		Player.PrevX = Player.x;
		Player.PrevY = Player.y;
		/*------*/
		
		//srand(time(NULL) + key_pressed + key_released);
		//pts = rand() % 6;
		
		DrawRectAt(&Hud, CLR_BLACK);
		Xoo = pts / 100;
		oXo = (pts - (Xoo * 100)) / 10;
		ooX = pts - (Xoo * 100) - (oXo * 10);
		printChar(letter[Xoo], 2, SCREEN_HEIGHT - 8);
		printChar(letter[oXo], 8, SCREEN_HEIGHT - 8);
		printChar(letter[ooX], 14, SCREEN_HEIGHT - 8);
		
		time_seed_factor += 1;
		srand((time(NULL) + key_pressed + key_released + Player.x + Player.y + Player.PrevX + Player.PrevY + pts + time_seed_factor) * time_seed_factor);
		
		/* ATIVAR DEPOIS
		int choice = rand() % 100;
		if(choice >= 99) {
			struct rect Grass;
			Grass.x = rand() % (SCREEN_WIDTH - 8);
			Grass.y = (rand() % (SCREEN_HEIGHT - 18));
			Grass.width = 8;
			Grass.height = 8;
			DrawSprite(&Grass, grass);
		}
		*/
	}
}


