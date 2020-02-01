/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 18:02:32 by sid-bell          #+#    #+#             */
/*   Updated: 2020/02/01 21:47:09 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

double	map(int val, double start_x, double zoom)
{
	return (((double)4*zoom) / WIDTH * val + start_x);
}

t_params	*ft_getter(t_params *p)
{
	static t_params *pp;

	if (p)
		pp = p;
	return (pp);
}

void	ft_init(t_params *params)
{
	params->zoom = 1;
	params->max = MAX;
	params->mouse_down = 0;
	params->start_x = -2;
	params->start_y = -2;
	params->mlx_ptr = mlx_init();
	params->win_ptr = mlx_new_window(params->mlx_ptr, WIDTH, HEIGHT, "fractal");
}

int	main(int argc, char **argv)
{
	argc = 0;
	argv = 0;
	t_params	p;

	ft_getter(&p);
	ft_init(&p);
	
	p.fractal = MANDELBROT;
	draw(&p);
	mlx_hook(p.win_ptr, 2, 0, &ft_key_press, NULL);
	mlx_hook(p.win_ptr, 4, 0, &ft_mouse_press, NULL);
	mlx_hook(p.win_ptr, 6, 0, &ft_mouse_move, NULL);
	mlx_hook(p.win_ptr, 5, 0, &ft_mouse_release, NULL);
	mlx_loop(p.mlx_ptr);
	return (0);
}
