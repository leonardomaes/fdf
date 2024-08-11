/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmaes <lmaes@student.42porto.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 12:12:08 by lmaes             #+#    #+#             */
/*   Updated: 2024/08/10 12:12:11 by lmaes            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

void    isometric(double *x, double *y, double z)
{
    double previous_x;
    double previous_y;

    if (x == NULL || y == NULL)
    {
        printf("Erro no isometric");
        exit(1);
    }
    previous_x = *x;
    previous_y = *y;
    *x = (previous_x - previous_y) * cos(0.523599);
    *y = (previous_x + previous_y) * sin(0.523599) - z;
}

double	ft_abs(float n)
{
	if (n < 0)
		return (-n);
	return(n);
}