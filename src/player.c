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

static SDL_Texture *pete[2];

void initPlayer(void)
{
	player = malloc(sizeof(Entity));
	memset(player, 0, sizeof(Entity));
	stage.entityTail->next = player;
	stage.entityTail = player;

	player->health = 1;

	pete[0] = loadTexture("gfx/pete01.png");
	pete[1] = loadTexture("gfx/pete02.png");

	player->texture = pete[0];

	SDL_QueryTexture(player->texture, NULL, NULL, &player->w, &player->h);
}

void doPlayer(void)
{
	player->dx = 0;

	if (app.keyboard[SDL_SCANCODE_A])
	{
		player->dx = -PLAYER_MOVE_SPEED;

		player->texture = pete[1];
	}

	if (app.keyboard[SDL_SCANCODE_D])
	{
		player->dx = PLAYER_MOVE_SPEED;

		player->texture = pete[0];
	}

	if (player->isOnGround) jump_counter = 0;

	if (app.keyboard[SDL_SCANCODE_SPACE] && player->isOnGround && (jump_counter == 0))
		//this changes the keybind for jumping to SPACE, the jumping function only occurs if the character is on the ground.
	{
		player->riding = NULL;
		player->dy = -20; // postion of the character must be the same to ensure double jump works
		playSound(SND_JUMP, CH_PLAYER);
	}

	if (app.keyboard[SDL_SCANCODE_E] && ((player->isOnGround) == 0) && (jump_counter < 10)) 
		// this changes the double jump/ boost to the key E, once pressed the player will be able to double jump mid air.
	{

		jump_counter++;// checks the players jump counter and initiates double jump depending on value 
		player->riding = NULL;
		player->dy = -20;

		

		playSound(SND_JUMP, CH_PLAYER);

	}

	



	if (app.keyboard[SDL_SCANCODE_ESCAPE]) // checks if the player has pressed the ESCAPE key to reset the level
	{
		player->x = player->y = 0; // places player back to beginning part of the level ( resets player coordinates )

		app.keyboard[SDL_SCANCODE_ESCAPE] = 0; // back to position 0 for the player once the key ESCAPE is pressed
	}
}
