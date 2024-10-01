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

void	var_init(t_data *fdf)
{
	fdf->map->zoom = 0.50;
	fdf->map->width = WINDOW_WIDTH * fdf->map->zoom;
	fdf->map->height = WINDOW_HEIGHT * fdf->map->zoom;
}

/* void	var_init(t_data *img, char *filename)
{
	img->fd = open(filename, O_RDONLY);
	if (img->fd < 0)
	{
		file_error(1);
		return ;
	}
	img->col = 0;
	img->rows = 0;
	img->draw.zoom = 0.65;
	img->draw.rotation = 0;
	img->draw.width_x = WINDOW_WIDTH * img->draw.zoom;		//Possivel correcao
	img->draw.height_y = WINDOW_HEIGHT * img->draw.zoom;
	img->draw.last_x = 0;
	img->draw.last_y = 0;
	img->draw.pos_x = 0.0;
	img->draw.pos_y = 0.0;
}*/
