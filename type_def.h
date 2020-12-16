#ifndef TYPE_DEF_H
# define TYPE_DEF_H

# include <math.h>
# include <stdio.h>
# include <stdlib.h>

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
}				t_resplution;

typedef struct	s_amblig
{
	float			rat_amlig;
	t_vector		color;
	unsigned int	rgb_16;
}				t_amblig;

typedef struct	s_camera
{
	t_vector		coord;
	t_vector		normal;
	unsigned int	fov;
}				t_camera;

typedef struct	s_light
{
	t_vector		coord;
	float			brirat;
	t_vector		color;
	unsigned int	rgb_16;
}				t_light;

typedef struct	s_sphere
{
	t_vector	coord;
	float		diam;
	t_vector	color;
	unsigned int	rgb_16;
}				t_sphere;

typedef struct	s_plane
{
	t_vector	coord;
	t_vector	normal;
	t_vector	color;
	unsigned int	rgb_16;
}				t_plane;

typedef struct	s_square
{
	t_vector	coord;
	t_vector	normal;
	t_vector	color;
	float		size;
	unsigned int	rgb_16;
}				t_square;

typedef struct	s_cylinder
{
	t_vector	coord;
	t_vector	normal;
	float		diam;
	float		heig;
	t_vector	color;
	unsigned int	rgb_16;
}				t_cylinder;

typedef struct	s_triangle
{
	t_vector	coord_fir;
	t_vector	coord_sec;
	t_vector	coord_thi;
	t_vector	color;
	unsigned int	rgb_16;
}				t_triangle;

typedef struct	s_objscene
{
	t_resplution	r;
	t_amblig		a;
	t_camera		c;
	t_light			l;
	t_sphere		sp;
	t_plane			pl;
	t_square		sq;
	t_cylinder		cy;
	t_triangle		tr;
}				t_objscene;

typedef struct	s_canvas
{
	t_vector coord_0;
	t_vector coord_v;
	t_vector viewport;
}				t_canvas;

#endif
