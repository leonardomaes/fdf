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

int	is_key(int	key)
{
	return (key == XK_Up || key == XK_Down || key == XK_Left || key == XK_Right \
			|| key == XK_r || key == XK_Shift_L || key == XK_Control_L\
			 || key == XK_w || key == XK_s || key == XK_a || key == XK_d\
			 || key == XK_q || key == XK_e || key == XK_1 || key == XK_2\
			  || key == XK_3);
}

void	do_key(int keysym, t_data *fdf)
{
	if (keysym == XK_Up)
	{
		if (fdf->map->cols > 70)
			fdf->map->y_offset -= 30;
		else
			fdf->map->y_offset -= 10;
	}
	if (keysym == XK_Down)
	{
		if (fdf->map->cols > 70)
			fdf->map->y_offset += 30;
		else
			fdf->map->y_offset += 10;
	}
	if (keysym == XK_Left)
	{
		if (fdf->map->cols > 70)
		{
			fdf->map->x_offset -= 30;
		}
		else
			fdf->map->x_offset -= 10;
	}
	if (keysym == XK_Right)
	{
		if (fdf->map->cols > 70)
		{
			fdf->map->x_offset += 30;
		}
		else
			fdf->map->x_offset += 10;
	}
	if (keysym == XK_Control_L && fdf->map->zoom > 0.2)
		fdf->map->zoom -= 0.1;
	if (keysym == XK_Shift_L)
		fdf->map->zoom += 0.1;
	if (keysym == XK_w)
	{
		apply_size(fdf, 1);
	}
	if (keysym == XK_s)
	{
		apply_size(fdf, -1);
	}
	if (keysym == XK_e)
		fdf->map->angle += 5;
	if (keysym == XK_q)
		fdf->map->angle -= 5;
	if (keysym == XK_a)
		get_next_color(fdf, -1);
	if (keysym == XK_d)
		get_next_color(fdf, 1);
	
	if (keysym == XK_1)
		apply_rotate(fdf, 1);
	if (keysym == XK_2)
		apply_rotate(fdf, 2);
	if (keysym == XK_3)
		apply_rotate(fdf, 2);
	
	if (keysym == XK_r)
		var_init(fdf);
}

// KEYBOARD COMMANDS
int	check_key(int keysym, t_data *fdf)
{
	if (is_key(keysym))
	{
		mlx_clear_window(fdf->mlx.mlx, fdf->mlx.win);
		do_key(keysym, fdf);
		print_fdf(fdf);
	}
	if (keysym == XK_Escape)
	{
		kill_all(fdf);
	}
	return (0);
}
