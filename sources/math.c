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

void    calculate_offset(t_data *fdf)
{
	t_offset	offset;
	t_points	point;
	int	x;
	int	y;

	offset.min_x = WINDOW_WIDTH;
	offset.max_x = 0;
	offset.min_y = WINDOW_HEIGHT;
	offset.max_y = 0;
	y = 0;
	while (y < fdf->map->rows)
	{
		x = 0;
		while (x < fdf->map->cols)
		{
			point = fdf->points[x][y];
			isometric(&point.x, &point.y, point.z);
			if (point.x < offset.min_x) offset.min_x = point.x;
			if (point.x > offset.max_x) offset.max_x = point.x;
			if (point.y < offset.min_y) offset.min_y = point.y;
			if (point.y > offset.max_y) offset.max_y = point.y;
			x++;
		}
		y++;
	}
	fdf->map->x_offset = (fdf->map->width / 2) - (offset.min_x + (offset.max_x - offset.min_x) / 2);
	fdf->map->y_offset = (fdf->map->height / 2) - (offset.min_y + (offset.max_y - offset.min_y) / 2);
}

void	isometric(double *x, double *y, int z)
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
	*x = (previous_x - previous_y) * cos(0.523599);
	*y = (previous_x + previous_y) * sin(0.523599) - z;
}

double	ft_abs(float n)
{
	if (n < 0)
		return (-n);
	return(n);
}
