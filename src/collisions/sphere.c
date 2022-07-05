/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   sphere.c                                           :+:    :+:            */
/*                                                     +:+                    */
/*   By: mjoosten <mjoosten@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/01 12:06:19 by ngerrets      #+#    #+#                 */
/*   Updated: 2022/07/05 15:08:43 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "collision.h"
#include "ray3.h"
#include "vec3.h"
#include "shape.h"
#include "shape_masks.h"
#include "equations.h"
#include <math.h>

t_collision	collision_sphere(t_shape *sphere, const t_ray3 *ray)
{
	t_collision	coll;
	t_abc		values;
	t_v3		oc;
	double		t[2];

	oc = vec3_sub(ray->o, sphere->o);
	values.a = 1.0;
	values.b = 2.0 * vec3_dot(ray->d, oc);
	values.c = vec3_dot(oc, oc) - (sphere->sp.radius * sphere->sp.radius);
	if (quadratic(t, values) < 0 || t[0] < 0)
		return (collision_none());
	coll.shape = sphere;
	coll.point = ray_point(ray, t[0]);
	coll.inside = t[1] < 0;
	coll.normal = vec3_norm(vec3_sub(coll.point, sphere->o));
	if (coll.inside)
		coll.normal = vec3_mul(coll.normal, -1.0);
	coll.distance = t[0];
	return (coll);
}
