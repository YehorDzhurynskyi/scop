/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer_procedure.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "renderer.h"

void		renderer_draw_circle(const t_mat4f *mvp,
								const t_vec4f *color,
								const float radius)
{
	t_gfx_program_circle	*program;

	program = &g_gfx_ctx.pool.circle;
	glUseProgram(program->id);
	glBindVertexArray(g_gfx_ctx.vao_null);
	glUniformMatrix4fv(program->u_location_mvp,
	1, GL_FALSE, &mvp->data[0][0]);
	glUniform4fv(program->u_location_color_tint, 1, (GLfloat*)color);
	glUniform1i(program->u_location_nsegments, 40);
	glUniform1f(program->u_location_radius, radius);
	glDrawArrays(GL_POINTS, 0, 1);
	glBindVertexArray(0);
	glUseProgram(0);
}

void		renderer_draw_cone(const t_mat4f *mvp,
								const t_vec4f *color,
								const float radius,
								const float height)
{
	t_gfx_program_cone	*program;

	program = &g_gfx_ctx.pool.cone;
	glUseProgram(program->id);
	glBindVertexArray(g_gfx_ctx.vao_null);
	glUniformMatrix4fv(program->u_location_mvp,
	1, GL_FALSE, &mvp->data[0][0]);
	glUniform4fv(program->u_location_color_tint, 1, (GLfloat*)color);
	glUniform1i(program->u_location_nsegments, 8);
	glUniform1f(program->u_location_height, height);
	glUniform1f(program->u_location_radius, radius);
	glDrawArrays(GL_POINTS, 0, 1);
	glBindVertexArray(0);
	glUseProgram(0);
}

void		renderer_draw_cube(const t_mat4f *mvp,
								const t_vec4f *color,
								const float size)
{
	t_gfx_program_cube	*program;

	program = &g_gfx_ctx.pool.cube;
	glUseProgram(program->id);
	glBindVertexArray(g_gfx_ctx.vao_null);
	glUniformMatrix4fv(program->u_location_mvp,
	1, GL_FALSE, &mvp->data[0][0]);
	glUniform4fv(program->u_location_color_tint, 1, (GLfloat*)color);
	glUniform1f(program->u_location_size, size);
	glDrawArrays(GL_POINTS, 0, 1);
	glBindVertexArray(0);
	glUseProgram(0);
}

static void	do_draw(t_gfx_program_noshading *program, t_vec4f *b, int *i)
{
	GLuint	vao;
	GLuint	buffers[3];

	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	glGenBuffers(3, buffers);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffers[0]);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * sizeof(int), i, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, buffers[1]);
	glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(t_vec4f), b, GL_STATIC_DRAW);
	glVertexAttribPointer(program->a_location_position,
	4, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(program->a_location_position);
	glBindBuffer(GL_ARRAY_BUFFER, buffers[2]);
	glBufferData(GL_ARRAY_BUFFER, 3 * sizeof(t_vec4f), b, GL_STATIC_DRAW);
	glVertexAttribPointer(program->a_location_color_tint,
	4, GL_FLOAT, GL_FALSE, 0, NULL);
	glEnableVertexAttribArray(program->a_location_color_tint);
	glDrawElements(GL_LINES, 6, GL_UNSIGNED_INT, NULL);
	glDeleteBuffers(3, buffers);
	glDeleteVertexArrays(1, &vao);
	glBindVertexArray(0);
}

void		renderer_draw_actor_basis(const t_actor *actor, const t_mat4f *vp)
{
	t_gfx_program_noshading	*program;
	t_mat4f					mvp;
	t_vec3f					origin;
	t_vec3f					radius;
	t_vec4f					basis[4];

	program = &g_gfx_ctx.pool.noshading;
	glUseProgram(program->id);
	origin = (t_vec3f) { 0.0f, 0.0f, 0.0f };
	mvp = renderer_calculate_local_mvp(actor, vp, &origin, &origin);
	radius = actor_radius_get(actor);
	glUniformMatrix4fv(program->u_location_mvp,
	1, GL_FALSE, &mvp.data[0][0]);
	basis[0] = (t_vec4f) { 1.0f + radius.x, 0.0f, 0.0f, 1.0f };
	basis[1] = (t_vec4f) { 0.0f, 1.0f + radius.y, 0.0f, 1.0f };
	basis[2] = (t_vec4f) { 0.0f, 0.0f, 1.0f + radius.z, 1.0f };
	basis[3] = (t_vec4f) { 0.0f, 0.0f, 0.0f, 1.0f };
	do_draw(program, basis, (int[]){ 3, 0, 3, 1, 3, 2 });
	glUseProgram(0);
}
