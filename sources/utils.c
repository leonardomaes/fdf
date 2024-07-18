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
	img->zoom = 1.5;
	img->y = WINDOW_HEIGHT;
	img->x = WINDOW_WIDTH;
}

double	scale(double num, double n_mi, double n_ma, double o_mi)
{
	double	scaled_number;

	scaled_number = (n_ma - n_mi) * (num - o_mi) / (WINDOW_HEIGHT - o_mi) + n_mi;
	return (scaled_number);
}

double	scale_x(double x_pos, double scal)
{
	double	x_scaled;
/* 	double	x_final; */

	x_scaled = ((WINDOW_WIDTH / x_pos) * 100) / (scal * 10);
	return (x_scaled);

/* 	x_scaled = x_pos * scal;
	x_final = (x_scaled - width * (scal - 1) / 2);
	return (x_final); */
}

double	scale_y(double y_pos, double scal, double heigth)
{
	double	y_scaled;
	double	y_final;

	y_scaled = y_pos * scal;
	y_final = (y_scaled - heigth * (scal - 1) / 2);
	return (y_final);
}

