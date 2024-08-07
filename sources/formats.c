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

void    draw_lines(t_data *img)	
{
	double	x;
	double	y;
	
	y = img->last_y;
	while (y <= img->cur_y)
	{
		x = img->last_x;
		while (x <= img->cur_x)
		{
			my_mlx_pixel_put(img, x, img->last_y, WHITE_PIXEL);
			x++;
		}
		my_mlx_pixel_put(img, img->last_x, y, WHITE_PIXEL);
		y++;
	}
}

void    print_fdf(t_data *img)
{
	int			i;
	int			j;

	j = 0;
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
			img->last_x = img->cur_x;
			if (i < img->col - 1)
				img->cur_x += (img->width_x / img->col);
			if (img->last_x != 0 && img->last_y != 0)
				draw_lines(img);
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