#Compile Options
NAME = fdf
CC = cc
CFLAGS = -Wall -Wextra -Werror
MLXFLAGS = -L/usr/X11R6/lib -lX11 -lXext -lm

# Directories
MLX = mlx/libmlx_Linux.a
LIBFT = includes/libft/libft.a
PRINTF = includes/ft_printf/libftprintf.a

#
SRC =	main.c sources/formats.c sources/colors.c sources/commands.c \
		sources/checkers.c sources/errors.c
#

# Commands
RM = rm -rf
OBJ = $(SRC:.c=.o)

all: $(NAME)

%.o : %.c
			$(CC) $(CFLAGS) -c $*.c -o $*.o

$(LIBFT):
			@make --silent -C includes/libft

$(PRINTF):
			@make --silent -C includes/ft_printf

$(MLX):
			make --silent -C mlx

$(NAME) : $(OBJ) $(PRINTF) $(LIBFT) $(MLX)
	@$(CC) $(CFLAGS) $(MLXFLAGS) -o $(NAME) $(OBJ) $(LIBFT) $(PRINTF) $(MLX) $(MLXFLAGS)

clean:
			$(RM) $(OBJ)
			@make --silent -C includes/ft_printf clean
			@make --silent -C includes/libft clean
fclean: clean
			$(RM) $(NAME)
			@make --silent -C includes/ft_printf fclean
			@make --silent -C includes/libft  fclean

re: fclean all
