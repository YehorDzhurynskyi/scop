/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec_sub.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ydzhuryn <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/21 14:29:49 by ydzhuryn          #+#    #+#             */
/*   Updated: 2017/11/24 13:51:56 by ydzhuryn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec.h"

t_vec3f	vec3f_sub(t_vec3f const *v1, t_vec3f const *v2)
{
	return ((t_vec3f){v1->x - v2->x, v1->y - v2->y, v1->z - v2->z});
}

t_vec3d	vec3d_sub(t_vec3d const *v1, t_vec3d const *v2)
{
	return ((t_vec3d){v1->x - v2->x, v1->y - v2->y, v1->z - v2->z});
}

t_vec4f	vec4f_sub(t_vec4f const *v1, t_vec4f const *v2)
{
	return ((t_vec4f){v1->x - v2->x, v1->y - v2->y,
	v1->z - v2->z, v1->w - v2->w});
}

t_vec4d	vec4d_sub(t_vec4d const *v1, t_vec4d const *v2)
{
	return ((t_vec4d){v1->x - v2->x, v1->y - v2->y,
	v1->z - v2->z, v1->w - v2->w});
}
