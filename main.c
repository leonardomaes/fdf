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
	char	*title;
	
	fdf = (t_data *)malloc(sizeof(t_data));
	if (!fdf)
		exit(1);
	fdf->mlx.mlx = mlx_init();
	if (!fdf->mlx.mlx)
		exit(1);
	fdf->filename = (char *)path;
	title = ft_strjoin("FDF - ", path);
	fdf->mlx.win = mlx_new_window(fdf->mlx.mlx, WINDOW_WIDTH, WINDOW_HEIGHT, title);
	free(title);
	fdf->mlx.img = mlx_new_image(fdf->mlx.mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	fdf->mlx.addr = mlx_get_data_addr(fdf->mlx.img, &fdf->mlx.bits_per_pixel, &fdf->mlx.line_length, &fdf->mlx.endian);
	return (fdf);	
}

int main(int argc, char *argv[])
{
	t_data *fdf;

	if (argc == 2)
	{
		fdf = init_win(argv[1]);
		if (file_check(fdf) == 1)
			return (1);
		printf("\n AAA \n");
		var_init(fdf);
		print_fdf(fdf);
		printf("\n ZZZ \n");
		setup_hook(fdf);
		mlx_loop(fdf->mlx.mlx);
	}
	else
	{
		ft_printf("ERROR:\nWrong number of arguments!\n");
		exit(1);
	}
	clear_all(fdf);
	return (0);
}
