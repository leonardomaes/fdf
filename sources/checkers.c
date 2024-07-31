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
	int	i;

	i = 0;
	img->line[i] = get_next_line(img->fd);
	while (img->line[i])
	{
		ft_printf("%s", img->line[i]);		// APAGAR
		img->line[++i] = get_next_line(img->fd);
		img->rows++;
		if (img->line[i] && ft_strlen(img->line[i]) != ft_strlen(img->line[i
					- 1]))
		{
			file_error(2);
			return (0);
		}
	}
	close(img->fd);
	return (1);
}

/*int	number_check(t_data *img)	// Continua daqui
{
	int		i;
	
	i = 0;
	while (img->line[0][i])
	{
		if (ft_isdigit(img->line[0][i]))
			img->col++;
		if (ft_isalpha(img->line[0][i]))
			return (0);
		i++;
	}
	return (1);
}*/

int	number_check(t_data *img)
{
	int		i;
	int		j;
	int		k;
	double	**points;

	i = 0;
	while (img->line[0][i])
	{
		if (ft_isdigit(img->line[0][i]) && !ft_isdigit(img->line[0][i + 1]))
			img->col++;
		i++;
	}
	points = alloc_points(img);
	i = 0;
	while (i < img->rows)
	{
		j = 0;
		k = 0;
		while (img->line[i][j])
		{
			if (ft_isdigit(img->line[i][j]))
			{
				points[i][k] = 0;
				while (ft_isdigit(img->line[i][j]))
				{
					points[i][k] = points[i][k] * 10 + (img->line[i][j] - '0');
					j++;
				}
				printf("%i", (int)points[i][k]);
				k++;
			}
			else
				j++;
		}
		printf("\n");
		i++;
	}
	// Libere a memória alocada para points antes de retornar
	for (i = 0; i < img->rows; i++)
		free(points[i]);
	free(points);

	return (1);
}

