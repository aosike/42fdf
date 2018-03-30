/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agundry <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/26 13:07:18 by agundry           #+#    #+#             */
/*   Updated: 2018/03/30 13:55:27 by agundry          ###   ########.fr       */
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
	//fdf->in = ft_strjoin(fdf->in, "\0");
	return (1);
}

int	get_map(t_fdf *fdf)
{
	char	*c;
	char	*num;
	t_pt	*m;
	int		y;

	y = 0;
	if (!(verify_map(fdf)) || !(fdf->map = (t_pt*)malloc((sizeof(t_pt) * fdf->msiz)))) /////
		return (-1);
	c = fdf->in;////
	m = fdf->map;
	while (*c) // - fdf->in < (long)fdf->msiz)
	{
		if (ft_isdigit(*c))
		{
			if (!(num = (char*)malloc(1)))
				return (-1);
			while (ft_isdigit(*c))
				num = ft_strjoin(num, c++);
			m->z = ft_atoi(num);
			m->x = (y % fdf->w);
			m->y = (y / fdf->w);
//			printf("%d,%d,%d\n", m->x, m->y, m->z);
			++m;
			++y;
			free(num);
		}
		++c;
	}
	return (1);
}

int	drawpts(t_fdf *fdf)
{
	t_pt	*map;
	size_t	s;
	int		xmod;
	int		ymod;

	map = fdf->map;
	s = 0;
	while (s < fdf->msiz)
	{
		printf("%d,%d,%d\n", map->x, map->y, map->z);
		xmod = (s % fdf->w) * 5; //replace 5 with scale factor var
		ymod = (s / fdf->w) * 5;
		mlx_pixel_put(fdf->mlx, fdf->win, map->x + xmod, map->y + ymod, 0xFFFFFF);
		++s;
		++map;
	}
	return (1);
}

int drawlines(t_fdf *fdf)
{
	t_fdf *dfd;
   
	dfd	= fdf;
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
	fdf.win = mlx_new_window(fdf.mlx, 500, 500, "dad");//
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
