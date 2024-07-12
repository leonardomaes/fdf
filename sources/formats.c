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

void    print_square(t_data *data, int x, int y)
{
    int lenght, height;
    int tam;
    tam = 200;
    height = y - tam;
    lenght = x + tam;
    
    while (x <= lenght)
    {
        my_mlx_pixel_put(data, x, y, 0xFFFFFF);
        x++;
    }
    while (y >= height)
    {
        my_mlx_pixel_put(data, x, y, 0xFFFFFF);
        y--;
    }
    while (x >= (lenght - tam))
    {
        my_mlx_pixel_put(data, x, y, 0xFFFFFF);
        x--;
    }
    while (y <= (height + tam))
    {
        my_mlx_pixel_put(data, x, y, 0xFFFFFF);
        y++;
    }
}

void    print_triangle(t_data *data, int x, int y)
{
    int lenght, height;
    int tam;
    tam = 300;
    lenght = x + tam;
    height = y - tam;
    while (x < (lenght - (tam/2)) && y > height)
    {
        my_mlx_pixel_put(data, x, y, 0xFFFFFF);
        x++;
        y--;
    }
    while (x < lenght && y < (height + tam))
    {
        my_mlx_pixel_put(data, x, y, 0xFFFFFF);
        x++;
        y++;
    }
    while (x > (lenght - tam))
    {
        my_mlx_pixel_put(data, x, y, 0xFFFFFF);
        x--;
    }
}

void    print_hexagon(t_data *data, int x, int y)
{
    int lenght, height;
    int tam;
    tam = 300;
    lenght = x + tam;
    height = y - tam;
    while (x < (lenght - (tam/2)) && y > height)
    {
        my_mlx_pixel_put(data, x, y, 0xFFFFFF);
        x++;
        y--;
    }
    while (x < lenght && y < (height + tam))
    {
        my_mlx_pixel_put(data, x, y, 0xFFFFFF);
        x++;
        y++;
    }
    while (x > (lenght - tam))
    {
        my_mlx_pixel_put(data, x, y, 0xFFFFFF);
        x--;
    }
}

void    print_line(t_data *data)
{
    int lenght, height;
    int tam, x, y;
    x = 320;
    y = 400;
    tam = 300;
    lenght = x + tam;
    height = y - tam;
    while (x <= lenght)
    {
        my_mlx_pixel_put(data, x, y, GREEN_PIXEL);
        x++;
    }
}

void    draw_screen(t_data *data)
{
	my_mlx_pixel_put(data, data->x, data->y, GREEN_PIXEL);
}