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
SRC =	sources/main.c sources/formats.c \
		sources/checkers.c sources/utils.c sources/exits.c \
		sources/checker_utils.c \

BSRC =	sources_bonus/main_bonus.c sources_bonus/formats_bonus.c sources_bonus/commands_bonus.c \
		sources_bonus/checkers_bonus.c sources_bonus/utils_bonus.c sources_bonus/exits_bonus.c \
		sources_bonus/checker_utils_bonus.c sources_bonus/rotate_bonus.c \
#

# Commands
RM = rm -rf
OBJ = $(SRC:.c=.o)
B_OBJ = $(BSRC:.c=.o)

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
bonus: $(B_OBJ) $(PRINTF) $(LIBFT) $(MLX)
	@$(CC) $(CFLAGS) $(MLXFLAGS) -o $(NAME)_bonus $(B_OBJ) $(LIBFT) $(PRINTF) $(MLX) $(MLXFLAGS)

clean:
			$(RM) $(OBJ) $(B_OBJ)
			@make --silent -C includes/ft_printf clean
			@make --silent -C includes/libft clean
fclean: clean
			$(RM) $(NAME)
			$(RM) $(NAME)_bonus
			@make --silent -C includes/ft_printf fclean
			@make --silent -C includes/libft  fclean
re: fclean all
