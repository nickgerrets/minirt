/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoosten <mjoosten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/17 14:22:16 by mjoosten          #+#    #+#             */
/*   Updated: 2022/07/08 11:02:24 by mjoosten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "material.h"
#include "config.h"
#include "libft.h"
#include <math.h>
#include <stdio.h>
#include "program.h"
#include "parse.h"

t_material	parse_material(char *str)
{
	static const t_material	table[] = {
	{"default", 0.0, 0.0, 1, DEFAULT_SHINE, DEFAULT_PHONG, 0},
	{"clouds", 0.0, 0.6, 1.5, 0.0, DEFAULT_PHONG, 0},
	{"water", 0.2, 0.5, 1.3, DEFAULT_SHINE, DEFAULT_PHONG, 0},
	{"mirror", 0.9, 0.0, 1.0, DEFAULT_SHINE, DEFAULT_PHONG, 0},
	{"planet", 0.0, 0.0, 1.0, 0.2, 2.0, 0},
	{"glass", 0.0, 0.9, 1.5, 4.0, 4.0, 0},
	{"star", 0.0, 0.4, 1.0, 0.8, 2.0, 0},
	{"shine", 0.0, 0.0, 1.0, 2.6, 2.2, 0},
	{"metal", 0.3, 0.0, 2.0, 1.2, 16.0, 0},
	{"transparent", 0.0, 0.9, 1.0, DEFAULT_SHINE, DEFAULT_PHONG, 0},
	{"checkerboard", 0.0, 0.0, 1.0, DEFAULT_SHINE, DEFAULT_PHONG, 1}
	};

	if (!str)
		return (table[0]);
	return (table[table_entry(
				(const char *)table,
				sizeof(table) / sizeof(*table),
				str,
				sizeof(t_material))]);
}

void	material_print(const t_material *material)
{
	printf("|  MATERIAL:\n");
	printf("|  |   name: %s\n", material->name);
	printf("|  |   reflection: %.3f\n", material->reflection);
	printf("|  |   refraction: %.3f\n", material->refraction);
	printf("|  |   refractive index: %.3f\n", material->index);
	printf("|  |   shine: %.3f\n", material->shine);
	printf("|  |   checkerboard: %d\n", material->checkerboard);
}
