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

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	render(t_data *data)
{
    if (data->win != NULL)
        mlx_pixel_put(data->win, data->win, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2, GREEN_PIXEL);
    return (0);
}
// KEYBOARD COMMANDS

int	check_key(int keysym, t_data *data)
{
	if (keysym == ESC)
	{
		mlx_destroy_window(data->mlx, data->win);
		data->win = NULL;
		write(1, "Closed\n", 7);
	}
	else if (keysym == XK_Up || keysym == XK_w)
	{
		data->y -= 10;
		my_mlx_pixel_put(data, data->x, data->y, GREEN_PIXEL);
		write(1, "w\n", 2);
	}
	else if (keysym == XK_Down || keysym == XK_s)
	{
		data->y += 10;
		my_mlx_pixel_put(data, data->x, data->y, RED_PIXEL);
		write(1, "s\n", 2);
	}
	else if (keysym == XK_Left || keysym == XK_a)
	{
		data->x -= 10;
		my_mlx_pixel_put(data, data->x, data->y, GREEN_PIXEL);
		write(1, "a\n", 2);
	}
	else if (keysym == XK_Right || keysym == XK_d)
	{
		data->x += 10;
		my_mlx_pixel_put(data, data->x, data->y, GREEN_PIXEL);
		write(1, "d\n", 2);
	}
	return (0);
}


// MOUSE COMMANDS
