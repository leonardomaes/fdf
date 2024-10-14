/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmaes <lmaes@student.42porto.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 13:49:12 by lmaes             #+#    #+#             */
/*   Updated: 2024/07/15 13:49:13 by lmaes            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/fdf_bonus.h"

t_info	*read_map(t_data *fdf)
{
	int		fd;
	t_info	*map;

	map = malloc(sizeof(t_info));
	map->cols = 0;
	map->rows = 0;
	fd = open(fdf->filename, O_RDONLY);
	if (fd < 0)
	{
		ft_printf("ERROR:File doesn't exist or couldn't open!\n");
		free(map);
		close(fd);
		return (NULL);
	}
	if (check_line(fd, map) == 1)
	{
		close(fd);
		free(map);
		return (NULL);
	}
	close(fd);
	return (map);
}

t_points	*get_data(char *line, t_data *fdf, int y)
{
	int			x;
	char		**data;
	char		**sep_data;
	t_points	*points;

	x = 0;
	points = malloc(fdf->map->cols * sizeof(t_points));
	if (!points)
		return (NULL);
	data = ft_split(line, ' ');
	while (data[x])
	{
		sep_data = ft_split(data[x], ',');
		points[x].x = x;
		points[x].y = y;
		points[x].original_z = ft_atoi(sep_data[0]);
		if (sep_data[1])
			points[x].color = ft_atoi_hex(sep_data[1]);
		else
			points[x].color = WHITE_PIXEL;
		x++;
		free_split(sep_data);
	}
	free_split(data);
	return (points);
}

t_points	**fill_points(t_data *fdf)
{
	int			fd;
	t_points	**points;

	fd = open(fdf->filename, O_RDONLY);
	if (fd < 0)
	{
		ft_printf("ERROR:File doesn't exist or couldn't open!\n");
		close(fd);
		return (NULL);
	}
	points = malloc(fdf->map->rows * sizeof(t_points *));
	if (!points)
		return (NULL);
	if (get_line(points, fdf, fd) == 1)
	{
		close(fd);
		free(points);
		return (NULL);
	}
	close(fd);
	return (points);
}

int	file_check(t_data *fdf)
{
	int	size;

	size = ft_strlen(fdf->filename);
	if (ft_strncmp(fdf->filename + (size - 4), ".fdf", 4) != 0)
	{
		ft_printf("ERROR:File specified in wrong format!\n");
		return (1);
	}
	fdf->map = read_map(fdf);
	if (fdf->map == NULL)
		return (1);
	fdf->points = fill_points(fdf);
	if (fdf->points == NULL)
		return (1);
	retore_original_z(fdf);
	return (0);
}
