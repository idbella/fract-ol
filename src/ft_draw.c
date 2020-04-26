/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <idbellasaid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 21:31:14 by sid-bell          #+#    #+#             */
/*   Updated: 2020/04/26 14:16:27 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	preview(t_params *p, int x, int y)
{
	t_complex	c;
	t_complex	z;
	double		tmp;
	int			i;

	c.a = map(x, p->start_x, p->zoom);
	c.b = map(y, p->start_y, p->zoom);
	z.a = map(x, p->start_x, p->zoom);
	z.b = map(y, p->start_y, p->zoom);
	i = 0;
	while (i < p->max)
	{
		tmp = z.a * z.a - z.b * z.b + c.a;
		z.b = 2 * z.a * z.b + c.b;
		z.a = tmp;
		if (z.a * z.a + z.b * z.b > 4)
			break ;
		i++;
	}
	if (i == p->max)
		mlx_pixel_put(p->mlx_ptr, p->win_ptr, x, y, RED);
}

void	mandelbrot(t_params *p, int x, int y)
{
	double		tmp;
	int			i;

	p->c.a = p->julia.a;
	p->c.b = p->julia.b;
	if (p->fractal != JULIA)
	{
		p->c.a = map(x, p->start_x, p->zoom);
		p->c.b = map(y, p->start_y, p->zoom);
	}
	p->z.a = map(x, p->start_x, p->zoom);
	p->z.b = map(y, p->start_y, p->zoom);
	i = -1;
	while (++i < p->max)
	{
		tmp = p->z.a * p->z.a - p->z.b * p->z.b + p->c.a;
		p->z.b = 2 * p->z.a * p->z.b + p->c.b;
		if (p->fractal == BURNING)
			p->z.b = fabs(p->z.b);
		p->z.a = p->fractal == BURNING ? fabs(tmp) : tmp;
		if (p->z.a * p->z.a + p->z.b * p->z.b > 4)
			break ;
	}
	if (i == p->max)
		mlx_pixel_put(p->mlx_ptr, p->win_ptr, x, y, RED);
}

void	draw(t_params *p)
{
	int y;
	int x;

	mlx_clear_window(p->mlx_ptr, p->win_ptr);
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			mandelbrot(p, x, y);
			x += p->step;
		}
		y += p->step;
	}
}
