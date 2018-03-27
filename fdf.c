/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agundry <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/26 13:07:18 by agundry           #+#    #+#             */
/*   Updated: 2018/03/26 21:00:59 by agundry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

int	verify_map(t_fdf *fdf)
{
	char	*line;
	size_t	i;
	size_t	lsiz;
	size_t	lsizprev;

	i = 0;
	lsiz = 0;
	lsizprev = 0;
	while (fdf->msiz += lsiz && get_next_line(fdf->fd, &line))
	{
		lsiz = 0;
		fdf->in = ft_strjoin(fdf->in, line);
		while (line[i])
		{
			if (ft_isdigit(line[i]) && ++lsiz)
				while (ft_isdigit(line[i]) && ++i)
					;
			if (line[++i] == '\0')
			{
				if (lsizprev != lsiz && lsizprev != 0)
					return (-1);
				break;
			}
		}
		lsizprev = lsiz;
		free(line);
	}
	fdf->in = ft_strjoin(fdf->in, "\0");
	fdf->w = lsiz;
	return (1);
}

int	get_map(t_fdf *fdf)
{
	char	*c;
	char	*num;
	t_pt	*m;
	int		y;

	y = 0;
	c = fdf->in;////
	if (!(verify_map(fdf))
			&& !(fdf->map = (t_pt*)malloc((sizeof(t_pt) * fdf->msiz) + 1))) /////
		return (-1);
	m = fdf->map;
	while (c - fdf->in < (long)fdf->msiz)
	{
		if (ft_isdigit(*c))
		{
			while (ft_isdigit(*c))
				num = ft_strjoin(num, c++);
			m->z = ft_atoi(num);
			m++->y = y++/fdf->w;
		}
		if (++c == '\0')
			break;
	}
	return (1);
}

int	drawpts(t_fdf *fdf)
{
//	t_pt	*map;

//	map = fdf->map;
//	while (map - fdf->map <= (long)fdf->msiz)
	mlx_pixel_put(fdf->mlx, fdf->win, fdf->map->x, fdf->map->y, 0xFFFFFF);
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
	//open map
	//parse, store, error check map (stored as list of point strux)
	//new mlx window /handlers
	//while (user hasnt pressed esc) { // mlx_loop !!!1
		//listen for usr input, determine rot
		//apply rotation fxns to translate x, y, z
	fdf_draw(&fdf);
		//if fdf->d draw points, draw lines, colorize } //make draw daddy first //
	//close, exit
}
