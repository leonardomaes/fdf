/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmaes <lmaes@student.42porto.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 12:52:08 by lmaes             #+#    #+#             */
/*   Updated: 2024/07/11 12:52:10 by lmaes            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <X11/X.h>
#include "fdf.h"

int	init_win(t_data *img)
{
	img->mlx = mlx_init();
	if (img->mlx == NULL)
	{
		mlx_destroy_display(img->mlx);
		return (0);
	}
	img->win = mlx_new_window(img->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, "FDF");
	if (img->win == NULL)
	{
		free (img->mlx);
		return (0);
	}
	img->img = mlx_new_image(img->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	img->addr = mlx_get_data_addr(img->img, &img->bits_per_pixel, &img->line_length, &img->endian);

	return (1);	
}

void	setup_hook(t_data *img)
{
	mlx_hook(img->win, KeyPress, KeyPressMask, &check_key, img);
	mlx_mouse_hook(img->win, mouse_hook, img);		// Continua daqui
	mlx_hook(img->win, DestroyNotify, 0, &kill_all, img);
	mlx_loop(img->mlx);
}

int main(int argv, char *argc[])
{
    t_data img;
	char	*filename;
	
	if (argv == 2)
		filename = argc[1];
	else
	{
		file_error(1);
		exit(1);
	}
	var_init(&img, filename);
	if (file_check(&img) == 0)
		exit(1);
	if(init_win(&img) == 0)
		exit (1);
	if (number_check(&img) == 0)
        exit(1);

	for (size_t i = 0; i < img.rows; i++)	//Apagar
	{
		for (size_t j = 0; j < img.col; j++)
		{
			printf("%i ", (int)img.points[i][j]);
		}
		printf("\n");
		
	}
	print_fdf(&img);
	setup_hook(&img);
	clear_all(&img);
	return (0);
}
