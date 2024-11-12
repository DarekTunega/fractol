#include "../include/anarchy.h"

int	ft_strcmp(const char *s1, const char *s2)
{
	while (*s1 != '\0' && *s2 != '\0' && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	if (*s1 - *s2 < 0)
		return (1);
	if (*s1 - *s2 > 0)
		return (1);
	return (0);
}

void	error_exit(char *errormess, char *correctMess, t_result res)
{
	printf(R"%s\n"RST, errormess);
	if (correctMess == NULL && res == F)
		exit(EXIT_FAILURE);
	else if (correctMess == NULL && res == S)
		exit(EXIT_SUCCESS);
	else
	{
		if (res == S)
		{
			printf(G "%s\n" RST, correctMess);
			exit(EXIT_FAILURE);
		}
		else
		{
			printf(G "%s\n" RST, correctMess);
			exit(EXIT_FAILURE);
		}
	}
}

int	sl(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	julia(int count_w, int count_h, double c_re, double c_im)
{
	double	x;
	double	y;
	int		i;
	double	x_new;

	x = ((count_w - window_width / 2) * 3.0 / window_width);
	y = ((window_height / 2) - count_h) * 3.0 / window_height;
	i = 0;
	while (x * x + y * y < 4 && i < FPS)
	{
		x_new = x * x - y * y + c_re;
		y = 2 * x * y + c_im;
		x = x_new;
		i++;
	}
	return (i);
}

void	renderer_innit(t_fractol *renderer)
{
	renderer->mlx = mlx_init(window_width, window_height, NAME, false);
	if (!renderer->mlx)
	{
		free(renderer->mlx);
		error_exit("Failed to initialize mlx\n", NULL, F);
	}
	renderer->width = window_width;
	renderer->height = window_height;
	if (!renderer->mlx)
		error_exit("Failed to initialize mlx\n", NULL, F);
}

char	*tolow(char *str)
{
	int		i;
	char	*res;
	char	toadd;

	i = 0;
	res = malloc(sizeof(char) * (sl(str) + 1));
	if (!res)
		return (NULL);
	while (str[i])
	{
		toadd = str[i];
		if (toadd >= 65 && toadd <= 90)
			toadd += 32;
		res[i] = toadd;
		i++;
	}
	res[i] = '\0';
	return (res);
}

void	register_key_press(void *param)
{
	t_fractol	*renderer;

	renderer = (t_fractol *)param;
	if (mlx_is_key_down(renderer->mlx, MLX_KEY_ESCAPE))
		mlx_close_window(renderer->mlx);
}

int	mandelbrot(int count_w, int count_h, int i)
{
	double	c_re;
	double	c_im;
	double	x;
	double	x_new;
	double	y;

	c_re = ((count_w - window_width / 2) * 3.0 / window_width) - 0.5;
	c_im = ((window_height / 2) - count_h) * 2.0 / window_height;
	x = 0;
	y = 0;
	while ((x * x + y * y < 4) && (i < FPS))
	{
		x_new = x * x - y * y + c_re;
		y = 2 * x * y + c_im;
		x = x_new;
		i++;
	}
	return (i);
}

void	put_pixel_mandelbrot(mlx_image_t *img)
{
	int	iter;
	int	count_w;
	int	count_h = 0;

	while (count_h < window_height)
	{
		count_w = 0;
		while (count_w < window_width)
		{
			iter = mandelbrot(count_w, count_h, 0);
			if (iter < FPS)
				mlx_put_pixel(img, count_w, count_h, 0xFFFFFFFF);
			else
				mlx_put_pixel(img, count_w, count_h, 0x000000FF);
			count_w++;
		}
		count_h++;
	}
}

void	put_pixel_julia(mlx_image_t *img, double c_re, double c_im)
{
	int	iter;
	int	count_w;
	int	count_h;

	for (count_h = 0; count_h < window_height; count_h++)
	{
		for (count_w = 0; count_w < window_width; count_w++)
		{
			iter = julia(count_w, count_h, c_re, c_im);
			if (iter < FPS)
				mlx_put_pixel(img, count_w, count_h, 0xFFFFFFFF);
			else
				mlx_put_pixel(img, count_w, count_h, 0x000000FF);
		}
	}
}

void	validate_julia(char **argv)
{
	int	i;
	int	dot_count;
	int	j;

	j = 2;
	i = 0;
	dot_count = 0;
	while (j <= 3)
	{
		i = 0;
		dot_count = 0;
		while (argv[j][i])
		{
			if ((argv[j][i] < '0' || argv[j][i] > '9') && argv[j][i] != '.')
				error_exit("Invalid argument passed", "julia <double> <double>",
						F);
			if (argv[j][i] == '.')
			{
				dot_count++;
				if (dot_count > 1)
					error_exit("Invalid argument passed",
							"julia <double> <double>", F);
			}
			i++;
		}
		j++;
	}
}

int	main(int argc, char **argv)
{
	char		*tocomp;
	t_fractol	renderer;
	mlx_image_t	*img;

	if (argc < 2)
		error_exit("No arguments passed",
					"either 'mandelbrot' or 'julia <double> <double>",
					F);
	tocomp = tolow(argv[1]);
	if ((!ft_strcmp("mandelbrot", tocomp) && argc == 2) || (argc == 4
			&& !ft_strcmp("julia", tocomp)))
	{
		free(tocomp);
		renderer_innit(&renderer);
		img = mlx_new_image(renderer.mlx, window_width, window_height);
		mlx_image_to_window(renderer.mlx, img, 0, 0);
		if (!ft_strcmp("mandelbrot", tocomp))
        {
            put_pixel_mandelbrot(img);
        }
		else if (!ft_strcmp("julia", tocomp) && argc == 4)
        {
			validate_julia(argv);
            double c_re = atof(argv[2]);
            double c_im = atof(argv[3]);
            put_pixel_julia(img, c_re, c_im);
        }
		mlx_loop_hook(renderer.mlx, &register_key_press, &renderer);
		mlx_loop(renderer.mlx);
		mlx_delete_image(renderer.mlx, img);
		mlx_terminate(renderer.mlx);
	}
	else
	{
		free(tocomp);
		error_exit("incorrectly passed data",
					"either 'mandelbrot' or 'julia <double> <double>",
					F);
	}
	return (0);
}
