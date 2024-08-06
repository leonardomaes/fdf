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

// KEYBOARD COMMANDS
int	check_key(int keysym, t_data *img)
{
	if (keysym == ESC)
	{
		kill_all(img);
		write(1, "\nClosed\n", 8);
		exit (1);
	}
	return (0);
}

// MOUSE COMMANDS
int	mouse_hook(int keysym, t_data *img)		//BONUS
{
	if (keysym == 4 && img->zoom < 1.0)	// Zoom in
		img->zoom += img->zoom/10;
	else if (keysym == 5)	//zoom out
		img->zoom -= img->zoom/10;
	return (0);
}
