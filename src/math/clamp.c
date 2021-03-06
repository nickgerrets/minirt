/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clamp.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mjoosten <mjoosten@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 16:56:09 by mjoosten          #+#    #+#             */
/*   Updated: 2022/06/27 16:56:22 by mjoosten         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

double	clamp(double d, double min, double max)
{
	if (d < min)
		d = min;
	if (d > max)
		d = max;
	return (d);
}
