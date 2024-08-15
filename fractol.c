/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadlane <cadlane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 04:42:51 by cadlane           #+#    #+#             */
/*   Updated: 2024/08/15 05:10:04 by cadlane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	main(int ac, char **av)
{
	t_fractal	fractal;

	if ((2 == ac && !ft_strncmp(av[1], "mandelbrot", 10))
		|| (4 == ac && !ft_strncmp(av[1], "julia", 5)))
	{
		fractal.name = av[1];
		if (!ft_strncmp(fractal.name, "julia", 5))
		{
			fractal.julia_x = string_to_double(av[2]);
			fractal.julia_y = string_to_double(av[3]);
		}
		init(&fractal);
		render(&fractal);
		mlx_loop(fractal.mlx_init);
	}
	else
	{
		ft_putstr("please fill one of this forms \n .");
		ft_putstr("/fractol mandelbrot \n./fractol julia <real> <i>");
		exit(1);
	}
}
