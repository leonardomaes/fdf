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

void	bresenham(t_points a, t_points b, t_data *fdf)
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
	a.x = a.x * (fdf->map->width / fdf->map->cols);
	a.y = a.y * (fdf->map->height / fdf->map->rows);
	b.x = b.x * (fdf->map->width / fdf->map->cols);
	b.y = b.y * (fdf->map->height / fdf->map->rows);
	fdf->map->x_offset = WINDOW_WIDTH * 2 / 5;
	fdf->map->y_offset = WINDOW_HEIGHT * 1 / 5;
	isometric(&a.x, &a.y, a.z);
	isometric(&b.x, &b.y, b.z);
	a.x += fdf->map->x_offset;
	a.y += fdf->map->y_offset;
	b.x += fdf->map->x_offset;
	b.y += fdf->map->y_offset;
	bresenham(a, b, fdf);
}

void	print_fdf(t_data *fdf)
{
	int	x;
	int	y;
	y = 0;
	while (y < fdf->map->cols)
	{
		x = 0;
		while (x < fdf->map->rows)
		{
			if (x < fdf->map->rows - 1)
			{
				printf("\n %i \n", x);
				draw_lines(fdf, fdf->points[x][y], fdf->points[x + 1][y]);
				printf(" 4444 \n");
			}
			if (y < fdf->map->cols - 1)
			{
				printf("\n %i \n", y);
				draw_lines(fdf, fdf->points[x][y], fdf->points[x][y + 1]);
				printf(" 6666 \n");
			}
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(fdf->mlx.mlx, fdf->mlx.win, fdf->mlx.img, 0, 0);
}
