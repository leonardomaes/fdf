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

void    draw_line(t_data *img, int flag)
{
	t_draw draw;

	draw.dx = fabs(img->cur_x - img->last_x);
	draw.dy = fabs(img->cur_y - img->last_y);
	draw.sx = (img->last_x < img->cur_x) ? 1 : -1;
	draw.sy = (img->last_y < img->cur_y) ? 1 : -1;
	draw.d1 = (draw.dx - draw.dy);
	draw.x = img->last_x;
	draw.y = img->last_y;
	if (flag == 1)
	{
		while (draw.x <= img->cur_x)
		{
			my_mlx_pixel_put(img, draw.x, draw.y, WHITE_PIXEL);
			draw.d2 = 2 * draw.d1;
			if (draw.d2 > -draw.dy)
			{
				draw.d1 -= draw.dy;
				draw.x += draw.sx;
			}
			if(draw.d2 < draw.dx)
			{
				draw.d1 += draw.dx;
				draw.y += draw.sy;
			}
		}
	}else if (flag == 2)
	{
		while (draw.y <= img->cur_y)
		{
			my_mlx_pixel_put(img, draw.x, draw.y, WHITE_PIXEL);
			draw.d2 = 2 * draw.d1;
			if (draw.d2 > -draw.dy)
			{
				draw.d1 -= draw.dy;
				draw.x += draw.sx;
			}
			if(draw.d2 < draw.dx)
			{
				draw.d1 += draw.dx;
				draw.y += draw.sy;
			}
		}
	}
}

void    calculate_offsets(t_data *img)
{
	double min_x;
	double min_y;
	double max_x;
	double max_y;
	double	x;
	double	y;
	int i;
	int	j;

	min_x = WINDOW_WIDTH;
	min_y = WINDOW_HEIGHT;
	max_x = 0;
	max_y = 0;
	j = 0;
	while (j < img->rows)
	{
		i = 0;
		while (i < img->col)
		{
			x = i * (img->width_x / img->col);
			y = j * (img->height_y / img->rows);
			isometric(&x, &y, img->points[j][i]);
			if (x < min_x) min_x = x;
			if (y < min_y) min_y = y;
			if (x > max_x) max_x = x;
			if (y > max_y) max_y = y;
			i++;
		}
		
		j++;
	}
	img->pos_x = (WINDOW_WIDTH - (max_x - min_x)) / 2 - min_x;
	img->pos_y = (WINDOW_HEIGHT - (max_y - min_y)) / 2 - min_y;
}

void	print_fdf(t_data *img)
{
	int	i;
	int	j;
	double	lx;
	double	ly;


	ft_bzero(img->addr, WINDOW_WIDTH * WINDOW_HEIGHT * (img->bits_per_pixel / 8));
	calculate_offsets(img);
	j = 0;
	while (j < img->rows)
	{
		i = 0;
		while (i < img->col)
		{
			img->last_x = (i * (img->width_x / img->col));
			img->last_y = (j * (img->height_y / img->rows));
			lx = img->last_x;
			ly = img->last_y;
			img->last_z = img->points[j][i];
			isometric(&img->last_x, &img->last_y, img->last_z);
			img->last_x += img->pos_x;
			img->last_y += img->pos_y;

			if (i < img->col - 1)
			{
				img->cur_x =(i + 1) * (img->width_x / img->col);
				img->cur_y = ly;
				img->cur_z = img->points[j][i+1];
				isometric(&img->cur_x, &img->cur_y, img->cur_z);
				img->cur_x += img->pos_x;
				img->cur_y += img->pos_y;
				draw_line(img, 1);
			}
			
  			if (j < img->rows - 1)
			{
				img->cur_x = lx;
				img->cur_y =(j + 1) * (img->height_y / img->rows);
				img->cur_z = img->points[j+1][i];
				isometric(&img->cur_x, &img->cur_y, img->cur_z);
				img->cur_x += img->pos_x;
				img->cur_y += img->pos_y;
				draw_line(img, 2);
			}
			i++;
		}
		j++;
	}
	mlx_put_image_to_window(img->mlx, img->win, img->img, 0, 0);
}