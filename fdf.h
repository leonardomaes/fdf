/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmaes <lmaes@student.42porto.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/11 12:49:40 by lmaes             #+#    #+#             */
/*   Updated: 2024/07/11 12:49:43 by lmaes            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
#define FDF_H

/***********************************************/
/*					Include					   */
/***********************************************/

# include "includes/ft_printf/ft_printf.h"
# include "includes/libft/libft.h"

# include "mlx/mlx.h"
# include "mlx/mlx_int.h"
# include <X11/X.h>
#include <X11/keysym.h>

# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <stdio.h>

/***********************************************/
/*					Structs					   */
/***********************************************/

typedef struct	s_data {
	//image
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;

	//mlx
    void	*mlx;
    void	*win;

	//draw
	double	x;
	double	y;
	double	zoom;

	//file
	int		fd;
	double		rows;
	double		col;
	char	*line[];
}				t_data;

/***********************************************/
/*					Defines					   */
/***********************************************/

// WINDOW SETTINGS
# define WINDOW_WIDTH 900
# define WINDOW_HEIGHT 600
# define MIDDLE_WIDTH WINDOW_WIDTH/2
# define MIDDLE_HEIGHT WINDOW_HEIGHT/2
# define MLX_ERROR 1
// COLORS
# define RED_PIXEL 0xFF000000
# define GREEN_PIXEL 0x0000FF00
# define BLUE_PIXEL 0x00FF0000
# define WHITE_PIXEL 0xFFFFFFFF
// KEYBOARD
# define ESC	65307
# define W		119
# define A		97
# define S		115
# define D		100

/***********************************************/
/*				Declarations				   */
/***********************************************/
// FORMATS
void	print_square(t_data *data, int x, int y);
void	print_triangle(t_data *data, int x, int y);
void	print_hexagon(t_data *data, int x, int y);
void	print_line(t_data *data);
void	draw_between(t_data *data);
void	print_fdf(t_data *data);

// COMMANDS
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
int		check_key(int keycode, t_data *data);

// CHECKERS
int		file_check(t_data *img);
int		number_check(t_data *img);

//	ERRORS
void file_error(int flag);

// UTILS
void	var_init(t_data *wininfo);
int		kill_all(t_data *data);
void	clear_all(t_data *data);


#endif