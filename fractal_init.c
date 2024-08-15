#include "fractol.h"
static void	malloc_error(void)
{
	ft_putsr("Problems with malloc");
	exit(1);
}



static void	data_init(t_fractal *fractal)
{
	fractal->diverge_value = 4; // 2 ^ 2, my hypotenuse
	fractal->iterations_nb= 42; 
	fractal->shift_x = 0.0;
	fractal->shift_y = 0.0;
	// zoom factor
	fractal->zoom = 1.0;
}


static void	events_init(t_fractal *fractal)
{
	mlx_hook(fractal->mlx_window,
			KeyPress,
			KeyPressMask,
			key_handler,
			fractal);
	mlx_hook(fractal->mlx_window,
			ButtonPress,
			ButtonPressMask,
			mouse_handler,
			fractal);
	mlx_hook(fractal->mlx_window,
			DestroyNotify,
			StructureNotifyMask,
			close_handler,
			fractal);
	mlx_hook(fractal->mlx_window,
			MotionNotify,
			PointerMotionMask,
			julia_track,
			fractal);
}


void	fractal_init(t_fractal *fractal)
{
	fractal->mlx_init = mlx_init();
	if (NULL == fractal->mlx_init)
		malloc_error();
	fractal->mlx_window = mlx_new_window(fractal->mlx_init,
										WIDTH,
										HEIGHT,
										fractal->name);
	if (NULL == fractal->mlx_window)
	{
		mlx_destroy_display(fractal->mlx_init);
		free(fractal->mlx_init);
		malloc_error();
	}
	fractal->img.img_ptr = mlx_new_image(fractal->mlx_init,
										WIDTH, HEIGHT);
	if (NULL == fractal->img.img_ptr)
	{
		mlx_destroy_window(fractal->mlx_init, fractal->mlx_window);
		mlx_destroy_display(fractal->mlx_init);
		free(fractal->mlx_init);
		malloc_error();
	}
	fractal->img.pixels_ptr = mlx_get_data_addr(fractal->img.img_ptr,
										&fractal->img.bpp,
										&fractal->img.line_len,
										&fractal->img.endian);
	events_init(fractal);
	data_init(fractal);
}