/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fdf.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agundry <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/26 13:16:35 by agundry           #+#    #+#             */
/*   Updated: 2018/03/26 21:01:10 by agundry          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H
# include "libft/inc/libft.h"
# include "mlx/mlx.h"
# include <stdlib.h>
# include <stdbool.h>

typedef struct	s_pt
{
	int			x;
	int			y;
	int			z;
	int			c;
}				t_pt;

typedef struct	s_fdf
{
	t_pt		*map;
	size_t		msiz;
	size_t		w;
	char		*in;
	int			fd;
	bool		d;
	void		*mlx;
	void		*win;

}				t_fdf;

int	verify_map(t_fdf *fdf);
int get_map(t_fdf *fdf);
int drawpts(t_fdf *fdf);
int drawlines(t_fdf *fdf);
int fdf_draw(t_fdf *fdf);
int main(int ac, char **av);
#endif
