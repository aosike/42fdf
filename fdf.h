/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agundry <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/26 13:16:35 by agundry           #+#    #+#             */
/*   Updated: 2018/04/16 14:13:04 by agundry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "libft/inc/libft.h"
# include "mlx/mlx.h"
# include <stdlib.h>
# include <stdbool.h>

typedef struct	s_pt //absolute x and y for pixel drawing
{
	int			x;
	int			y;
	int			z;
}				t_pt;

typedef struct	s_fdf
{
	int			*map; //map can just be an array of z vals?
	t_pt		*pts; //
	size_t		msiz;
	size_t		w;
	char		*in;
	int			fd;
	int			xmod;
	int			ymod;
	bool		d;
	void		*mlx;
	void		*win;

}				t_fdf;

void	midpoint(t_pt *p1, t_pt *p2, t_fdf *fdf);
int		verify_map(t_fdf *fdf);
int		get_map(t_fdf *fdf);
int		drawpts(t_fdf *fdf);
int		drawlines(t_fdf *fdf);
int		fdf_draw(t_fdf *fdf);
int		main(int ac, char **av);
#endif
