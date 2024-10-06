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
	fdf->map->color = WHITE_PIXEL;
	fdf->map->view = 2;
	retore_original_z(fdf);
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

void	get_next_color(t_data *fdf, int flag)
{
	if (flag == 1)
	{
		if (fdf->map->color == WHITE_PIXEL)
			fdf->map->color = GREEN_PIXEL;
		if (fdf->map->color == GREEN_PIXEL)
			fdf->map->color = BLUE_PIXEL;
		if (fdf->map->color == BLUE_PIXEL)
			fdf->map->color = RED_PIXEL;
		if (fdf->map->color == RED_PIXEL)
			fdf->map->color = WHITE_PIXEL;
	}
	else
	if (flag == -1)
	{
		if (fdf->map->color == WHITE_PIXEL)
			fdf->map->color = RED_PIXEL;
		if (fdf->map->color == RED_PIXEL)
			fdf->map->color = BLUE_PIXEL;
		if (fdf->map->color == BLUE_PIXEL)
			fdf->map->color = GREEN_PIXEL;
		if (fdf->map->color == GREEN_PIXEL)
			fdf->map->color = WHITE_PIXEL;
	}
}

void	apply_rotate(t_data *fdf, int	flag)
{
	int	x;
	int	y;

	y = 0;
	while (y < fdf->map->cols)
	{
		x = 0;
		while (x < fdf->map->rows)
		{
			if (flag == 1)
			{
				rotate_x(&fdf->points[x][y], 0);
				rotate_y(&fdf->points[x][y], 0);
				rotate_z(&fdf->points[x][y], 0);
			}
			if (flag == 2)
			{
				rotate_x(&fdf->points[x][y], 90);
				rotate_y(&fdf->points[x][y], 0);
				rotate_z(&fdf->points[x][y], 0);
			}
			if (flag == 3)
			{
				rotate_x(&fdf->points[x][y], 0);
				rotate_y(&fdf->points[x][y], 90);
				rotate_z(&fdf->points[x][y], -90);
			}	
			x++;
		}
		y++;
	}
}
