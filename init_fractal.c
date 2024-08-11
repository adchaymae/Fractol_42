/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_fractal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadlane <cadlane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 03:21:09 by cadlane           #+#    #+#             */
/*   Updated: 2024/08/10 03:21:11 by cadlane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "minilibx-linux/mlx.h"

static void	malloc_error(void)
{
	ft_putstr("Problems with malloc");
	exit(EXIT_FAILURE);
}



void	data_init(t_fractal *fractal)
{
	fractal->escape_value = 4; // 2 ^ 2, my hypotenuse
	fractal->nb_iteraions = 42;
	fractal->shift_x = 0.0;
	fractal->shift_y = 0.0;
	// zoom factor
	fractal->zoom = 1.0;
}

void init(t_fractal *fractal)
{
    fractal->mlx_init = mlx_init();
    if (NULL == fractal->mlx_init)
		malloc_error();
    fractal->mlx_window = fractal->mlx_window = mlx_new_window(fractal->mlx_init, WIDTH, HEIGHT, fractal->name);
    if (NULL == fractal->mlx_window)
	{
		mlx_destroy_display(fractal->mlx_init);
		free(fractal->mlx_init);
		malloc_error();
	}
    fractal->img.img_ptr = mlx_new_image(fractal->mlx_init, WIDTH, HEIGHT);
	if (NULL == fractal->img.img_ptr)
	{
		mlx_destroy_window(fractal->mlx_init, fractal->mlx_window);
		mlx_destroy_display(fractal->mlx_init);
		free(fractal->mlx_init);
		malloc_error();
	}
    fractal->img.pixels_ptr = mlx_get_data_addr(fractal->img.img_ptr,&fractal->img.bpp, &fractal->img.line_len, &fractal->img.endian);
    data_init(fractal);
}

