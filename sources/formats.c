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

#include <X11/X.h>
#include "../fdf.h"

void	draw_bresenham(t_points a, t_points b, t_data *fdf)
{
	t_draw	draw;
	int	steps;
	int	i;

	draw.dx = fabs(b.x - a.x);
	draw.dy = fabs(b.y - a.y);
	draw.sx = (a.x < b.x) ? 1 : -1;
	draw.sy = (a.y < b.y) ? 1 : -1;
	draw.err = (draw.dx > draw.dy ? draw.dx : -draw.dy) / 2;
	steps = (draw.dx > draw.dy) ? draw.dx : draw.dy;
	i = 0;
	while (i <= steps)
	{
		if (a.x >= 0 && a.x < WINDOW_WIDTH && a.y >= 0 && a.y < WINDOW_HEIGHT)
		{
			if (a.color == 0)
				my_mlx_pixel_put(fdf, a.x, a.y, fdf->map->color);
			else
				my_mlx_pixel_put(fdf, a.x, a.y, a.color);
		}
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

	ft_bzero(fdf->mlx.addr, WINDOW_WIDTH * WINDOW_HEIGHT * (fdf->mlx.bits_per_pixel / 8));
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
