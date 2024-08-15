#ifndef FRACTOL_H
# define FRACTOL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h> 
# include <math.h>
# include <X11/X.h>
# include <X11/keysym.h>
# include "minilibx-linux/mlx.h"

#define WIDTH	800
#define	HEIGHT	800

#define BLACK       0x000000  
#define WHITE       0xFFFFFF 
#define PSYCHEDELIC_PURPLE 0x660066
#define AQUA_DREAM      0x33CCCC

typedef struct	s_complex
{
	double	x;
	double	y;
}				t_complex;


typedef struct	s_img
{
	void	*img_ptr; 
	char	*pixels_ptr;
	int		bpp;
	int		endian;
	int		line_len;
}				t_img;

typedef struct	s_fractal
{
	char	*name;
	void	*mlx_init; 
	void	*mlx_window; 
	t_img	img;

	double	diverge_value; 
	int		iterations_nb; 
	double	shift_x;
	double	shift_y;
	double	zoom;
	double	julia_x;
	double	julia_y;
}				t_fractal;


int		ft_strncmp(char *s1, char *s2, int n);
void    ft_putstr(char *s);
double  string_to_double(char *s);
void    init(t_fractal *fractal);
void    render(t_fractal *fractal);

double		map(double unscaled_num, double new_min, double new_max, double old_min, double old_max);
t_complex   sum_complex(t_complex z1, t_complex z2);
t_complex   square_complex(t_complex z);

int			key_handler(int keysym, t_fractal *fractal);

int    	close_handler(t_fractal *fractal);
int		mouse_handler(int button, int x, int y, t_fractal *fractal);
int		julia_track(int x, int y, t_fractal *fractal);

#endif