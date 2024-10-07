/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmaes <lmaes@student.42porto.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/30 02:30:08 by lmaes             #+#    #+#             */
/*   Updated: 2024/09/30 02:35:11 by lmaes            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	free_points(t_data *fdf)
{
	int	i;

	i = 0;
	while (i < fdf->map->rows)
	{
		free(fdf->points[i]);
		i++;
	}
	free(fdf->points);
}

void	free_split(char **data)
{
	int	i;

	i = 0;
	while (data[i])
	{
		free(data[i]);
		i++;
	}
	free(data);
}

void	clear_all(t_data *fdf)
{
	if (!fdf)
		return ;
	mlx_clear_window(fdf->mlx.mlx, fdf->mlx.win);
	mlx_destroy_image(fdf->mlx.mlx, fdf->mlx.img);
	if (fdf->mlx.win)
		mlx_destroy_window(fdf->mlx.mlx, fdf->mlx.win);
	if (fdf->mlx.mlx)
		mlx_destroy_display(fdf->mlx.mlx);
	free(fdf->mlx.mlx);
	free(fdf->map);
	free(fdf);
}

int	kill_all(t_data *fdf)
{
	free_points(fdf);
	clear_all(fdf);
	write(1, "\nClosed\n", 8);
	exit(1);
	return (0);
}
