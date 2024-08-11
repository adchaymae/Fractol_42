/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cadlane <cadlane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/27 00:55:26 by cadlane           #+#    #+#             */
/*   Updated: 2024/08/10 03:19:47 by cadlane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
#define FRACTOL_H

#include <stdio.h>  //TODO debugging
#include <stdlib.h> //malloc free
#include <unistd.h> // write
#include <math.h>
#include <X11/X.h>
#include <X11/keysym.h>
#include "minilibx-linux/mlx.h"


/*
 * We use a square to
 * keep the rendering math simple
 */
#define WIDTH 800
#define HEIGHT 800

/*
 * COLORS
 */
#define BLACK 0x000000 // RGB(0, 0, 0)
#define WHITE 0xFFFFFF // RGB(255, 255, 255)
#define RED 0xFF0000   // RGB(255, 0, 0)
#define GREEN 0x00FF00 // RGB(0, 255, 0)
#define BLUE 0x0000FF  // RGB(0, 0, 255)

// Psychedelic colors
#define MAGENTA_BURST 0xFF00FF      // A vibrant magenta
#define LIME_SHOCK 0xCCFF00         // A blinding lime
#define NEON_ORANGE 0xFF6600        // A blazing neon orange
#define PSYCHEDELIC_PURPLE 0x660066 // A deep purple
#define AQUA_DREAM 0x33CCCC         // A bright turquoise
#define HOT_PINK 0xFF66B2           // As the name suggests!
#define ELECTRIC_BLUE 0x0066FF      // A radiant blue
#define LAVA_RED 0xFF3300           // A bright, molten red

/*
 * COMPLEX value
 */
typedef struct s_complex
{
    //		real
    double x;
    //		i
    double y;
} t_complex;

/*
 * IMAGE
 * This is basically a pixels buffer
 * values from mlx_get_data_addr()
 */
typedef struct s_img
{
    void *img_ptr;    // pointer to image struct
    char *pixels_ptr; // points to the actual pixels
    int bpp;
    int endian;
    int line_len;
} t_img;

/*
 * FRACTAL ID
 * ~ MLX stuff
 * ~ Image
 * ~ Hooks values
 */
typedef struct s_fractal
{
    char *name;
    // MLX
    void *mlx_init; // mlx_init()
    void *mlx_window;     // mlx_new_window()
    // Image
    t_img img;

    // Hooks member variables //TODO
    double escape_value; // hypotenuse
    int nb_iteraions;
    double	shift_x;
	double	shift_y;
	double	zoom;
} t_fractal;

int ft_strncmp(char *s1, char *s2, int n);
void ft_putstr(char *s);
void init(t_fractal *fractal);
void render(t_fractal *fractal);
double map(double unscaled_num, double new_min, double new_max, double old_min, double old_max);
t_complex   sum_complex(t_complex z1, t_complex z2);
t_complex   square_complex(t_complex z);
void	data_init(t_fractal *fractal);

#endif