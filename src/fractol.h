/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <idbellasaid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 18:01:39 by sid-bell          #+#    #+#             */
/*   Updated: 2020/04/26 14:16:13 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
#define FRACTOL_H
# include <mlx.h>
# include "libft.h"
# include <stdio.h>
# include <math.h>
# include <pthread.h>

# define MANDELBROT 0
# define JULIA 1
# define BURNING 2
# define WIDTH 600
# define HEIGHT 400
# define MAX 20
# define GREY 16579836
# define RED 13395558
# define GREEN 13421670

typedef struct	s_complex
{
	double a;
	double b;
}				t_complex;

typedef struct	s_params
{
	void		*win_ptr;
	void		*mlx_ptr;
	t_complex	julia;
	char		fractal;
	double		start_x;
	double		start_y;
	int			mouse_down;
	int			x;
	int			y;
	double		zoom;
	int			max;
	int			step;
	int			stop;
	t_complex	z;
	t_complex	c;
}				t_params;

int		ft_key_press(int keycode);
void	draw(t_params *p);
int		ft_mouse_press(int keycode, int x, int y);
int		ft_mouse_release(int button);
int		ft_mouse_move(int x, int y);
double	map(int val, double start_x, double zoom);
t_params	*ft_getter(t_params *p);
#endif