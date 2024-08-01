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

/* void    print_fdf(t_data *img)
{
	int     i;
	int     j;
	double     x;
	double     y;

	j = 0;
	img->pos_y = MIDDLE_HEIGHT - (((MIDDLE_HEIGHT / (img->rows / 2)) * img->zoom) * (img->rows / 2));
	img->pos_x = MIDDLE_WIDTH - (((MIDDLE_WIDTH / (img->col / 2)) * img->zoom) * (img->col / 2));
	y = img->pos_y;
	printf("pos_y= %f\n", img->pos_y);		//Apagar
	printf("pos_x= %f\n", img->pos_x);		//Apagar
	printf("y1= %f\n", img->rows);		//Apagar
	printf("y1= %f\n", img->col);		//Apagar
	while (j < img->rows)
	{
		i = 0;
		x = img->pos_x;
		while (i < img->col)
		{
			my_mlx_pixel_put(img, x, y, WHITE_PIXEL);   
			x += (img->width_x / img->col);
			i++;
		}
		y += (img->height_y / img->rows);
		j++;
	}
	printf("pos_final_y= %f\n", y);		//Apagar
	printf("pos_final_x= %f\n", x);		//Apagar
} */

void    draw_lines(t_data *img)
{
	double	i;
	double	j;

	i = img->last_x;
	while (i <= img->cur_x)
	{
		j = img->last_y;
		while (j <= (img->last_y + (img->height_y / img->rows)))
		{
			if(i == img->last_x)
				my_mlx_pixel_put(img, img->last_x, j, WHITE_PIXEL);
			else
				my_mlx_pixel_put(img, img->cur_x, j, WHITE_PIXEL);
			printf("1");
			j++;
		}
/* 		if (img->last_y == img->cur_y)
			my_mlx_pixel_put(img, i, j, WHITE_PIXEL);
		else */
			my_mlx_pixel_put(img, i, img->cur_y, WHITE_PIXEL);
		printf("2\n");
		i++;
	}
}

void    print_fdf(t_data *img)
{
	int			i;
	int			j;

	j = 0;
	img->pos_y = MIDDLE_HEIGHT - (((MIDDLE_HEIGHT / (img->rows / 2)) * img->zoom) * (img->rows / 2));
	img->pos_x = MIDDLE_WIDTH - (((MIDDLE_WIDTH / (img->col / 2)) * img->zoom) * (img->col / 2));
	img->cur_y = img->pos_y;
	printf("pos_y= %f\n", img->pos_y);		//Apagar
	printf("pos_x= %f\n", img->pos_x);		//Apagar
	printf("y1= %f\n", img->rows);			//Apagar
	printf("y1= %f\n", img->col);			//Apagar
	while (j < img->rows)
	{
		i = 0;
		img->cur_x = img->pos_x;
		img->last_y = img->cur_y;
		while (i < img->col)
		{
			my_mlx_pixel_put(img, img->cur_x, img->cur_y, WHITE_PIXEL);	//Apagar depois de finalizado
			img->last_x = img->cur_x;
			img->cur_x += (img->width_x / img->col);
			i++;
			if (img->last_x != 0 && img->last_y != 0)
				draw_lines(img);
			
		}
		printf("\n");
		img->cur_y += (img->height_y / img->rows);
		j++;
	}
	printf("pos_final_y= %f\n", img->cur_y);		//Apagar
	printf("pos_final_x= %f\n", img->cur_x);		//Apagar
	printf("height_y= %f\n", img->height_y);		//Apagar
	printf("width_x= %f\n", img->width_x);			//Apagar
}