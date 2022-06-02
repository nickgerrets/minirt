/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   material.h                                         :+:    :+:            */
/*                                                     +:+                    */
/*   By: ngerrets <ngerrets@student.codam.nl>         +#+                     */
/*                                                   +#+                      */
/*   Created: 2022/06/02 11:54:38 by ngerrets      #+#    #+#                 */
/*   Updated: 2022/06/02 12:28:22 by ngerrets      ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATERIAL_H
# define MATERIAL_H

typedef enum e_material_type
{
	MATERIAL_DEFAULT = 0,
	MATERIAL_MIRROR
}	t_material_type;

/**
**	data to define behaviour of impacting rays
**	@param reflection	<float> percentage (0.0 - 1.0)
**
*/
typedef struct s_material
{
	t_material_type	type;
	float			reflection;
}	t_material;

#endif
