/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 21:31:14 by sid-bell          #+#    #+#             */
/*   Updated: 2020/08/01 03:27:24 by sid-bell         ###   ########.fr       */
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

void	ft_putpixel(int x, int y, int clr)
{
	t_params *p = ft_getter(0);
	mlx_pixel_put(p->mlx_ptr, p->win_ptr, x, y, clr);
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
		ft_putpixel(x, y, RED);
}



void	ft_drawbox(int width, int height, int x, int y, int clr);
void	ft_string(t_button *btn);
void	draw(t_params *p)
{
	int y;
	int x;

	mlx_clear_window(p->mlx_ptr, p->win_ptr);
	y = 0;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH - 100)
		{
			mandelbrot(p, x, y);
			x += p->step;
		}
		y += p->step;
	}
	ft_drawbox(4,HEIGHT, WIDTH - 100, 0, GREEN);
	ft_drawbox(100,30, WIDTH - 100, HEIGHT-30, GREEN);
	ft_buttons();
	
	mlx_string_put(p->mlx_ptr, p->win_ptr, WIDTH - 70, 25, RED, "fractal");
	mlx_string_put(p->mlx_ptr, p->win_ptr, WIDTH - 60, 145, RED, "zoom");
	mlx_string_put(p->mlx_ptr, p->win_ptr, WIDTH - 80, 230, RED, "iterations");
	mlx_string_put(p->mlx_ptr, p->win_ptr, WIDTH - 55, 280, RED, ft_itoa(p->max));
	mlx_string_put(p->mlx_ptr, p->win_ptr, WIDTH - 70, HEIGHT - 10, 0, "sid-bell");
}

void	ft_buttons()
{
	t_list *lst;
	t_button *btn;
	lst = ft_getter(0)->buttons;
	while (lst)
	{
		btn = lst->content;
		int clr;
		int width = btn->width;
		int x = btn->x;
		clr = btn->highlighted ? btn->highlightcolor : btn->color;
		if (btn->value == ft_getter(0)->fractal)
		{
			clr = btn->highlightcolor;
			width = 90;
			x = WIDTH - 100;
		}
		ft_drawbox(width, btn->height, x, btn->y, clr);
		ft_string(btn);
		lst = lst->next;
	}
}

void	ft_string(t_button *btn)
{
	int x;
	int y;
	t_params *p;

	p = ft_getter(0);
	x = btn->x + btn->width/2 - (ft_strlen(btn->caption) * 6)/2;
	y = btn->y + btn->height/2 + 4;
	mlx_string_put(p->mlx_ptr, p->win_ptr,x , y, btn->textcolor, btn->caption);
}

void	ft_drawbox(int width, int height, int x, int y, int clr)
{
	int x1;
	int y1;
	int y0;

	x1 = x + width;
	while (x < x1)
	{
		y0 = y + height;
		y1 = y;
		while (y1 < y0)
		{
			ft_putpixel(x, y1, clr);
			y1++;
		}
		x++;
	}
}
