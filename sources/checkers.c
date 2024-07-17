/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmaes <lmaes@student.42porto.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 13:49:12 by lmaes             #+#    #+#             */
/*   Updated: 2024/07/15 13:49:13 by lmaes            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../fdf.h"

int	file_check(t_data *img)
{
	int	rows;
	int	i;

	rows = 0;
	i = 0;
	img->line[i] = get_next_line(img->fd);
	while (img->line[i])
	{
		ft_printf("%s", img->line[i]);		// APAGAR
		img->line[++i] = get_next_line(img->fd);
		rows++;
		if (img->line[i] && ft_strlen(img->line[i]) != ft_strlen(img->line[i
					- 1]))
		{
			file_error(2);
			return (0);
		}
	}
	close(img->fd);
	img->rows = rows;
	return (1);
}

int	number_check(t_data *img)	// Continua daqui
{
	int		i;
	i = 0;
	
}