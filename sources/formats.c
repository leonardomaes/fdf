/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formats.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmaes <lmaes@student.42porto.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 13:12:56 by lmaes             #+#    #+#             */
/*   Updated: 2024/07/11 13:12:57 by lmaes            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"
#include <X11/X.h>

void	isometric(double *x, double *y, int z, int angle)
{
	double	previous_x;
	double	previous_y;

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

int	init_param(t_points *a, t_points *b, t_draw *draw)
{
	int	steps;

	draw->dx = fabs(b->x - a->x);
	draw->dy = fabs(b->y - a->y);
	if (a->x < b->x)
		draw->sx = 1;
	else
		draw->sx = -1;
	if (a->y < b->y)
		draw->sy = 1;
	else
		draw->sy = -1;
	if (draw->dx > draw->dy)
		draw->err = draw->dx / 2;
	else
		draw->err = -draw->dy / 2;
	if (draw->dx > draw->dy)
		steps = draw->dx;
	else
		steps = draw->dy;
	return (steps);
}

void	draw_bresenham(t_points a, t_points b, t_data *fdf)
{
	t_draw	draw;
	int		steps;
	int		i;

	steps = init_param(&a, &b, &draw);
	i = 0;
	while (i <= steps)
	{
		if (a.x >= 0 && a.x < WINDOW_WIDTH && a.y >= 0 && a.y < WINDOW_HEIGHT)
			my_mlx_pixel_put(fdf, a.x, a.y, a.color);
		draw.e2 = draw.err;
		if (draw.e2 > -draw.dx)
		{
			draw.err -= draw.dy;
			a.x += draw.sx;
		}
		if (draw.e2 < draw.dy)
		{
			draw.err += draw.dx;
			a.y += draw.sy;
		}
		i++;
	}
}

void	draw_lines(t_data *fdf, t_points a, t_points b)
{
	fdf->map->width = WINDOW_WIDTH * fdf->map->zoom;
	fdf->map->height = WINDOW_HEIGHT * fdf->map->zoom;
	a.x = a.x * (fdf->map->width / fdf->map->cols);
	a.y = a.y * (fdf->map->height / fdf->map->rows);
	b.x = b.x * (fdf->map->width / fdf->map->cols);
	b.y = b.y * (fdf->map->height / fdf->map->rows);
	if (fdf->map->view == 2)
	{
		rotate_x(&a, fdf->map->alpha);
		rotate_y(&a, fdf->map->beta);
		rotate_z(&a, fdf->map->gamma);
		rotate_x(&b, fdf->map->alpha);
		rotate_y(&b, fdf->map->beta);
		rotate_z(&b, fdf->map->gamma);
		isometric(&a.x, &a.y, a.z, fdf->map->angle);
		isometric(&b.x, &b.y, b.z, fdf->map->angle);
	}
	a.x += fdf->map->x_offset;
	a.y += fdf->map->y_offset;
	b.x += fdf->map->x_offset;
	b.y += fdf->map->y_offset;
	draw_bresenham(a, b, fdf);
}

void	print_fdf(t_data *fdf)
{
	int	i;
	int	j;

	ft_bzero(fdf->mlx.addr, WINDOW_WIDTH * WINDOW_HEIGHT
		* (fdf->mlx.bits_per_pixel / 8));
	i = 0;
	while (i < fdf->map->cols)
	{
		j = 0;
		while (j < fdf->map->rows)
		{
			if (j < fdf->map->rows - 1)
			{
				draw_lines(fdf, fdf->points[j][i], fdf->points[j + 1][i]);
			}
			if (i < fdf->map->cols - 1)
			{
				draw_lines(fdf, fdf->points[j][i], fdf->points[j][i + 1]);
			}
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(fdf->mlx.mlx, fdf->mlx.win, fdf->mlx.img, 0, 0);
}
