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

#include "../includes/fdf.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->mlx.addr + (y * data->mlx.line_length + x
			* (data->mlx.bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

void	var_init(t_data *fdf)
{
	fdf->map->zoom = 0.50;
	fdf->map->size = 0;
	fdf->map->x_offset = WINDOW_WIDTH * 2 / 5;
	fdf->map->y_offset = WINDOW_HEIGHT * 1 / 5;
	fdf->map->angle = 30;
}

double	get_radian(int angle)
{
	double	radian;

	radian = angle * (PI / 180);
	return (radian);
}

int	check_key(int keysym, t_data *fdf)
{
	if (keysym == XK_Escape)
	{
		kill_all(fdf);
	}
	return (0);
}
