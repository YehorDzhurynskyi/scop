/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INPUT_H
# define INPUT_H

# include "scene/scene.h"
# include <glad/glad.h>

enum	e_actor_interaction_mode
{
	TRANSLATION,
	ROTATION,
	SCALING
};

typedef struct s_scene_interactor	t_scene_interactor;
struct	s_scene_interactor
{
	t_scene							*scene_target;

	enum e_actor_interaction_mode	interaction_mode;
	t_actor							*actor_selected;

	GLuint							vao;
	GLuint							vbo_outline_color;
};

typedef struct s_app	t_app;

void	input_handle(t_app *app, t_scene_interactor *interactor);
void	input_handle_camera(t_app *app, t_camera *camera);

t_bool	scene_interactor_init(t_scene_interactor *interactor,
const t_scene *scene);
void	scene_interactor_delete(t_scene_interactor *interactor);
void	scene_interactor_select_actor(t_scene_interactor *interactor,
const t_actor *actor);

#endif
