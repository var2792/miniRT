#ifndef TYPE_DEF_H
# define TYPE_DEF_H

# include "libft/libft.h"
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <time.h>

typedef struct	s_my_mlx
{
	void		*ptr;
	void		*win;
}				t_my_mlx;

typedef struct	s_data {
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_data;

typedef struct	s_vector
{
	float	x;
	float	y;
	float	z;
}				t_vector;

typedef struct	s_resplution
{
	unsigned int	x;
	unsigned int	y;
	int				is;
}				t_resplution;

typedef struct	s_amblig
{
	float			rat;
	t_vector		cl;
	int				is;
}				t_amblig;

typedef struct	s_camera
{
	t_vector		cd;
	t_vector		nm;
	int				fov;
}				t_camera;

typedef struct	s_light
{
	t_vector		cd;
	float			br;
	t_vector		cl;
}				t_light;

typedef struct	s_sphere
{
	t_vector	cd;
	float		d;
	t_vector	cl;
	int			is;
}				t_sphere;

typedef struct	s_plane
{
	t_vector	cd;
	t_vector	nm;
	t_vector	cl;
	int			is;
}				t_plane;

typedef struct	s_square
{
	t_vector	cd;
	t_vector	nm;
	t_vector	cl;
	float		s;
	t_vector	ps[4];
	int			is;
}				t_square;

typedef struct	s_cylinder
{
	t_vector	cd;
	t_vector	nm;
	float		d;
	float		h;
	t_vector	cl;
	int			is;
}				t_cylinder;

typedef struct	s_triangle
{
	t_vector	cd1;
	t_vector	cd2;
	t_vector	cd3;
	t_vector	cl;
	t_vector	nm;
	int			is;
}				t_triangle;

typedef struct	s_scobjs
{
	t_resplution	r;
	t_amblig		a;
	t_list			*c;
	t_list			*l;
	t_list			*sp;
	t_list			*pl;
	t_list			*sq;
	t_list			*tr;
	t_list			*cy;
	t_vector		orig_cam;
}				t_scobjs;

typedef struct	s_scene
{
	t_vector	cdo;
	t_vector	cdv;
	t_vector	viewport;
	t_vector	*rotmat;
}				t_scene;

typedef struct	s_general
{
	t_my_mlx	mlx;
	t_data		img;
	t_scobjs	objs;
	t_scene		scene;
	t_vector	pix;
	float		cl;
	int			num_cam;
}				t_general;


#endif
