/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 18:01:39 by sid-bell          #+#    #+#             */
/*   Updated: 2020/02/01 21:46:57 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
#define FRACTOL_H
# include <mlx.h>
# include "libft.h"
# include <stdio.h>
# include <math.h>
# include <pthread.h>

# define MANDELBROT -1
# define JULIA 1
# define WIDTH 300
# define HEIGHT 300
# define MAX 50
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
}				t_params;

int		ft_key_press(int keycode);
void	draw(t_params *p);
int		ft_mouse_press(int keycode, int x, int y);
int		ft_mouse_release(int button);
int		ft_mouse_move(int x, int y);
double	map(int val, double start_x, double zoom);
t_params	*ft_getter(t_params *p);
#endif