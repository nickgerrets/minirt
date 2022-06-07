/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoosten <mjoosten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/01 11:00:30 by mjoosten          #+#    #+#             */
/*   Updated: 2022/06/07 12:14:15 by mjoosten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ray3.h"
#include "collision.h"
#include "shape.h"
#include "shape_masks.h"
#include <math.h>

/* https://en.wikipedia.org/wiki/Line–plane_intersection
**
**     (p0 - l0) . n
** t = -------------
**		   l . n
**
** p0: plane origin
** l0: ray origin
** n: plane normal
** l: ray direction
**
** if the denominator l . n is zero, the ray is perpendicular to the plane
*/
t_collision	collision_plane(const t_shape *plane, const t_ray3 *ray)
{
	t_collision	coll;
	double		denom;
	double		t;

	coll = collision_none();
	denom = vec3_dot(ray->direction, plane->pl.normal);
	if (fabs(denom) < __DBL_EPSILON__)	
		return (coll);
	t = vec3_dot(vec3_sub(plane->origin, ray->origin), plane->pl.normal) / denom;
	if (t > __DBL_EPSILON__)
	{
		coll.point = ray_point(ray, t);
		coll.shape = (t_shape *)plane;
		if (denom < 0)
			coll.normal = plane->pl.normal;
		else
			coll.normal = vec3_inv(plane->pl.normal);
		coll.distance = t;
	}
	return (coll);
}
