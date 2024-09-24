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

	draw.dx = fabs(img->draw.cur_x - img->draw.last_x);
	draw.dy = fabs(img->draw.cur_y - img->draw.last_y);
	draw.sx = (img->draw.last_x < img->draw.cur_x) ? 1 : -1;
	draw.sy = (img->draw.last_y < img->draw.cur_y) ? 1 : -1;
	draw.d1 = (draw.dx - draw.dy);
	draw.x = img->draw.last_x;
	draw.y = img->draw.last_y;
	if (flag == 1)
	{
		while (draw.x <= img->draw.cur_x)
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
		while (draw.y <= img->draw.cur_y)
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
			x = i * (img->draw.width_x / img->col);
			y = j * (img->draw.height_y / img->rows);
			isometric(&x, &y, img->points[j][i]);
			if (x < min_x) min_x = x;
			if (y < min_y) min_y = y;
			if (x > max_x) max_x = x;
			if (y > max_y) max_y = y;
			i++;
		}
		
		j++;
	}
	img->draw.pos_x = (WINDOW_WIDTH - (max_x - min_x)) / 2 - min_x;
	img->draw.pos_y = (WINDOW_HEIGHT - (max_y - min_y)) / 2 - min_y;
}

void	print_fdf(t_data *img)		// Arrumar
{
	int	i;
	int	j;
	double	lx;
	double	ly;


	ft_bzero(img->image.addr, WINDOW_WIDTH * WINDOW_HEIGHT * (img->image.bits_per_pixel / 8));
	calculate_offsets(img);
	j = 0;
	while (j < img->rows)
	{
		i = 0;
		while (i < img->col)
		{
			img->draw.last_x = (i * (img->draw.width_x / img->col));
			img->draw.last_y = (j * (img->draw.height_y / img->rows));
			lx = img->draw.last_x;
			ly = img->draw.last_y;
			img->draw.last_z = img->points[j][i];		// J sao os rows e I as cols
			isometric(&img->draw.last_x, &img->draw.last_y, img->draw.last_z);
			img->draw.last_x += img->draw.pos_x;
			img->draw.last_y += img->draw.pos_y;

			if (i < img->col - 1)
			{
				img->draw.cur_x =(i + 1) * (img->draw.width_x / img->col);
				img->draw.cur_y = ly;
				img->draw.cur_z = img->points[j][i+1];
				isometric(&img->draw.cur_x, &img->draw.cur_y, img->draw.cur_z);
				img->draw.cur_x += img->draw.pos_x;
				img->draw.cur_y += img->draw.pos_y;
				draw_line(img, 1);
			}
			
  			if (j < img->rows - 1)
			{
				img->draw.cur_x = lx;
				img->draw.cur_y =(j + 1) * (img->draw.height_y / img->rows);
				img->draw.cur_z = img->points[j+1][i];
				isometric(&img->draw.cur_x, &img->draw.cur_y, img->draw.cur_z);
				img->draw.cur_x += img->draw.pos_x;
				img->draw.cur_y += img->draw.pos_y;
				draw_line(img, 2);
			}
			i++;
		}
		j++;
	}
	mlx_put_image_to_window(img->mlx, img->win, img->image.img, 0, 0);
	printf("pos_y= %f\n", img->draw.pos_y);				//Apagar
	printf("pos_x= %f\n", img->draw.pos_x);				//Apagar
	printf("rows= %f\n", img->rows);				//Apagar
	printf("cols= %f\n", img->col);					//Apagar
	printf("pos_final_y= %f\n", img->draw.cur_y);		//Apagar
	printf("pos_final_x= %f\n", img->draw.cur_x);		//Apagar
	printf("height_y= %f\n", img->draw.height_y);		//Apagar
	printf("width_x= %f\n", img->draw.width_x);			//Apagar
	printf("zoom= %f\n", img->draw.zoom);				//Apagar
}