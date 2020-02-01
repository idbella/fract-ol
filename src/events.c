/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 21:32:39 by sid-bell          #+#    #+#             */
/*   Updated: 2020/02/01 21:49:22 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		ft_key_press(int keycode)
{
	t_params *p;

	printf("key = %d\n", keycode);
	p = ft_getter(0);
	if (keycode == 49)
	{
		p->fractal *= -1;
		draw(p);
	}
	if (keycode == 69)
	{
		p->max++;
		draw(p);
	}
	if (keycode == 78)
	{
		p->max--;
		draw(p);
	}
	return (0);
}

int		ft_mouse_press(int keycode, int x, int y)
{
	t_params	*params;

	params = ft_getter(NULL);
	if (x <= 0 || y <= 0)
		return (0);
	if (keycode == 1)
	{
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
	return (0);
}

int		ft_mouse_release(int button)
{
	t_params *params;

	params = ft_getter(NULL);
	if (button == 1)
		params->mouse_down = 0;
	return (0);
}

int		ft_mouse_move(int x, int y)
{
	t_params	*p;
	int			dx;
	int			dy;

	p = ft_getter(NULL);
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
	else if (p->fractal == JULIA)
	{
		p->julia.a = map(x, p->start_x, p->zoom);
		p->julia.b = map(y, p->start_y, p->zoom);
		draw(p);
	}
	return (0);
}
