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

void	var_init(t_data *img, char *filename)
{
	img->fd = open(filename, O_RDONLY);
	if (img->fd < 0)
	{
		file_error(1);
		return ;
	}
	img->col = 0;
	img->rows = 0;
	img->zoom = 0.50;
	img->rotation = 0;
	img->width_x = WINDOW_WIDTH * img->zoom;		//Possivel correcao
	img->height_y = WINDOW_HEIGHT * img->zoom;
	img->last_x = 0;
	img->last_y = 0;
	img->pos_x = 0.0;
	img->pos_y = 0.0;
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
	int i;
	
	i = 0;
	if (!data)
		return ;
	if (data->win)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx)
		mlx_destroy_display(data->mlx);
	
	while (i < data->rows)
	{
		free(data->points[i++]);
	}
	free(data->points);
	free(data->mlx);
}

double	**alloc_points(t_data *img)
{
	int i;
	double **points;
	i = 0;

	points = (double **)malloc(img->rows * sizeof(double *));
	if (points == NULL)
		return (0);

	i = 0;
	while (i < img->rows)
	{
		points[i] = (double *)malloc(img->col * sizeof(double));
		if (points[i] == NULL)
		{
			while (--i >= 0)
				free(points[i]);
			free(points);
			return (0);
		}
		i++;
	}
	return (points);
}