#ifndef ANARCHY_H
# define ANARCHY_H

# include "./MLX42/include/MLX42/MLX42.h"
# include <errno.h>
# include <limits.h>
# include <pthread.h>
# include <stdbool.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# define RST "\033[0m"
# define R "\x1B[31m"
# define G "\x1B[32m"
# define FPS 100
# define window_width 800
# define window_height 800
# define NAME "Fractol"

typedef enum e_result
{
	S,
	F
}	t_result;

typedef struct s_fractol
{
	mlx_t				*mlx;
	int					width;
	int					height;
	int					move_count;
}						t_fractol;
#endif
