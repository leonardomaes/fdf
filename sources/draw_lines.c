/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_lines.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmaes <lmaes@student.42porto.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 13:58:59 by lmaes             #+#    #+#             */
/*   Updated: 2024/09/27 13:59:01 by lmaes            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void    calculate_offsets(t_data *img)
{
	double min_x;
	double min_y;
	double max_x;
	double max_y;
	double	x;
	double	y;
	int i;
	int	j;

	min_x = WINDOW_WIDTH;
	min_y = WINDOW_HEIGHT;
	max_x = 0;
	max_y = 0;
	j = 0;
	while (j < img->rows)
	{
		i = 0;
		while (i < img->col)
		{
			x = i * (img->draw.width_x / img->col);
			y = j * (img->draw.height_y / img->rows);
			isometric(&x, &y, img->points[j][i]);
			if (x < min_x) min_x = x;
			if (y < min_y) min_y = y;
			if (x > max_x) max_x = x;
			if (y > max_y) max_y = y;
			i++;
		}
		j++;
	}
	img->draw.pos_x = (WINDOW_WIDTH - (max_x - min_x)) / 2 - min_x;
	img->draw.pos_y = (WINDOW_HEIGHT - (max_y - min_y)) / 2 - min_y;
}

void    draw_line(t_data *img, int flag)
{
	t_draw line_draw;

	line_draw.dx = fabs(img->draw.cur_x - img->draw.last_x);			//
	line_draw.dy = fabs(img->draw.cur_y - img->draw.last_y);
	line_draw.sx = (img->draw.last_x < img->draw.cur_x) ? 1 : -1;		// Step x
	line_draw.sy = (img->draw.last_y < img->draw.cur_y) ? 1 : -1;		// Step y
	line_draw.d1 = (line_draw.dx - line_draw.dy);
	line_draw.x = img->draw.last_x;
	line_draw.y = img->draw.last_y;
	if (flag == 1)
	{
		while (line_draw.x <= img->draw.cur_x)
		{
			my_mlx_pixel_put(img, line_draw.x, line_draw.y, WHITE_PIXEL);
			line_draw.d2 = 2 * line_draw.d1;
			if (line_draw.d2 > -line_draw.dy)
			{
				line_draw.d1 -= line_draw.dy;
				line_draw.x += line_draw.sx;
			}
			if(line_draw.d2 < line_draw.dx)
			{
				line_draw.d1 += line_draw.dx;
				line_draw.y += line_draw.sy;
			}
		}
	}
	else if (flag == 2)
	{
		while (line_draw.y <= img->draw.cur_y)
		{
			my_mlx_pixel_put(img, line_draw.x, line_draw.y, WHITE_PIXEL);
			line_draw.d2 = 2 * line_draw.d1;
			if (line_draw.d2 > -line_draw.dy)
			{
				line_draw.d1 -= line_draw.dy;
				line_draw.x += line_draw.sx;
			}
			if(line_draw.d2 < line_draw.dx)
			{
				line_draw.d1 += line_draw.dx;
				line_draw.y += line_draw.sy;
			}
		}
	}
}