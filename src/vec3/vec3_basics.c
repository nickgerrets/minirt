/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_basics.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoosten <mjoosten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 19:15:30 by ngerrets          #+#    #+#             */
/*   Updated: 2022/07/04 13:37:23 by mjoosten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "vec3.h"
#include <math.h>

t_v3	vec3(double x, double y, double z)
{
	return ((t_v3){x, y, z});
}

/* Also known as magnitude */
double	vec3_length(t_v3 vec3)
{
	return (sqrt(vec3.x * vec3.x + vec3.y * vec3.y + vec3.z * vec3.z));
}

t_v3	vec3_norm(t_v3 v)
{
	double	length;

	length = vec3_length(v);
	return (vec3_mul(v, 1.0 / length));
}
