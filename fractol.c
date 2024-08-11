/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadlane <cadlane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 01:00:18 by cadlane           #+#    #+#             */
/*   Updated: 2024/08/10 03:14:50 by cadlane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "minilibx-linux/mlx.h"


int main(int argc, char **argv)
{
    t_fractal fractal;
    if((argc == 2 && !ft_strncmp(argv[1], "mandelbrot",10))
    || (argc == 4 && !ft_strncmp(argv[1], "julia",5)))
    {
        fractal.name = argv[1];
        init(&fractal);
		render(&fractal);
		mlx_loop(fractal.mlx_init);
    }
    else
    {
        ft_putstr("please fill one of this forms \n ./fractol mandelbrot \n ===================== \n ./fractol julia <real> <i>");
        exit(1);
    }
}