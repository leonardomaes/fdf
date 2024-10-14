/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmaes <lmaes@student.42porto.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 12:18:19 by lmaes             #+#    #+#             */
/*   Updated: 2024/10/07 12:18:20 by lmaes            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf_bonus.h"

int	count_cols(char *line, int expected_cols)
{
	char	**split_line;
	int		cols;

	split_line = ft_split(line, ' ');
	cols = 0;
	while (split_line[cols])
		cols++;
	free_split(split_line);
	if (expected_cols == 0)
		return (cols);
	if (cols != expected_cols)
		return (-1);
	return (cols);
}

int	check_cols(char *line, t_info *map)
{
	int		cols;
	char	*line_trim;

	line_trim = ft_strtrim(line, "\n");
	cols = count_cols(line_trim, map->cols);
	if (cols == -1)
	{
		free(line_trim);
		return (1);
	}
	if (map->cols == 0)
		map->cols = cols;
	free(line_trim);
	return (0);
}

int	check_line(int fd, t_info *map)
{
	char	*line;

	line = get_next_line(fd);
	if (!line)
	{
		ft_printf("ERROR:File can't be readed!\n");
		return (1);
	}
	while (line)
	{
		if (check_cols(line, map) == 1)
		{
			ft_printf("ERROR:Map in wrong format, check the edges!\n");
			free(line);
			return (1);
		}
		free(line);
		line = get_next_line(fd);
		map->rows++;
	}
	free(line);
	return (0);
}

void	free_point(t_points **points, int y)
{
	while (y-- > 0)
		free(points[y]);
	free(points);
}

int	get_line(t_points **points, t_data *fdf, int fd)
{
	char	*line;
	char	*line_trim;
	int		y;

	y = 0;
	line = get_next_line(fd);
	while (line)
	{
		line_trim = ft_strtrim(line, "\n");
		points[y] = get_data(line_trim, fdf, y);
		if (points[y] == NULL)
		{
			free_point(points, y);
			free(line_trim);
			free(line);
			return (1);
		}
		free(line_trim);
		free(line);
		y++;
		line = get_next_line(fd);
	}
	free(line);
	return (0);
}
