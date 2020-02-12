/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "input.h"
#include <SDL.h>
#include <math.h>
#include <assert.h>

#define ACTOR_SPEED		0.3
#define ACTOR_ROT_SPEED	1.5

void	input_handle(t_scene_interactor *interactor)
{
    const Uint8	*keystate;
    SDL_Keymod  mod;

    assert(interactor);
    assert(interactor->scene_target);
    mod = SDL_GetModState();
    keystate = SDL_GetKeyboardState(NULL);
    if (interactor->actor_selected)
    {
        if (keystate[SDL_SCANCODE_ESCAPE])
        {
            interactor->actor_selected = NULL;
        }
        else if (mod & KMOD_LCTRL)
        {
            if (keystate[SDL_SCANCODE_S])
            {
                interactor->interaction_mode = SCALING;
            }
            else if (keystate[SDL_SCANCODE_R])
            {
                interactor->interaction_mode = ROTATION;
            }
            else if (keystate[SDL_SCANCODE_T])
            {
                interactor->interaction_mode = TRANSLATION;
            }
        }
        else if (keystate[SDL_SCANCODE_1])
        {
            if (interactor->interaction_mode == TRANSLATION)
            {

            }
        }
    }
    input_handle_camera(&interactor->scene_target->camera);
}