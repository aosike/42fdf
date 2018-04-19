/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agundry <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/17 15:53:11 by agundry           #+#    #+#             */
/*   Updated: 2018/04/19 14:22:45 by agundry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	put_pixel(t_fdf *f, int x, int y, int c)
{
	int	r;
	int	g;
	int	b;

	r = (c & 0xFF0000) >> 16;
	g = (c & 0xFF00) >> 8;
	b = (c & 0xFF);
	if (x >= 0 && y >= 0 && x < 2000 && y <= 1000) //
	{
		f->data[(y * f->size_line) + (4 * x) + 2] = r;
		f->data[(y * f->size_line) + (4 * x) + 1] = g;
		f->data[(y * f->size_line) + (4 * x)] = b;
	}
}

void	draw_line(t_pt *p1, t_pt *p2, t_fdf *f, int v)
{
	float			x[3];
	float			y[2];
	unsigned int	c;

	x[1] = v == 1 ? p1->x : p1->y;
	y[0] = v == 1 ? p1->y : p1->x;
	x[2] = v == 1 ? p2->x : p2->y;
	y[1] = v == 1 ? p2->y : p1->y;
	x[0] = x[1];
	f->xmod = 50;
	f->ymod = 50;
	if (p1->z <= -255)
		c = 0x000000;
	else if (p1->z <= 0 || p2->z <= 0)
		c = 0x0000FF + p1->z;
	else if (p1->z <= 50)
		c = (0xFF - p1->z * 3) << 8;
	else if (p1->z <= 120)
		c = ((0x80 - p1->z) << 16) + (33 << 8);
	else
		c = 0xFFFFFF;
	while (x[0] < x[2])
	{
		put_pixel(f, x[0] + (f->xmod * x[0]) , y[0] + (((y[1] - y[0])
						* (x[0] - x[1])) / (x[2] - x[1])) + (f->ymod * y[0]), c);
		x[0] += 0.01;
	}
}

void	put_map(t_fdf *f)
{
	int		s;
	t_pt	*p1;
	t_pt	*p2;

	s = 0;
	while (s < (int)f->msiz)
	{
		if ((s - f->w) > 0)
		{
			p1 = (f->pts[s - f->w].y < f->pts[s].y) ? &f->pts[s - f->w] : &f->pts[s];
			p2 = (f->pts[s - f->w].y < f->pts[s].y) ? &f->pts[s] : &f->pts[s - f->w];
			draw_line(p1, p2, f, 0);
		}
		if (s / f->w == (s - 1) / f->w && s - 1 >= 0)
		{
			p1 = (f->pts[s - 1].y < f->pts[s].y) ? &f->pts[s - 1] : &f->pts[s];
			p2 = (f->pts[s - 1].y < f->pts[s].y) ? &f->pts[s] : &f->pts[s - 1];
			draw_line(p1, p2, f, 1);
		}
		++s;
	}
}

static void	fill_img(t_fdf *f)
{
	f->size_line = f->w * f->bpp;
	if (!(f->data = mlx_get_data_addr(f->img, &f->bpp, &f->size_line, &f->endian)))
		;//error out
	else
		put_map(f);
}

static void	draw(t_fdf *f)
{
	f->h = f->msiz / f->w;
	f->img = mlx_new_image(f->mlx, 2000, 2000);
	fill_img(f);
	mlx_put_image_to_window(f->mlx, f->win, f->img, 0, 0);
	mlx_destroy_image(f->mlx, f->img);
}

int	key_hook(t_fdf *f)
{
	draw(f);
	return (0);
}

int	expose_hook(t_fdf *f)
{
	draw(f);
	return (0);
}

int	load_pts(t_fdf *f)
{
	size_t	s;

	s = 0;
	if (!(f->pts = (t_pt*)malloc(sizeof(t_pt) * f->msiz)))
		return (-1);
	while (s < f->msiz)
	{
		f->pts[s].x = s % f->w;
		f->pts[s].y = s / f->w;
		f->pts[s].z = f->map[s];
		++s;
	}
	return (1);
}

int	verify_map(t_fdf *f) //woikin hee
{
	char    *line;
	size_t  i;
	size_t  lsiz;
	size_t  lsizprev;
	
	lsiz = 0;
	i = 0;
	lsizprev = 0;
	f->msiz = 0;
	if (!(f->in = (char*)malloc(sizeof(char) * 1)))
		return (-1);
	ft_bzero(f->in, sizeof(f->in));
	while (get_next_line(f->fd, &line))
	{
		f->in = ft_strjoin(f->in, line);
		f->in = ft_strjoin(f->in, "\n");
		while (i < ft_strlen(line))
		{
			if (ft_isdigit(line[i]) && ++lsiz)
				while (ft_isdigit(line[i]) && ++i)
					;
			if (line[++i] == '\0')
				if (lsizprev != lsiz && lsizprev != 0)
					return (-1);
		}
		f->w = lsiz;
		lsizprev = lsiz;
		f->msiz += lsiz;
		free(line);
		lsiz = 0;
		i = 0;
	}
	return (1);
}

int get_map(t_fdf *f) //also garbage
{
	char	*c;
	char	*num;
	int		*m;

	if (!(verify_map(f))
			|| !(f->map = (int*)malloc((sizeof(int) * f->msiz)))) /////
		return (-1);
	c = f->in;
	m = f->map;
	while (*c)
	{
		if (ft_isdigit(*c))
		{
			if (!(num = (char*)malloc(1)))
				return (-1);
			while (ft_isdigit(*c))
				num = ft_strjoin(num, c++);
			*m = ft_atoi(num);
			++m;
			free(num);
		}
		++c;
	}
	return (1);
}

int	main(int ac, char **av)
{
	t_fdf	f;
	if (ac != 2 || !(ft_strstr(av[1], ".fdf")) || !(f.fd = open(av[1], O_RDONLY))
			|| !(get_map(&f)) || !(load_pts(&f)) || !(f.mlx = mlx_init())
				|| !(f.win = mlx_new_window(f.mlx, 2000, 2000, "dad")))
		return (-1);//make each of these return an error cod
	mlx_hook(f.win, 3, 3, key_hook, &f); //ERROR HERE?!
	mlx_expose_hook(f.win, expose_hook, &f);
	mlx_loop(f.mlx);
	return (0);
}
