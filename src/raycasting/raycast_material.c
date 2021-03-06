/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   raycast_material.c                                 :+:    :+:            */
/*                                                     +:+                    */
/*   By: mjoosten <mjoosten@student.42.fr>            +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/02 11:50:42 by ngerrets      #+#    #+#                 */
/*   Updated: 2022/07/07 14:28:52 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "program.h"
#include "material.h"
#include "raycasting.h"
#include "shape.h"
#include "vec3.h"
#include "color.h"
#include "ray3.h"

#define REFLECTION 0
#define REFRACTION 1

//	For checkerboard material
t_color	checkerboard_color(t_v3 coordinates)
{
	double	x;
	double	y;

	x = 12.0 * coordinates.x + __FLT_EPSILON__;
	y = 12.0 * coordinates.y + __FLT_EPSILON__;
	if (((int)y % 2 && (int)x % 2) || ((int)y % 2 == 0 && (int)x % 2 == 0))
		return ((t_color){0, 0, 0});
	return ((t_color){1.0, 1.0, 1.0});
}

t_ray3	modified_ray(const t_ray3 *ray, const t_rdata *rdata, int mode)
{
	t_ray3	mray;

	mray.o = vec3_sub(rdata->coll.point, vec3_mul(ray->d, __FLT_EPSILON__));
	if (mode == REFLECTION)
		mray.d = vec3_calc_reflection(ray->d, rdata->coll.normal);
	else
		mray.d = vec3_calc_refraction(ray->d, rdata->coll.normal, ray->index,
				rdata->coll.shape->material.index);
	if (mode == REFRACTION)
		mray.o = vec3_add(mray.o, vec3_mul(mray.d, __FLT_EPSILON__));
	mray.bounces = ray->bounces + 1;
	if (!rdata->coll.inside && mode == REFRACTION)
		mray.index = rdata->coll.shape->material.index;
	else
		mray.index = 1.0;
	return (mray);
}

t_color	blend_ray(const t_program *program,
	const t_ray3 *ray,
	t_rdata rdata,
	int mode)
{
	t_rdata	new_rd;
	t_ray3	mray;
	float	percentage;

	mray = modified_ray(ray, &rdata, mode);
	new_rd = raycast(program, &mray);
	if (new_rd.coll.shape == NULL)
		new_rd.color = (t_color){0, 0, 0};
	if (mode == REFLECTION)
		percentage = rdata.coll.shape->material.reflection;
	else
		percentage = rdata.coll.shape->material.refraction;
	return (color_blend(rdata.color, new_rd.color, percentage));
}

t_rdata	material_cast(const t_program *program,
	const t_ray3 *ray,
	t_rdata rdata)
{
	rdata.color = raycast_calc_lighting(program, rdata.coll);
	if (ray->bounces >= RAY_MAX_BOUNCES)
		return (rdata);
	if (rdata.coll.shape->material.reflection > 0)
		rdata.color = blend_ray(program, ray, rdata, REFLECTION);
	if (rdata.coll.shape->material.refraction > 0)
		rdata.color = blend_ray(program, ray, rdata, REFRACTION);
	return (rdata);
}
