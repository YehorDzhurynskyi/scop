/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer_interactor.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#include "renderer.h"

static void	renderer_draw_outlines(const t_scene_interactor *interactor,
									const t_mat4f *vp)
{
	t_gfx_program_noshading	*program;
	t_mat4f					model;

	program = &g_gfx_ctx.pool.noshading;
	glUseProgram(program->id);
	glBindVertexArray(interactor->vao);
	model = actor_calculate_matrix_model(interactor->actor_selected);
	model = mat4f_mat4f_mult(&model, vp);
	glUniformMatrix4fv(program->u_location_mvp, 1, GL_FALSE, &model.data[0][0]);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,
	interactor->actor_selected->mesh->ibo_wireframe);
	glDrawElements(GL_LINES, interactor->actor_selected->mesh->nfaces * 6,
	GL_UNSIGNED_INT, NULL);
	glBindVertexArray(0);
	glUseProgram(0);
}

t_mat4f		renderer_calculate_local_mvp(const t_actor *actor,
											const t_mat4f *vp,
											const t_vec3f *offset,
											const t_vec3f *rot)
{
	t_actor fake;
	t_mat4f model;

	fake.position = vec3f_add(&actor->position, offset);
	fake.orientation = transform_rotate(&actor->orientation, rot);
	fake.scale = (t_vec3f) { 1.0f, 1.0f, 1.0f };
	model = actor_calculate_matrix_model(&fake);
	return (mat4f_mat4f_mult(&model, vp));
}

void		renderer_draw_interactor(const t_scene_interactor *interactor)
{
	t_mat4f view;
	t_mat4f proj;

	if (interactor->actor_selected == NULL)
	{
		return ;
	}
	view = camera_calculate_matrix_view(&interactor->scene_target->camera);
	proj = camera_calculate_matrix_proj(&interactor->scene_target->camera);
	view = mat4f_mat4f_mult(&view, &proj);
	renderer_draw_outlines(interactor, &view);
	if (interactor->interaction_mode == TRANSLATION)
	{
		renderer_draw_controls_translation(interactor, &view);
	}
	else if (interactor->interaction_mode == ROTATION)
	{
		renderer_draw_controls_rotation(interactor, &view);
	}
	else if (interactor->interaction_mode == SCALING)
	{
		renderer_draw_controls_scaling(interactor, &view);
	}
}
