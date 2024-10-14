/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmaes <lmaes@student.42porto.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 14:37:31 by lmaes             #+#    #+#             */
/*   Updated: 2024/10/07 14:37:32 by lmaes            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf_bonus.h"

void	rotate_x(t_points *a, float alpha)
{
	int	tmp;

	tmp = a->y;
	a->y = tmp * cos(alpha) - a->z * sin(alpha);
	a->z = tmp * sin(alpha) + a->z * cos(alpha);
}

void	rotate_y(t_points *a, float beta)
{
	int	tmp;

	tmp = a->x;
	a->x = tmp * cos(beta) + a->z * sin(beta);
	a->z = a->z * cos(beta) - tmp * sin(beta);
}

void	rotate_z(t_points *a, float gamma)
{
	int	tmp;

	tmp = a->x;
	a->x = tmp * cos(gamma) - a->y * sin(gamma);
	a->y = tmp * sin(gamma) + a->y * cos(gamma);
}
