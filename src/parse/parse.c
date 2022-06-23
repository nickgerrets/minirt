/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoosten <mjoosten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 13:59:09 by mjoosten          #+#    #+#             */
/*   Updated: 2022/06/23 15:49:46 by mjoosten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "program.h"
#include <fcntl.h>
#include "shape.h"
#include "shape_masks.h"
#include "libft.h"
#include "parse.h"
#include "light.h"

char		**get_args(char *line);
void		build_object(t_program *program, char **args);
t_object	get_object(t_program *program, char *str);
int			open_rt(char *file);

void	build_scene(t_program *program, char *file)
{
	char	**args;
	char	*line;
	int		fd;

	fd = open_rt(file);
	line = ft_get_next_line(fd);
	while (line)
	{
		args = get_args(line);
		if (args[0])
			build_object(program, args);
		free(line);
		ft_free_array(args);
		line = ft_get_next_line(fd);
	}
	close(fd);
	ft_lstiter(program->lights, (void (*)(void *))light_print);
	ft_lstiter(program->shapes, (void (*)(void *))shape_print);
	if (program->camera.fov == 0)
		rt_error(NULL, "Missing camera");
}

char	**get_args(char *line)
{
	char	**args;
	size_t	len;

	len = ft_strlen(line);
	if (len > 0 && line[len - 1] == '\n')
		line[len - 1] = 0;
	if (line[0] == ' ')
		rt_error(NULL, "Line starting with space");
	args = ft_split(line, ' ');
	if (!args)
		rt_error(NULL, "Split allocation failed");
	return (args);
}

void	build_object(t_program *program, char **args)
{
	t_object	object;
	int			argsize;

	argsize = ft_argsize(args);
	object = get_object(program, args[0]);
	if (argsize < object.min_args || argsize > object.max_args)
		rt_error(NULL, "Wrong amount of arguments");
	object.f(args, object.ptr);
}

t_object	get_object(t_program *program, char *str)
{
	const t_object	table[] = {
	{OBJECT_AMBIENCE, "A", 3, 3, build_ambience, &program->ambience},
	{OBJECT_CAMERA, "C", 4, 4, build_camera, &program->camera},
	{OBJECT_LIGHT, "L", 4, 4, build_light, &program->lights},
	{OBJECT_SPHERE, "sp", 4, 5, build_sphere, &program->shapes},
	{OBJECT_PLANE, "pl", 4, 5, build_plane, &program->shapes},
	{OBJECT_CYLINDER, "cy", 6, 7, build_cylinder, &program->shapes},
	{OBJECT_CONE, "co", 6, 7, build_cone, &program->shapes}
	};
	int				tablesize;
	int				len;
	int				i;

	i = 0;
	len = ft_strlen(str);
	tablesize = sizeof(table) / sizeof(*table);
	while (i < tablesize)
	{
		if (ft_strncmp(str, table[i].id, len) == 0)
			return ((t_object){table[i].type, table[i].id, table[i].min_args,
				table[i].max_args, table[i].f, table[i].ptr});
		i++;
	}
	rt_error(str, "not an identifier");
	return ((t_object){});
}

int	open_rt(char *file)
{
	int	fd;
	int	len;

	len = ft_strlen(file);
	if (len < 3 || ft_strncmp(file + len - 3, ".rt", len))
		rt_error(file, "not a .rt file");
	fd = open(file, O_RDONLY);
	if (fd < 0)
	{
		perror(file);
		exit(EXIT_FAILURE);
	}
	return (fd);
}

void	rt_error(char *s1, char *s2)
{
	ft_putstr_fd("Error\n", 2);
	if (s1)
	{
		ft_putstr_fd(s1, 2);
		ft_putstr_fd(": ", 2);
	}
	ft_putendl_fd(s2, 2);
	exit(EXIT_FAILURE);
}
