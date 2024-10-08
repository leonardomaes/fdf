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

int	is_key(int key)
{
	return (key == XK_Up || key == XK_Down || key == XK_Left || key == XK_Right
		|| key == XK_r || key == XK_Shift_L || key == XK_Control_L
		|| key == XK_w || key == XK_s || key == XK_a || key == XK_d
		|| key == XK_q || key == XK_e || key == XK_1 || key == XK_2
		|| key == XK_3 || key == XK_KP_Subtract || key == XK_KP_Add
		|| key == XK_z || key == XK_x);
}

void	do_key(int keysym, t_data *fdf)
{
	if (keysym == XK_KP_Subtract && fdf->map->zoom > 0.2)
		fdf->map->zoom -= 0.1;
	if (keysym == XK_KP_Add)
		fdf->map->zoom += 0.1;
	if (keysym == XK_e)
		fdf->map->angle += 5;
	if (keysym == XK_q)
		fdf->map->angle -= 5;
	if (keysym == XK_1)
	{
		var_init(fdf);
		fdf->map->view = 1;
		fdf->map->x_offset -= 200;
	}
	if (keysym == XK_2)
	{
		var_init(fdf);
		fdf->map->view = 2;
	}
	if (keysym == XK_r)
		var_init(fdf);
	move_keys(keysym, fdf);
	rotate_keys(keysym, fdf);
}

void	move_keys(int key, t_data *fdf)
{
	int	i;

	if (fdf->map->cols > 70 || fdf->map->zoom >= 0.9)
		i = 30;
	else
		i = 10;
	if (key == XK_Up)
		fdf->map->y_offset -= i;
	if (key == XK_Down)
		fdf->map->y_offset += i;
	if (key == XK_Left)
		fdf->map->x_offset -= i;
	if (key == XK_Right)
		fdf->map->x_offset += i;
	if (key == XK_Shift_L)
		apply_size(fdf, 1);
	if (key == XK_Control_L)
		apply_size(fdf, -1);
}

void	rotate_keys(int key, t_data *fdf)
{
	if (key == XK_s)
		fdf->map->alpha -= 0.05;
	if (key == XK_w)
		fdf->map->alpha += 0.05;
	if (key == XK_a)
		fdf->map->beta -= 0.05;
	if (key == XK_d)
		fdf->map->beta += 0.05;
	if (key == XK_z)
		fdf->map->gamma -= 0.05;
	if (key == XK_x)
		fdf->map->gamma += 0.05;
}

int	check_key(int keysym, t_data *fdf)
{
	if (is_key(keysym))
	{
		do_key(keysym, fdf);
	}
	if (keysym == XK_Escape)
	{
		kill_all(fdf);
	}
	return (0);
}
