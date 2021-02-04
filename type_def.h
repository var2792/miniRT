#ifndef TYPE_DEF_H
# define TYPE_DEF_H

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

typedef struct  s_data {
    void        *img;
    char        *addr;
    int         bits_per_pixel;
    int         line_length;
    int         endian;
}               t_data;

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
	float			rat_amlig;
	t_vector		color;
}				t_amblig;

typedef struct	s_camera
{
	t_vector		coord;
	t_vector		normal;
	unsigned int	fov;
	int				is;
}				t_camera;

typedef struct	s_light
{
	t_vector		coord;
	float			brirat;
	t_vector		color;
	int				is;
}				t_light;

typedef struct	s_sphere
{
	t_vector	coord;
	float		diam;
	t_vector	color;
	int			is;
}				t_sphere;

typedef struct	s_plane
{
	t_vector	coord;
	t_vector	normal;
	t_vector	color;
	int			is;
}				t_plane;

typedef struct	s_square
{
	t_vector	coord;
	t_vector	normal;
	t_vector	color;
	float		size;
	t_vector	ps[4];
	int			is;
}				t_square;

typedef struct	s_cylinder
{
	t_vector	coord;
	t_vector	coord2;
	t_vector	normal;
	float		diam;
	float		heig;
	t_vector	color;
	int			is;
}				t_cylinder;

typedef struct	s_triangle
{
	t_vector	coord_fir;
	t_vector	coord_sec;
	t_vector	coord_thi;
	t_vector	color;
	t_vector	normal;
	int			is;
}				t_triangle;

typedef struct	s_objscene
{
	t_resplution	r;
	t_amblig		a;
	t_camera		c[50];
	t_light			l[50];
	t_sphere		sp[50];
	t_plane			pl[50];
	t_square		sq[50];
	t_cylinder		cy[50];
	t_triangle		tr[50];
	t_vector		orig_cam;
}				t_objscene;

typedef struct	s_scene
{
	t_vector	coord_0;
	t_vector	coord_v;
	t_vector	viewport;
	t_vector	*rotmat;
}				t_scene;

typedef struct	s_general
{
	t_my_mlx	mlx;
	t_data		img;
	t_objscene	objects;
	t_scene		scene;
	t_vector	pix;
	float		color;
	int			num_cam;
}				t_general;


#endif
