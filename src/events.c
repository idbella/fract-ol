/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 21:32:39 by sid-bell          #+#    #+#             */
/*   Updated: 2020/08/01 02:03:37 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		ft_key_press(int keycode)
{
	t_params *p;

	p = ft_getter(0);
	if (keycode == 32)
	{
		if (++p->fractal > BURNING)
			p->fractal = MANDELBROT;
		draw(p);
	}
	if (keycode == 61)
	{
		p->max++;
		draw(p);
	}
	if (keycode == 45)
	{
		p->max--;
		draw(p);
	}
	if (keycode == 115)
	{
		p->stop *= -1;
	}
	return (0);
}

int		ft_mouse_press(int keycode, int x, int y)
{
	t_params	*params;

	params = ft_getter(NULL);
	if (x <= 0 || y <= 0)
		return (0);
	
	if (keycode == 1 && x < WIDTH - 100)
	{
		params->step = 2;
		params->x = x;
		params->y = y;
		params->mouse_down = 1;
	}
	if (keycode == 4 || keycode == 5)
	{
		if (keycode == 4)
			params->zoom *= 1.04;
		if (keycode == 5)
			params->zoom *= 0.96;
		draw(params);
	}
	t_list *lst;
	t_button *btn;
	lst = ft_getter(0)->buttons;
	while (lst)
	{
		btn = lst->content;
		if ((x > btn->x && x < btn->x + btn->width) &&
			(y > btn->y && y < btn->y + btn->height))
		{
			btn->callback(btn);
		}
		lst = lst->next;
	}
	return (0);
}

int		ft_mouse_release(int button)
{
	t_params *params;

	params = ft_getter(NULL);
	if (button == 1 && params->mouse_down)
	{
		params->mouse_down = 0;
		params->step = 1;
		draw(params);
	}
	return (0);
}

int		ft_mouse_move(int x, int y)
{
	t_params	*p;
	int			dx;
	int			dy;

	p = ft_getter(NULL);
	//printf("x = %f\n", map(x, p->start_x, p->zoom));
	if (p->mouse_down)
	{
		dx = p->x - x;
		dy = p->y - y;
		p->start_x += map(dx, p->start_x, p->zoom) - p->start_x;
		p->start_y += map(dy, p->start_y, p->zoom) - p->start_y;
		draw(p);
		p->x = x;
		p->y = y;
	}
	else if (p->fractal == JULIA && p->stop < 0)
	{
		if (x < WIDTH - 100)
		{
			p->julia.a = map(x, p->start_x, p->zoom);
			p->julia.b = map(y, p->start_y, p->zoom);
			draw(p);
		}
	}
	t_list *lst;
	t_button *btn;
	lst = ft_getter(0)->buttons;
	char d = 0;
	while (lst)
	{
		btn = lst->content;
		if ((x > btn->x && x < btn->x + btn->width) &&
			(y > btn->y && y < btn->y + btn->height))
		{
			btn->highlighted = 1;
			d = 1;
		}
		else if (btn->highlighted)
		{
			btn->highlighted = 0;
			d = 1;
		}
		lst = lst->next;
	}
	if (d)
		ft_buttons();
	return (0);
}
