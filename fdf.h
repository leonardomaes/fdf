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
	int		rows;
	int		col;
	char	*line[];
}				t_data;


# define WINDOW_WIDTH 960
# define WINDOW_HEIGHT 540
# define SCALE 1
# define MLX_ERROR 1
# define RED_PIXEL 0xFF000000
# define GREEN_PIXEL 0x0000FF00
# define BLUE_PIXEL 0x00FF0000
# define WHITE_PIXEL 0xFFFFFFFF
# define ESC	65307
# define W		119
# define A		97
# define S		115
# define D		100

// FORMATS
void	print_square(t_data *data, int x, int y);
void	print_triangle(t_data *data, int x, int y);
void	print_hexagon(t_data *data, int x, int y);
void	print_line(t_data *data);
void	draw_screen(t_data *data);
void	print_fdf(t_data *data);

// COMMANDS
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
int		handle_keypress(int keysym, t_data *win);
int		render(t_data *data);
int		draw_keypress(int keysym, t_data *data);
int		check_key(int keycode, t_data *data);

// CHECKERS
int		file_check(t_data *img);
int		number_check(t_data *img);

//	ERRORS
void file_error(int flag);

// UTILS
void	var_init(t_data *wininfo);
double	scale(double num, double n_mi, double n_ma, double o_mi);
double	scale_x(double x_pos, double scal);
double	scale_y(double y_pos, double scal, double heigth);

#endif