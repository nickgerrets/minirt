/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   scene_draw.c                                       :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/03/01 11:42:17 by ngerrets      #+#    #+#                 */
/*   Updated: 2022/05/27 12:41:16 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#include "program.h"
#include "collision.h"
#include "color.h"
#include <math.h>

/*
t_cam	*camera_init(int fov)
{
	t_cam	*cam;

	cam = mmem(sizeof(t_cam));
	cam->o = vec3(0, 0, 0);
	cam->d = vec3(0, 0, 1);
	cam->fovc = tan(fov / 2 * M_PI / 180);
	cam->matrix = matrix_from_dir(cam->o, cam->d);
	return (cam);
}

t_ray	ray_from_cam(double x, double y, t_scene *scene)
{
	t_v3	o;
	t_v3	d;
	t_cam	*camera;
	t_ray	ray;

	camera = scene->cam;
	o = scene->cam->o;
	d = ray_get_dir(x, y, scene);
	ray = ray3(o, d);
	if (scene->shader_sinwave)
		shader_sinwave_to_ray(&ray);
	ray.d = matrix_mul_vec(ray.d, camera->matrix);
	ray.d = vec3_nor(vec3_sub(ray.d, o));
	return (ray);
}

t_v3	ray_get_dir(double x, double y, t_scene *scene)
{
	t_v3	r;

	r.x = (2.0 * (x + 0.5) / (double)scene->width - 1.0)
		* scene->aspect * scene->cam->fovc;
	r.y = (1.0 - 2.0 * (y + 0.5) / (double)scene->height) * scene->cam->fovc;
	r.z = 1.0;
	return (r);
}
*/


static t_v3	_get_origin(t_program *program)
{
	return (program->camera.origin);
}

static t_v3 _get_direction(int x, int y, t_program *program)
{
	t_v3	direction;
	double	fovc;

	fovc = tan(90 / 2 * M_PI / 180);
	direction.x = (2.0 * (x + 0.5) / program->mlx->width - 1.0) * fovc;
	direction.y = (1.0 - 2.0 * (y + 0.5) / program->mlx->height) * fovc;
	direction.z = 1.0;
	vec3_normalize(&direction);
	return (direction);
}

static void	_clear(t_mlx_image *img)
{
	unsigned int	x;
	unsigned int	y;

	x = 0;
	while (x < img->width)
	{
		y = 0;
		while (y < img->height)
		{
			mlx_putpixel(img, x, y, 0xFFFFFFFF);
			y++;
		}
		x++;
	}
}

void	scene_draw(t_program *program)
{
	unsigned int	x;
	unsigned int	y;
	t_collision		coll;
	t_ray3			ray;
	t_color			c;

	_clear(program->buffer);
	y = 0;
	while (y < program->buffer->height)
	{
		x = 0;
		while (x < program->buffer->width)
		{
			ray = ray3(_get_origin(program), _get_direction(x, y, program));
			coll = raycast_get_collision(program->shapes, &ray);
			if (coll.shape != NULL)
				c = coll.shape->color;
			else
				c = color_f(0.5, 0.5, 0.5);
			if (coll.shape != NULL)
				color_luminosity(&c, vec3_dot(vec3(0, 1, 0), coll.normal));
			//color_cap(&c);
			mlx_putpixel(program->buffer, x, y, color_to_int(c));
			x++;
		}
		y++;
	}
}
