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

t_data	*init_win(const char *path)
{
	t_data	*fdf;
	fdf = (t_data *)malloc(sizeof(t_data));
	if (!fdf)
		exit(1);
	fdf->mlx = mlx_init();
	if (!fdf->mlx)
		exit(1);
	fdf->win = mlx_new_window(fdf->mlx, WINDOW_WIDTH, WINDOW_HEIGHT, ft_strjoin("FDF - ", path));
	fdf->image.img = mlx_new_image(fdf->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	fdf->image.addr = mlx_get_data_addr(fdf->image.img, &fdf->image.bits_per_pixel, &fdf->image.line_length, &fdf->image.endian);
	return (fdf);	
}

int main(int argc, char *argv[])
{
    t_data *img;
	char	*filename;
	
	if (argc == 2)
		filename = argv[1];
	else
	{
		file_error(1);
		exit(1);
	}
	img = init_win(argv[1]);
	var_init(img, filename);
	printf("\n\nA\n\n");

	if (file_check(img) == 0)
		exit(1);
	printf("\n");
 	for (size_t i = 0; i < img->rows; i++)	//Apagar
	{
		for (size_t j = 0; j < img->col; j++)
		{
			printf("%i ", (int)img->points[i][j]);
		}
		printf("\n");
	}



	setup_hook(img);
	print_fdf(img);
	mlx_loop(img->mlx);

	clear_all(img);
	return (0);
}
