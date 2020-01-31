/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 21:31:14 by sid-bell          #+#    #+#             */
/*   Updated: 2020/01/31 21:43:56 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	mandelbrot(t_params *p, int x, int y)
{
	t_complex	c;
	t_complex	z;
	double		tmp;
	int			i;
	double		val;

	c.a = p->julia.a;
	c.b = p->julia.b;
	if (p->fractal == MANDELBROT)
	{
		c.a = map(x, p->start_x, p->zoom);
		c.b = map(y, p->start_y, p->zoom);
	}
	z.a = map(x, p->start_x, p->zoom);
	z.b = map(y, p->start_y, p->zoom);
	i = 0;
	while (i < MAX)
	{
		tmp = z.a * z.a - z.b * z.b + c.a;
		z.b = 2 * z.a * z.b + c.b;
		z.a = tmp;
		val = z.a * z.a + z.b * z.b;
		if (val > 4)
			break ;
		i++;
	}
	if (i == MAX)
		mlx_pixel_put(p->mlx_ptr, p->win_ptr, x, y, GREEN);
}

void	draw(t_params *p)
{
	int x;
	int y;

	mlx_clear_window(p->mlx_ptr, p->win_ptr);
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			mandelbrot(p, x, y);
			x++;
		}
		y++;
	}
}
