/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   formats.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmaes <lmaes@student.42porto.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 13:12:56 by lmaes             #+#    #+#             */
/*   Updated: 2024/07/11 13:12:57 by lmaes            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <X11/X.h>
#include "../fdf.h"

void    draw_between(t_data *data)
{
	my_mlx_pixel_put(data, data->x, data->y, GREEN_PIXEL);
}

void    print_fdf(t_data *img)
{
    int     i;
    int     j;
    double     x;
    double     y;

    j = 0;
    img->pos_y = MIDDLE_HEIGHT - (((MIDDLE_HEIGHT / (img->rows / 2)) * img->zoom) * (img->rows / 2));
    img->pos_x = MIDDLE_WIDTH - (((MIDDLE_WIDTH / (img->col / 2)) * img->zoom) * (img->col / 2));
    y = img->pos_y;
    printf("y1= %f\n", img->rows);
    printf("y1= %f\n", img->col);
    while (j < img->rows)
    {
        i = 0;
        x = img->pos_x;
        while (i < img->col)
        {
            my_mlx_pixel_put(img, x, y, WHITE_PIXEL);   
            x += (img->x / img->col);
            i++;
        }
        y += (img->y / img->rows);
        j++;
    }
}
