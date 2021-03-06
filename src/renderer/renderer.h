/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   renderer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 15:08:24 by ydzhuryn          #+#    #+#             */
/*   Updated: 2018/01/05 17:20:48 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDERER_H
# define RENDERER_H

# include "input/input.h"
# include "shader.h"

typedef struct s_texture	t_texture;
struct	s_texture
{
	t_byte		*raw;
	uint32_t	width;
	uint32_t	height;
	uint32_t	pitch;
	uint16_t	bpp;
};

t_bool	texture_load_bmp(const char *filename, t_texture *ctexture);
void	texture_delete(t_texture *texture);

typedef struct s_gfx_program_phong	t_gfx_program_phong;
struct	s_gfx_program_phong
{
	GLuint	id;

	GLint	u_location_mvp;
	GLint	u_location_is_smooth_mode_enabled;
	GLint	u_location_palette;
	GLint	u_location_texture;

	GLint	a_location_position;
	GLint	a_location_color_tint;
	GLint	a_location_color;
};

typedef struct s_gfx_program_noshading	t_gfx_program_noshading;
struct	s_gfx_program_noshading
{
	GLuint	id;

	GLint	u_location_mvp;

	GLint	a_location_position;
	GLint	a_location_color_tint;
};

typedef struct s_gfx_program_grid	t_gfx_program_grid;
struct	s_gfx_program_grid
{
	GLuint	id;

	GLint	u_location_mvp;
	GLint	u_location_dimension;
	GLint	u_location_nsteps;
	GLint	u_location_color_tint;
};

typedef struct s_gfx_program_circle	t_gfx_program_circle;
struct	s_gfx_program_circle
{
	GLuint	id;

	GLint	u_location_mvp;
	GLint	u_location_nsegments;
	GLint	u_location_color_tint;
	GLint	u_location_radius;
};

typedef struct s_gfx_program_cone	t_gfx_program_cone;
struct	s_gfx_program_cone
{
	GLuint	id;

	GLint	u_location_mvp;
	GLint	u_location_height;
	GLint	u_location_radius;
	GLint	u_location_nsegments;
	GLint	u_location_color_tint;
};

typedef struct s_gfx_program_cube	t_gfx_program_cube;
struct	s_gfx_program_cube
{
	GLuint	id;

	GLint	u_location_mvp;
	GLint	u_location_size;
	GLint	u_location_color_tint;
};

typedef struct s_gfx_program_pool	t_gfx_program_pool;
struct	s_gfx_program_pool
{
	t_gfx_program_phong		phong;
	t_gfx_program_noshading	noshading;
	t_gfx_program_grid		grid;
	t_gfx_program_circle	circle;
	t_gfx_program_cone		cone;
	t_gfx_program_cube		cube;
};

typedef struct s_gfx_ctx	t_gfx_ctx;
struct	s_gfx_ctx
{
	t_gfx_program_pool	pool;
	GLuint				vao_null;
};
extern t_gfx_ctx	g_gfx_ctx;

t_bool	renderer_init(t_gfx_ctx *ctx);
void	renderer_delete(t_gfx_ctx *ctx);

t_bool	renderer_init_noshading_program(t_gfx_program_noshading *program);
t_bool	renderer_init_phong_program(t_gfx_program_phong *program);
t_bool	renderer_init_grid_program(t_gfx_program_grid *program);
t_bool	renderer_init_circle_program(t_gfx_program_circle *program);
t_bool	renderer_init_cone_program(t_gfx_program_cone *program);
t_bool	renderer_init_cube_program(t_gfx_program_cube *program);

t_bool	renderer_init_gfx_mesh(t_mesh *mesh);
t_bool	renderer_init_gfx_interactor(t_scene_interactor *interactor);
void	renderer_delete_gfx_mesh(t_mesh *mesh);
void	renderer_delete_gfx_interactor(t_scene_interactor *interactor);

void	renderer_draw_scene(const t_scene *scene);
void	renderer_draw_interactor(const t_scene_interactor *interactor);
void	renderer_draw_controls_translation(const t_scene_interactor *interactor,
const t_mat4f *vp);
void	renderer_draw_controls_rotation(const t_scene_interactor *interactor,
const t_mat4f *vp);
void	renderer_draw_controls_scaling(const t_scene_interactor *interactor,
const t_mat4f *vp);

void	renderer_draw_circle(const t_mat4f *mvp,
const t_vec4f *color, const float radius);
void	renderer_draw_cone(const t_mat4f *mvp,
const t_vec4f *color, const float radius, const float height);
void	renderer_draw_cube(const t_mat4f *mvp,
const t_vec4f *color, const float size);
void	renderer_draw_actor_basis(const t_actor *actor, const t_mat4f *vp);

t_mat4f	renderer_calculate_local_mvp(const t_actor *actor,
const t_mat4f *vp, const t_vec3f *offset, const t_vec3f *rot);

#endif
