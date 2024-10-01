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

void free_points(t_data *fdf)
{
	int i;

	i = 0;
	while (i < fdf->map->rows)
	{
		free(fdf->points[i]);
		i++;
	}
	free(fdf->points);
}

void free_split(char **data)
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

void	clear_all(t_data *data)
{
	if (!data)
		return ;
	mlx_destroy_image(data->mlx.mlx, data->mlx.img);
	if (data->mlx.win)
		mlx_destroy_window(data->mlx.mlx, data->mlx.win);
	if (data->mlx.mlx)
		mlx_destroy_display(data->mlx.mlx);
	free(data->map);
	free(data);
}

int	kill_all(t_data *data)
{
	clear_all(data);
	write(1, "\nClosed\n", 8);
	exit (1);
	return (0);
}
