/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_draw.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 21:31:14 by sid-bell          #+#    #+#             */
/*   Updated: 2020/02/01 21:50:14 by sid-bell         ###   ########.fr       */
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
	while (i < p->max)
	{
		tmp = z.a * z.a - z.b * z.b + c.a;
		z.b = 2 * z.a * z.b + c.b;
		z.a = tmp;
		val = z.a * z.a + z.b * z.b;
		if (val > 4)
			break ;
		i++;
	}
	if (i == p->max)
		mlx_pixel_put(p->mlx_ptr, p->win_ptr, x, y, GREEN);
	// else
	// 	mlx_pixel_put(p->mlx_ptr, p->win_ptr, x, y, GREY);
}

void	*ft_thr(void *ptr)
{
	int x;
	int y;
	t_params	*p;

	p = ft_getter(0);
	y = *(int *)ptr;
	x = 0;
	while (x < WIDTH)
	{
		mandelbrot(p, x, y);
		x++;
	}
	return (NULL);
}

void	draw(t_params *p)
{
	int y;
	//pthread_t th[HEIGHT];

	mlx_clear_window(p->mlx_ptr, p->win_ptr);
	y = 0;
	while (y < HEIGHT)
	{
		//pthread_create(&th[y], NULL, ft_thr, &y);
		ft_thr(&y);
		y++;
	}
	//y = 0;
	// while (y < HEIGHT)
	// {
	// 	pthread_join(th[y], NULL);
	// 	y++;
	// }
}
