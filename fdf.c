/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agundry <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/26 13:07:18 by agundry           #+#    #+#             */
/*   Updated: 2018/04/16 14:13:10 by agundry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	verify_map(t_fdf *fdf) //check file existence, etc.
{
	char	*line;
	size_t	i;
	size_t	lsiz;
	size_t	lsizprev;

	lsiz = 0;
	i = 0;
	lsizprev = 0;
	if (!(fdf->in = (char*)malloc(sizeof(char) * 1)))
		return (-1);
	while (get_next_line(fdf->fd, &line))
	{
		fdf->in = ft_strjoin(fdf->in, line);
		fdf->in = ft_strjoin(fdf->in, "\n");
		while (i < ft_strlen(line))
		{
			if (ft_isdigit(line[i]) && ++lsiz)
				while (ft_isdigit(line[i]) && ++i)
					;
			if (line[++i] == '\0')
				if (lsizprev != lsiz && lsizprev != 0)
					return (-1);
		}
		if (fdf->w == 0)
			fdf->w = lsiz;
		lsizprev = lsiz;
		fdf->msiz += lsiz;
		free(line);
		lsiz = 0;
		i = 0;
	}
	return (1);
}

int	get_map(t_fdf *fdf)
{
	char	*c;
	char	*num;
	int		*m;

	if (!(verify_map(fdf)) || !(fdf->map = (int*)malloc((sizeof(int) * fdf->msiz)))) /////
		return (-1);
	c = fdf->in;
	m = fdf->map;
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

int	drawpts(t_fdf *fdf)
{
	int		*m;
	size_t	s;

	m = fdf->map;
	s = 0;
	if (!(fdf->pts = (t_pt*)malloc(sizeof(t_pt) * fdf->msiz)))
		return (-1);
	while (s < fdf->msiz)
	{
		fdf->xmod = 10 + (s % fdf->w) * 20; //replace 5 with scale factor var //macro?!?! //expensive!!!
		fdf->ymod = 10 + (s / fdf->w) * 20; //refactor these
		mlx_pixel_put(fdf->mlx, fdf->win, fdf->pts[s].x, fdf->pts[s].y, 0xFFFFFF + (50 * m[s]));
		++s;
	}
	return (1);
}

void	midpoint(t_pt *p1, t_pt *p2, t_fdf *fdf) //modify to take in two endpoint strux and fdf struk
{
	int	d;
	int	x;
	int	y;
	int	dx;
	int	dy;

	dx = p2->x - p1->x;
	dy = p2->y - p1->y;
	d = dy - (dx / 2);
	x = p1->x;
	y = p1->y;
	while (x++ < p2->x) //consider scaling, might be a good time to redefine pts
		//
	{
		d += (d < 0) ? (d + dy) : (dy - dx);
		y += (d < 0) ? 0 : 1;
		mlx_pixel_put(fdf->mlx, fdf->win, (x * 20), (y * 20), 0xFFFFFF + (50 * p1->z));
	}
}

int drawlines(t_fdf *fdf)
{
	int		*map;
	size_t	s;
	t_pt	p1;
	t_pt	p2;

	s = 0;
	map = fdf->map;
	while (s < fdf->msiz)
	{
		//load p1
		p1.x = s % fdf->w;
		p1.y = s / fdf->w;
		p1.z = map[s];
		//make fxn to load p2? do here before each if or within?
		p2.x = (s - fdf->w) % fdf->w;
		p2.y = (s - fdf->w) / fdf->w;
		p2.z = map[s - fdf->w];
		if (map[s - fdf->w])
			midpoint(&p1, &p2, fdf);
		p2.x = (s - 1) % fdf->w;
		p2.y = (s - 1) / fdf->w;
		p2.z = map[s - 1];
		if (map[s - 1])
			midpoint(&p1, &p2, fdf);
		p2.x = (s + 1) % fdf->w;
		p2.y = (s + 1) / fdf->w;
		p2.z = map[s + 1];
		if (map[s + 1])
			midpoint(&p1, &p2, fdf);
		p2.x = (s + fdf->w) % fdf->w;
		p2.y = (s + fdf->w) / fdf->w;
		p2.z = map[s + fdf->w];
		if (map[s + fdf->w])
			midpoint(&p1, &p2, fdf);
		s++;
	}
	return (1);
}

int	fdf_draw(t_fdf *fdf)
{
	if (!drawpts(fdf) || !drawlines(fdf))
		return (-1);
	return (1);
}

int	main(int ac, char **av)
{
	t_fdf	fdf;

	ft_bzero(&fdf, sizeof(fdf));
	if (ac != 2 || !(strstr(av[1], ".fdf")) || !(fdf.fd = open(av[1], O_RDONLY))
			|| !(get_map(&fdf))) /////
		return (0);
	fdf.mlx = mlx_init();
	fdf.win = mlx_new_window(fdf.mlx, 1000, 1000, "dad");//
//	mlx_loop(fdf.mlx);
//	mlx_loop_hook(fdf.mlx, (&fdf_draw)(&fdf));
	//open map
	//parse, store, error check map (stored as list of point strux)
	//new mlx window /handlers
	//while (user hasnt pressed esc) { // mlx_loop !!!1
		//listen for usr input, determine rot
		//apply rotation fxns to translate x, y, z
	fdf_draw(&fdf);
	mlx_loop(fdf.mlx);
		//if fdf->d draw points, draw lines, colorize } //make draw daddy first //
	//close, exit
}
