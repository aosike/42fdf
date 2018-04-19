/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agundry <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/26 13:16:35 by agundry           #+#    #+#             */
/*   Updated: 2018/04/19 14:19:56 by agundry          ###   ########.fr       */
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
	int			x; //make floats?
	int			y;
	int			z;
}				t_pt;

typedef struct	s_fdf
{
	int			*map; //map can just be an array of z vals?
	t_pt		*pts; //
	size_t		msiz;
	int			w;
	int			h;
	char		*in;
	char		*data;
	int			fd;
	int			xmod;
	int			ymod;
	bool		d;
	int			bpp;
	int			endian;
	int			size_line;
	void		*mlx;
	void		*win;
	void		*img;

}				t_fdf;

static void	put_pixel(t_fdf *f, int x, int y, int c);
void		put_map(t_fdf *f);
static void	fill_img(t_fdf *f);
static void	draw(t_fdf *f);
int			key_hook(t_fdf *f);
int			expose_hook(t_fdf *f);
int			load_pts(t_fdf *f);
int			verify_map(t_fdf *fdf);
int			get_map(t_fdf *fdf);
void		draw_line(t_pt *p1, t_pt *p2, t_fdf *fdf, int v);
int			main(int ac, char **av);
#endif
