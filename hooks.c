/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadlane <cadlane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/15 04:43:04 by cadlane           #+#    #+#             */
/*   Updated: 2024/08/15 05:15:34 by cadlane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	close_handler(t_fractal *fractal)
{
	mlx_destroy_image(fractal->mlx_init,
		fractal->img.img_ptr);
	mlx_destroy_window(fractal->mlx_init,
		fractal->mlx_window);
	mlx_destroy_display(fractal->mlx_init);
	free(fractal->mlx_init);
	exit(0);
}

int	key_handler(int keysym, t_fractal *fractal)
{
	if (keysym == XK_Escape)
		close_handler(fractal);
	render(fractal);
	return (0);
}

/*
 * int (*f)(int button, int x, int y, void *param)
*/
int	mouse_handler(int button, int x, int y, t_fractal *fractal)
{
	(void)x;
	(void)y;
	if (button == Button5)
	{
		fractal->zoom *= 0.95;
	}
	else if (button == Button4)
	{
		fractal->zoom *= 1.05;
	}
	render(fractal);
	return (0);
}
