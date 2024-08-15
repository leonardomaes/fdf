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
				draw.x+= draw.sx;
			}
			if(draw.d2 < draw.dx)
			{
				draw.d1 += draw.dx;
				draw.y+= draw.sy;
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
				draw.x+= draw.sx;
			}
			if(draw.d2 < draw.dx)
			{
				draw.d1 += draw.dx;
				draw.y+= draw.sy;
			}
		}
	}
	my_mlx_pixel_put(img, 400, 100, RED_PIXEL); //em cima
	my_mlx_pixel_put(img, 677, 670, RED_PIXEL); //em baixo
	my_mlx_pixel_put(img, 45, 306, RED_PIXEL); // Esquerda
	my_mlx_pixel_put(img, 1032, 465, RED_PIXEL); // Direita
}

void	print_fdf(t_data *img)
{
	int	i;
	int	j;
	double	lx;
	double	ly;


	ft_bzero(img->addr, WINDOW_WIDTH * WINDOW_HEIGHT * (img->bits_per_pixel / 8));
	img->pos_y = MIDDLE_HEIGHT - (WINDOW_HEIGHT * img->zoom / 2) + (WINDOW_HEIGHT * img->zoom / (2 * img->rows));		//Razao de 1/10
	img->pos_x = WINDOW_WIDTH / img->zoom / img->col;
	//img->pos_x = MIDDLE_WIDTH - (WINDOW_WIDTH * img->zoom / 2) + (WINDOW_WIDTH * img->zoom / (2 * img->col));			//Razao de 2/5
	//img->pos_y = WINDOW_HEIGHT / img->zoom / img->rows;
	//img->pos_x = WINDOW_WIDTH / img->zoom / img->col;
	//img->pos_y = WINDOW_HEIGHT / 100;
	//img->pos_x = WINDOW_WIDTH / 5 * 2.5;
	//img->pos_x = (WINDOW_WIDTH - img->width_x) / 2;
	//img->pos_y = (WINDOW_HEIGHT - img->height_y) / 2;
	//img->pos_x = 400;
	//img->pos_y = 100;
	//isometric(&img->pos_x, &img->pos_y, img->points[j][i]);
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