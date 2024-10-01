/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmaes <lmaes@student.42porto.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/12 12:13:11 by lmaes             #+#    #+#             */
/*   Updated: 2024/07/12 12:13:12 by lmaes            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void	my_mlx_pixel_put(t_data *data, int x, int y, int color)
{
	char	*dst;

	dst = data->mlx.addr + (y * data->mlx.line_length + x * (data->mlx.bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

// KEYBOARD COMMANDS
int	check_key(int keysym, t_data *img)
{
	if (keysym == ESC)
	{
		kill_all(img);
	}
	return (0);
}

void	setup_hook(t_data *img)
{
	mlx_hook(img->mlx.win, KeyPress, KeyPressMask, &check_key, img);
	mlx_hook(img->mlx.win, DestroyNotify, 0, &kill_all, img);
}