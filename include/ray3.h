/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray3.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoosten <mjoosten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 19:08:36 by ngerrets          #+#    #+#             */
/*   Updated: 2022/07/08 11:15:57 by mjoosten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY3_H
# define RAY3_H

# include "vec3.h"

/**
**	Represents a 3-dimensional ray
**	@param o <t_v3> Origin point of the ray
**	@param d <t_v3> Normalized vector as direction
**  @param bounces <int> Amount of times ray has bounced
**  @param index <double> Refractive index of the material the ray is in
*/
typedef struct s_ray3
{
	t_v3	o;
	t_v3	d;
	int		bounces;
	double	index;
}			t_ray3;

/* ray3.c */
t_v3	ray_point(const t_ray3 *ray, double t);

/* ray_debug.c */
void	ray_print(t_ray3 ray3);

#endif
