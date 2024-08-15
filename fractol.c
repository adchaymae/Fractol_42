
#include "fractol.h"

int	main(int ac, char **av)
{
	t_fractal	fractal;


	if (2 == ac && !ft_strncmp(av[1], "mandelbrot", 10)
		|| 4 == ac && !ft_strncmp(av[1], "julia", 5))
	{
		fractal.name = av[1];
		if (!ft_strncmp(fractal.name, "julia", 5))
		{
			fractal.julia_x = atodbl(av[2]);
			fractal.julia_y = atodbl(av[3]);
		}
		fractal_init(&fractal);
		fractal_render(&fractal);
		mlx_loop(fractal.mlx_init);
	}
	else
	{
		ft_putstr("please fill one of this forms \n ./fractol mandelbrot \n./fractol julia <real> <i>");
        exit(1);
	}
}