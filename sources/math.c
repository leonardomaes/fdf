/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmaes <lmaes@student.42porto.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 12:12:08 by lmaes             #+#    #+#             */
/*   Updated: 2024/08/10 12:12:11 by lmaes            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

double	get_radian(int	angle)
{
	double	radian;

	radian = angle * (PI / 180);
	return (radian);
}

void rotate_z(t_points *a, int angle)
{
 int tmp;

 tmp = a->x;
 a->x = tmp * cos(get_radian(angle)) - a->y * sin(get_radian(angle));
 a->y = tmp * sin(get_radian(angle)) + a->y * cos(get_radian(angle));
}

void rotate_y(t_points *a, int angle)
{
 int tmp;

 tmp = a->x;
 a->x = tmp * cos(get_radian(angle)) + a->z * sin(get_radian(angle));
 a->z = a->z * cos(get_radian(angle)) - tmp * sin(get_radian(angle));
}

void rotate_x(t_points *a, int angle)
{
 int tmp;

 tmp = a->y;
 a->y = tmp * cos(get_radian(angle)) - a->z * sin(get_radian(angle));
 a->z = tmp * sin(get_radian(angle)) + a->z * cos(get_radian(angle));
}


void	isometric(double *x, double *y, int z, int angle)
{
	double previous_x;
	double previous_y;

	if (x == NULL || y == NULL)
	{
		printf("Erro with isometric function");
		exit(1);
	}
	previous_x = *x;
	previous_y = *y;
	*x = (previous_x - previous_y) * cos(get_radian(angle));
	*y = (previous_x + previous_y) * sin(get_radian(angle)) - z;
}

double	ft_abs(float n)
{
	if (n < 0)
		return (-n);
	return(n);
}
