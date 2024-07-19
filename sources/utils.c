/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmaes <lmaes@student.42porto.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 12:49:53 by lmaes             #+#    #+#             */
/*   Updated: 2024/07/18 12:49:53 by lmaes            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	var_init(t_data *img)
{
	img->col = 0;
	img->rows = 0;
	img->zoom = 0.65;
	img->x = WINDOW_WIDTH * img->zoom;
	img->y = WINDOW_HEIGHT * img->zoom;
}

int	kill_all(t_data *data)
{
	clear_all(data);
	write(1, "\nClosed\n", 8);
	exit (1);
	return (0);
}

void	clear_all(t_data *data)
{
	if (!data)
		return ;
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx)
		mlx_destroy_display(data->mlx);
	free(data->mlx);
}