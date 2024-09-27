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

void	draw_horizontal(t_data *img, int x, int y)
{
	img->draw.cur_x = (x + 1) * (img->draw.width_x / img->col);
	img->draw.cur_y = img->draw.ly;
	img->draw.cur_z = img->points[y][x + 1];
	isometric(&img->draw.cur_x, &img->draw.cur_y, img->draw.cur_z);
	img->draw.cur_x += img->draw.pos_x;
	img->draw.cur_y += img->draw.pos_y;
	draw_line(img, 1);
}

void	draw_vertical(t_data *img, int x, int y)
{
	img->draw.cur_x = img->draw.lx;
	img->draw.cur_y = (y + 1) * (img->draw.height_y / img->rows);
	img->draw.cur_z = img->points[y + 1][x];
	isometric(&img->draw.cur_x, &img->draw.cur_y, img->draw.cur_z);
	img->draw.cur_x += img->draw.pos_x;
	img->draw.cur_y += img->draw.pos_y;
	draw_line(img, 2);
}

void print_fdf(t_data	*img)
{
	int	x;
	int	y;

	calculate_offsets(img);		// Pega a pos inicial do x e y
	y = 0;
	while (y < img->rows)
	{
		x = 0;
		while (x < img->col)
		{
			img->draw.last_x = (x * (img->draw.width_x / img->col));
			img->draw.last_y = (y * (img->draw.height_y / img->rows));
			img->draw.lx = img->draw.last_x;
			img->draw.ly = img->draw.last_y;
			img->draw.last_z = img->points[y][x];
			isometric(&img->draw.last_x, &img->draw.last_y, img->draw.last_z);
			img->draw.last_x += img->draw.pos_x;
			img->draw.last_y += img->draw.pos_y;
			if (x < img->col - 1)
			{
				draw_horizontal(img, x, y);
			}
			if (y < img->rows - 1)
			{
				draw_vertical(img, x, y);
			}
			x++;
		}
		y++;
	}
	mlx_put_image_to_window(img->mlx, img->win, img->image.img, 0, 0);
}


/* void	print_fdf(t_data *img)		// Arrumar
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
			img->draw.last_z = img->points[j][i];
			isometric(&img->draw.last_x, &img->draw.last_y, img->draw.last_z);
			img->draw.last_x += img->draw.pos_x;		// pos_x = Posicao inicial ja com isometrico aplicado
			img->draw.last_y += img->draw.pos_y;
			if (i < img->col - 1)			// Desenhar coluna (vertical)
			{
				//printf("\ni%i -", i);
				img->draw.cur_x =(i + 1) * (img->draw.width_x / img->col);
				img->draw.cur_y = ly;
				img->draw.cur_z = img->points[j][i+1];
				isometric(&img->draw.cur_x, &img->draw.cur_y, img->draw.cur_z);
				img->draw.cur_x += img->draw.pos_x;
				img->draw.cur_y += img->draw.pos_y;
				draw_line(img, 1);
			}
  			if (j < img->rows - 1)			// Desenhar linha (horizontal)
			{
				//printf(" j%i\n", j);
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
} */
