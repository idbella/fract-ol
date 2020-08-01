/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sid-bell <sid-bell@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 18:02:32 by sid-bell          #+#    #+#             */
/*   Updated: 2020/08/01 03:29:32 by sid-bell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

double	map(int val, double start_x, double zoom)
{
	return (zoom / WIDTH * val + start_x);
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
	params->zoom = 3;
	params->step = 2;
	params->buttons = NULL;
	params->max = MAX;
	params->stop = -1;
	params->mouse_down = 0;
	params->start_x = -2;
	params->start_y = -1;
	params->step = 1;
	params->mlx_ptr = mlx_init();
	if (!params->mlx_ptr || !(params->win_ptr = mlx_new_window(params->mlx_ptr, WIDTH, HEIGHT, "fractal 1")))
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

void	ft_click(void *bt)
{
	t_params *p;
	t_button *btn;

	btn = bt;
	p = ft_getter(0);
	p->fractal = btn->value;
	draw(p);
}
t_button	*ft_addbtn(char *text, int y, int val);

void	ft_zoom(void *bt)
{
	t_params	*p;
	t_button	*btn;
	double		center;

	btn = bt;
	p = ft_getter(0);
	
	if (btn->value == -2)
	{
		double sx = p->zoom;
		center = sx * 1.04;
		center = center - sx;
		p->start_x -= center/2;
		double sy = p->zoom;
		center = sy * 1.04;
		center = center - sy;
		p->start_y -= center/2;
		p->zoom *= 1.04;
	}
	else if (btn->value == -1)
	{
		double sx = p->zoom;
		//printf("sx = %lf\n", sx);
		center = sx * 0.96;
		center = sx - center;
		p->start_x += center/2;
		//printf("sx = %lf\n", );
		double sy = p->zoom;
		center = sy * 0.96;
		center = sy - center;
		p->start_y += center/2;
		p->zoom *= 0.96;
	}
	else
	{
		p->zoom = 3;
		p->start_x = -2;
		p->start_y = -1;
	}
	draw(p);
}

void	ft_maxiter(void *bt)
{
	t_button	*btn;
	t_params	*p;

	btn = bt;
	p = ft_getter(0);
	if (btn->value == -1)
		p->max++;
	else
		p->max--;
	draw(p);
}

void	ft_btns()
{
	t_button *b;

	ft_addbtn("mandelbrot", 40, MANDELBROT);
	ft_addbtn("julia", 70, JULIA);
	ft_addbtn("burinigship", 100, BURNING);

	b = ft_addbtn("+", 160, -1);
	b->width = 20;
	b->x = WIDTH - 80;
	b->callback = ft_zoom;
	b = ft_addbtn("-", 160, -2);
	b->width = 20;
	b->x = WIDTH - 40;
	b->callback = ft_zoom;
	b = ft_addbtn("reset", 185, -3);
	b->width = 60;
	b->x = WIDTH - 80;
	b->callback = ft_zoom;

	b = ft_addbtn("+", 240, -1);
	b->width = 20;
	b->x = WIDTH - 80;
	b->callback = ft_maxiter;
	b = ft_addbtn("-", 240, -2);
	b->width = 20;
	b->x = WIDTH - 40;
	b->callback = ft_maxiter;
}

t_button	*ft_addbtn(char *text, int y, int val)
{
	t_button *btn;
	t_params *p;

	p = ft_getter(0);
	btn = ft_memalloc(sizeof(t_button));
	btn->caption = ft_strdup(text);
	btn->color = GREY;
	btn->textcolor = 0;
	btn->value = val;
	btn->width = 80;
	btn->height = 20;
	btn->highlightcolor = GREEN;
	btn->x = WIDTH - 90;
	btn->y = y;
	btn->highlighted = 0;
	btn->callback = ft_click;
	ft_lstadd(&p->buttons, ft_lstnew(btn, 0));
	return (btn);
}

int		main(int argc, char **argv)
{
	t_params	p;

	ft_usage(argc, argv, &p);
	ft_init(&p);
	ft_getter(&p);
	ft_btns();
	draw(&p);
	mlx_hook(p.win_ptr, 2, 1, &ft_key_press, NULL);
	mlx_hook(p.win_ptr, 4, 4, &ft_mouse_press, NULL);
	mlx_hook(p.win_ptr, 5, 8, &ft_mouse_release, NULL);
	mlx_hook(p.win_ptr, 6, 64, &ft_mouse_move, NULL);
	mlx_loop(p.mlx_ptr);
	return (0);
}
