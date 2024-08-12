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

void    draw_line(t_data *img)
{
	t_draw draw;

	draw.dx = fabs(img->cur_x - img->last_x);
	draw.dy = fabs(img->cur_y - img->last_y);
	draw.sx = (img->last_x < img->cur_x) ? 1 : -1;
	draw.sy = (img->last_y < img->cur_y) ? 1 : -1;
	draw.d1 = (draw.dx - draw.dy);
	draw.x = img->last_x;
	draw.y = img->last_y;
	while (draw.x < img->cur_x)
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

void	print_fdf(t_data *img)
{
	int	i;
	int	j;


	ft_bzero(img->addr, WINDOW_WIDTH * WINDOW_HEIGHT * (img->bits_per_pixel / 8));
	j = 0;
	i = 0;
	//img->pos_y = MIDDLE_HEIGHT - (WINDOW_HEIGHT * img->zoom / 2) + (WINDOW_HEIGHT * img->zoom / (2 * img->rows));		//Razao de 1/10
	//img->pos_x = MIDDLE_WIDTH - (WINDOW_WIDTH * img->zoom / 2) + (WINDOW_WIDTH * img->zoom / (2 * img->col));			//Razao de 2/5
	//img->pos_y = WINDOW_HEIGHT / img->zoom / img->rows;
	//img->pos_x = WINDOW_WIDTH / img->zoom / img->col;
	img->pos_y = WINDOW_HEIGHT / 10;
	img->pos_x = WINDOW_WIDTH / 5 * 2.5;
	//isometric(&img->pos_x, &img->pos_y, img->points[j][i]);
	while (j < img->rows)
	{
		i = 0;
		while (i < img->col)
		{
			img->last_x = img->pos_x + (i * (img->width_x / img->col));
			img->last_y = img->pos_y + (j * (img->height_y / img->rows));
			img->last_z = img->points[j][i];
			if (i < img->col - 1)
			{
				img->cur_x = img->pos_x + (i + 1) * (img->width_x / img->col);
				img->cur_y = img->last_y;
				img->cur_z = img->points[j][i+1];
				isometric(&img->last_x, &img->last_y, img->last_z);
				isometric(&img->cur_x, &img->cur_y, img->cur_z);
				draw_line(img);
			}
			
/* 			if (j < img->rows - 1)
			{
				img->cur_x = img->last_x;
				img->cur_y = img->pos_y + (j + 1) * (img->height_y / img->rows);
				img->cur_z = img->points[j+1][i];
				isometric(&img->last_x, &img->last_y, img->last_z);
				isometric(&img->cur_x, &img->cur_y, img->cur_z);
				draw_line(img);
			} */
			i++;
		}
		j++;
	}
	mlx_put_image_to_window(img->mlx, img->win, img->img, 0, 0);
	printf("pos_y= %f\n", img->pos_y);				//Apagar
	printf("pos_x= %f\n", img->pos_x);				//Apagar
	printf("rows= %f\n", img->rows);				//Apagar
	printf("cols= %f\n", img->col);					//Apagar
	printf("pos_final_y= %f\n", img->cur_y);		//Apagar
	printf("pos_final_x= %f\n", img->cur_x);		//Apagar
	printf("height_y= %f\n", img->height_y);		//Apagar
	printf("width_x= %f\n", img->width_x);			//Apagar
	printf("zoom= %f\n", img->zoom);				//Apagar
}




/*

void    draw_line(t_data *img)
{
	double dx = fabs(img->cur_x - img->last_x);
	double dy = fabs(img->cur_y - img->last_y);
	double sx = (img->last_x < img->cur_x) ? 1 : -1;
	double sy = (img->last_y < img->cur_y) ? 1 : -1;
	double err = dx - dy;

	while (img->last_x <= img->cur_x)
	{
		my_mlx_pixel_put(img, img->last_x, img->last_y, WHITE_PIXEL);
		double e2 = 2 * err;
		if (e2 > -dy)
		{
			err -= dy;
			img->last_x += sx;
		}
		if (e2 < dx)
		{
			err += dx;
			img->last_y += sy;
		}
	}
}

void    print_fdf(t_data *img)
{
	int			i;
	int			j;


	ft_bzero(img->addr, WINDOW_WIDTH * WINDOW_HEIGHT * (img->bits_per_pixel / 8));
	j = 0;
	i = 0;
	img->pos_y = MIDDLE_HEIGHT - (WINDOW_HEIGHT * img->zoom / 2) + (WINDOW_HEIGHT * img->zoom / (2 * img->rows));
	img->pos_x = MIDDLE_WIDTH - (WINDOW_WIDTH * img->zoom / 2) + (WINDOW_WIDTH * img->zoom / (2 * img->col));
	img->cur_y = img->pos_y;
	while (j < img->rows)	
	{
		i = 0;
		while (i < img->col)
		{
			img->last_x = img->pos_x + i * (img->width_x / img->col);
			img->last_y = img->pos_y + j * (img->height_y / img->rows);
			img->last_z = img->points[j][i];
			if (i < img->col - 1)
			{
				img->cur_x = img->pos_x + (i + 1) * (img->width_x / img->col);
				img->cur_y = img->last_y;
				img->cur_z = img->points[j][i+1];
				isometric(&img->last_x, &img->last_y, img->last_z);
				isometric(&img->cur_x, &img->cur_y, img->cur_z);
				draw_line(img);
			}
			
			if (j < img->rows - 1)
			{
				img->cur_x = img->last_x;
				img->cur_y = img->pos_y + (j + 1) * (img->height_y / img->rows);
				img->cur_z = img->points[j+1][i];
				isometric(&img->last_x, &img->last_y, img->last_z);
				isometric(&img->cur_x, &img->cur_y, img->cur_z);
				draw_line(img);
			}
			i++;
		}
		j++;
	}
	mlx_put_image_to_window(img->mlx, img->win, img->img, 0, 0);
}

void    draw_lines(t_data *img)	
{
	double	x;
	double	y;
	double	x1;
	double	y1;

	y = img->last_y;
	printf("A");
	while (y <= img->cur_y)
	{
		x = img->last_x;
		while (x <= img->cur_x)
		{
			y1 = y;
			x1 = x;
			//isometric(&x1, &y1, img->cur_z);
			my_mlx_pixel_put(img, x1, img->last_y, WHITE_PIXEL);
			x++;
		}
		my_mlx_pixel_put(img, img->last_x, y1, WHITE_PIXEL);
		y++;
	}
}

void    print_fdf(t_data *img)
{
	int			i;
	int			j;

	ft_bzero(img->addr, WINDOW_WIDTH * WINDOW_HEIGHT * (img->bits_per_pixel / 8));
	j = 0;
	i = 0;
	img->pos_y = MIDDLE_HEIGHT - (WINDOW_HEIGHT * img->zoom / 2) + (WINDOW_HEIGHT * img->zoom / (2 * img->rows));
	img->pos_x = MIDDLE_WIDTH - (WINDOW_WIDTH * img->zoom / 2) + (WINDOW_WIDTH * img->zoom / (2 * img->col));
	img->cur_y = img->pos_y;
	while (j < img->rows)	
	{
		i = 0;
		img->cur_x = img->pos_x;
		img->last_y = img->cur_y;
		if (j < img->rows - 1)
			img->cur_y += (img->height_y / img->rows);
		
		while (i < img->col)
		{
			img->cur_z = img->points[j][i];
			img->last_x = img->cur_x;
			if (i < img->col - 1)
				img->cur_x += (img->width_x / img->col);
			
			if (img->last_x != 0 && img->last_y != 0)
			{
				//isometric(&img->last_x, &img->last_y, img->cur_z);
				//isometric(&img->cur_x, &img->cur_y, img->cur_z);
				draw_lines(img);
			}
			my_mlx_pixel_put(img, img->last_x+2, 36, RED_PIXEL);	//Apagar depois de finalizado
			i++;
		}
		j++;
	}
	mlx_put_image_to_window(img->mlx, img->win, img->img, 0, 0);



	printf("pos_y= %f\n", img->pos_y);				//Apagar
	printf("pos_x= %f\n", img->pos_x);				//Apagar
	printf("rows= %f\n", img->rows);				//Apagar
	printf("cols= %f\n", img->col);					//Apagar
	printf("pos_final_y= %f\n", img->cur_y);		//Apagar
	printf("pos_final_x= %f\n", img->cur_x);		//Apagar
	printf("height_y= %f\n", img->height_y);		//Apagar
	printf("width_x= %f\n", img->width_x);			//Apagar
	printf("zoom= %f\n", img->zoom);				//Apagar
}

*/