/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmaes <lmaes@student.42porto.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 12:49:53 by lmaes             #+#    #+#             */
/*   Updated: 2024/07/18 12:49:53 by lmaes            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	var_init(t_data *fdf)
{
	fdf->map->zoom = 0.50;
	fdf->map->size = 0;
	fdf->map->x_offset = WINDOW_WIDTH * 2 / 5;
	fdf->map->y_offset = WINDOW_HEIGHT * 1 / 5;
	fdf->map->angle = 30;
	fdf->map->view = 2;
	fdf->map->size_applyed = 0;
	fdf->map->alpha = 0;
	fdf->map->beta = 0;
	fdf->map->gamma = 0;
	retore_original_z(fdf);
}

double	get_radian(int angle)
{
	double	radian;

	radian = angle * (PI / 180);
	return (radian);
}

int	adjust_z_value(t_points *point, int flag, t_data *fdf)
{
	if (flag == 1)
	{
		if (point->z >= 0)
			point->z += point->original_z;
		else
			point->z -= abs(point->original_z);
		return (1);
	}
	else if (flag == -1 && fdf->map->size_applyed > 0)
	{
		if (point->z >= 0)
			point->z -= point->original_z;
		else
			point->z += abs(point->original_z);
		return (1);
	}
	return (0);
}

void	apply_size(t_data *fdf, int flag)
{
	int	x;
	int	y;
	int	changed;

	changed = 0;
	y = 0;
	while (y < fdf->map->cols)
	{
		x = 0;
		while (x < fdf->map->rows)
		{
			changed = adjust_z_value(&fdf->points[x][y], flag, fdf);
			x++;
		}
		y++;
	}
	if (changed)
	{
		if (flag == 1)
			fdf->map->size_applyed++;
		else if (flag == -1)
			fdf->map->size_applyed--;
	}
}

void	retore_original_z(t_data *fdf)
{
	int	x;
	int	y;

	y = 0;
	while (y < fdf->map->cols)
	{
		x = 0;
		while (x < fdf->map->rows)
		{
			fdf->points[x][y].z = fdf->points[x][y].original_z;
			x++;
		}
		y++;
	}
}
