/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <idbellasaid@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 18:02:32 by sid-bell          #+#    #+#             */
/*   Updated: 2020/04/26 14:11:19 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

double	map(int val, double start_x, double zoom)
{
	return (((double)3*zoom) / WIDTH * val + start_x);
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
	params->step = 2;
	params->max = MAX;
	params->stop = -1;
	params->mouse_down = 0;
	params->start_x = -2;
	params->start_y = -1;
	params->step = 1;
	params->mlx_ptr = mlx_init();
	if (!params->mlx_ptr || !(params->win_ptr = mlx_new_window(params->mlx_ptr, WIDTH, HEIGHT, "fractal")))
	{
		ft_printf_fd(2, "unable to init mlx\n");
		exit(1);
	}
}

void	ft_usage(int argc, char **argv, t_params *p)
{
	char err;

	err = argc < 2;
	if (argc > 1)
	{
		if (ft_strequ(argv[1], "mandelbrot"))
			p->fractal = MANDELBROT;
		else if (ft_strequ(argv[1], "burnigship"))
			p->fractal = BURNING;
		else if (ft_strequ(argv[1], "julia"))
			p->fractal = JULIA;
		else
			err = 1;
	}
	if (err)
	{
		ft_printf_fd(2, "usage : ./fractol mandelbrot|burningship|julia\n");
		exit(1);
	}
}

int		main(int argc, char **argv)
{
	t_params	p;

	ft_usage(argc, argv, &p);
	ft_init(&p);
	ft_getter(&p);
	draw(&p);
	mlx_hook(p.win_ptr, 2, 1, &ft_key_press, NULL);
	mlx_hook(p.win_ptr, 4, 4, &ft_mouse_press, NULL);
	mlx_hook(p.win_ptr, 5, 8, &ft_mouse_release, NULL);
	mlx_hook(p.win_ptr, 6, 64, &ft_mouse_move, NULL);
	mlx_loop(p.mlx_ptr);
	return (0);
}
