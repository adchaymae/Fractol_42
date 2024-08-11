/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_fractal.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadlane <cadlane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/10 03:21:30 by cadlane           #+#    #+#             */
/*   Updated: 2024/08/10 03:21:32 by cadlane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include "minilibx-linux/mlx.h"

/*
 * Put a pixel in my image buffer
*/
static void	my_pixel_put(int x, int y, t_img *img, int color)
{
	int	offset;

	offset = (y * img->line_len) + (x * (img->bpp / 8));
	*(unsigned int *)(img->pixels_ptr + offset) = color;
}

static void	init_c(t_complex *z, t_complex *c, t_fractal *fractal)
{	
	if (!ft_strncmp(fractal->name, "julia", 5))
	{
		//c->x = fractal->julia_x;
		//c->y = fractal->julia_y;
	}
	else
	{
		c->x = z->x;
		c->y = z->y;
	}
}

static void	handle_pixel(int x, int y, t_fractal *fractal)
{
	t_complex	z;
	t_complex	c;
	int			i;
	int			color;
	i = 0; 
	z.x = (map(x, -2, +2, 0, WIDTH) * fractal->zoom) + fractal->shift_x;
	z.y = (map(y, +2, -2, 0, HEIGHT) * fractal->zoom) + fractal->shift_y;

	// How many times you want to iterate z^2 + c
	//	to check if the point escaped?
    init_c(&z, &c, fractal);
	while (i < fractal->nb_iteraions)
	{
		// actual z^2 + c	
		// z = z^2 + c
		z = sum_complex(square_complex(z), c);
		// Is the value escaped???
		// if hypotenuse > 2 i assume the point has escaped
		if ((z.x * z.x) + (z.y * z.y) > fractal->escape_value)
		{
			color = map(i, BLACK, WHITE, 0, fractal->nb_iteraions);
			my_pixel_put(x, y, &fractal->img, color);
			return ;
		}
		++i;	
	}
    my_pixel_put(x, y, &fractal->img, AQUA_DREAM);
	// We are in MANDELBROT given the iterations made
	//my_pixel_put(x, y, &fractal->img, PSYCHEDELIC_PURPLE);
}

void render(t_fractal *fractal){
	int	x;
	int	y;

	y = -1;
	while (++y < 800)
	{
		x = -1;
		while (++x < 800)
		{
			handle_pixel(x, y, fractal);
		}
	}
	mlx_put_image_to_window(fractal->mlx_init,fractal->mlx_window,fractal->img.img_ptr,0, 0);	

}