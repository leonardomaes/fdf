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
	img->x = 480;
	img->y = 270;
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

int main(void)
{
    t_data img;
	char	*filename = "42.fdf";
	
	img.fd = open(filename, O_RDONLY);
	if (img.fd < 0)
	{
		file_error(1);
		return (0);
	}
	if (file_check(&img) == 0)
		exit(1);
	ft_printf("%i\n", img.rows); 		// APAGAR
	if(init_win(&img) == 0)
		return (0);
	print_fdf(&img);








	//print_square(&img, 320, 400);
	//print_triangle(&img, 10, 400);
	//print_hexagon(&img, 630, 400);
	//print_line(&img);
	//draw_screen(&img);

	mlx_put_image_to_window(img.mlx, img.win, img.img, 0, 0);
	
	//mlx_key_hook(img.win, handle_keypress, &img);
	//mlx_key_hook(img.win, check_key, &img);
	//						OU
    //mlx_loop_hook(img.win, &render, &img);
    mlx_hook(img.win, KeyPress, KeyPressMask, &check_key, &img);
	
	mlx_loop(img.mlx);

    mlx_destroy_display(img.mlx);
    free(img.mlx);

	return (0);
}
