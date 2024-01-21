/*
Copyright (C) 2015-2018 Parallel Realities

This program is free software; you can redistribute it and/or
modify it under the terms of the GNU General Public License
as published by the Free Software Foundation; either version 2
of the License, or (at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program; if not, write to the Free Software
Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

*/

#include "common.h"

static void logic(void);
static void draw(void);
static void drawHud(void);

void initStage(void)
{
	app.delegate.logic = logic;
	app.delegate.draw = draw;

	memset(&stage, 0, sizeof(Stage));

	stage.entityTail = &stage.entityHead;

	initEntities();

	initPlayer();

	initMap();
}

static void logic(void)
{
	doPlayer();

	doEntities();

	doCamera();
}

static void draw(void)
{
	SDL_SetRenderDrawColor(app.renderer, 220, 20, 40, 255); // changes background colour
	SDL_RenderFillRect(app.renderer, NULL);

	drawMap();

	drawEntities();

	drawHud();
}

static void drawHud(void)
{
	SDL_Rect r;
	long past = 0.0; //allows the digits to appear on the hud screen 
	long now;
	r.x = 0;
	r.y = 0;
	r.w = SCREEN_WIDTH;
	r.h = 35;

	SDL_SetRenderDrawBlendMode(app.renderer, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(app.renderer, 0, 0, 0, 196);
	SDL_RenderFillRect(app.renderer, &r);
	SDL_SetRenderDrawBlendMode(app.renderer, SDL_BLENDMODE_NONE);
	now = SDL_GetTicks(); // initialises now 

	drawText(SCREEN_WIDTH - 5, 5, 255, 255, 255, TEXT_RIGHT, "MAGIC PIZZA %d/%d", stage.pizzaFound, stage.pizzaTotal);  // have not changed variable names for pizza to magic egg as it would make too many errors
	//draws lettering of magic egg and how many magic egg that have been collected 

	drawText(SCREEN_WIDTH - 1060, 5, 255, 255, 255, TEXT_RIGHT, "TIME: %d", now); 
	// changing the digits changes the size of the lettering and also the position 
	// draws timer lettering and how many seconds it has taken to complete level

	drawText(SCREEN_WIDTH - 200, 680, 255, 250, 250, TEXT_RIGHT, " W = UP,A = LEFT,D = RIGHT,SPACE = JUMP E = BOOST %d", stage.pizzaTotal);

}
