/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   program.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoosten <mjoosten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 17:36:28 by ngerrets          #+#    #+#             */
/*   Updated: 2022/06/07 13:32:32 by mjoosten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROGRAM_H
# define PROGRAM_H

# include "MLX42/MLX42.h"
# include "libft.h"
# include <stdlib.h>
# include "vec3.h"
# include "light.h"
# include "mat4.h"
# include "threads.h"

# define WINDOW_W 1280
# define WINDOW_H 800
# define WINDOW_TITLE "WINDOW TITLE"
# define WINDOW_RESIZE 0

// typedef struct s_img
// {
//     void    *mlx_img;
//     void    *addr;
// }           t_img;

/**
**	Camera data
**	@param origin <t_v3> Origin point vector
**	@param direction <t_v3> Normal vector
**	@param view_matrix <t_mat4> Camera view matrix for rotation calculation
**	@param fov <float> Field of view
*/
typedef struct s_cam
{
	t_v3	origin;
	t_v3	direction;
	t_mat4	view_matrix;
	float	fov;
}			t_cam;

/**
**	Holds important data needed throughout the program
**	@param mlx <t_mlx*> Main MLX42 pointer
**	@param buffer <t_mlx_image*> MLX42-Image that holds the screen buffer
**	@param shapes <t_list*> Pointer to first element of all the shapes
**	@param light <t_list*> Pointer to first element of all the lights
*/
typedef struct s_program
{
	t_mlx		*mlx;
	t_mlx_image	*buffer;
	t_threads	threads;
	t_cam		camera;
	t_ambience	ambience;
	int			lights_amount;
	t_list		*lights;
	t_list		*shapes;
}				t_program;

/* program_init.c */
t_program	program_get(void);
void		program_run(t_program *program);
void		program_terminate(t_program *program);

/* camera.c */
void		camera_calculate_matrix(t_cam *camera);

/* parse.c */
void		build_scene(t_program *program, char *file);

/* scene_draw.c */
void		scene_draw(void *ptr);

#endif
