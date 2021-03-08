#ifndef FUNCT_DEF_H
# define FUNCT_DEF_H

# include "type_def.h"
# include "../mlx_linux/mlx.h"

//save_pic
int		bmp_image(t_general *gen);
void	save_pic(t_general *gen, t_camera *cam);
char	*create_bmp_name(char *file);
//sphere
float	find_discr(t_vector vec1, t_vector vec2, float rad, float *t1);
void	correct_color(t_vector *cl);
float		check_orient(t_vector normal, t_vector l, t_vector cor_0, t_vector p);
//main
int		exit_program(t_general *gen);
void	my_mlx_pixel_put(t_data *data, int x, int y, int color);
int		exit_program(t_general *gen);
//cylinder_utils
float		bright_cy(t_cylinder cy, t_light num_l, t_vector p, int fl);
unsigned int	rescolcy(t_vector cycl, t_vector sum, t_vector acl, float br);
int				shadow_cy(t_cylinder cy, t_light num_l, t_vector pt);
int		see_cy(t_general gen, t_cylinder cy, t_vector *p);
int		belong_cy2(t_general gen, t_cylinder cy, t_vector *p);
int		belong_cy(t_general gen, t_cylinder cy, t_vector *p); //cy
//cylinder_utils2
void	rot_cy_cord(t_general *gen, t_cylinder *cy, t_vector *new, t_vector *p);
void	rot_shadow_cy(t_light *num_l, t_cylinder *cy, t_vector *new, t_vector *pt);
//print_pic
void	show_null_file(t_general *gen, int sav);
void	point_with_objs(t_general *gen);
void	print_pic(t_general *gen, t_camera *cam);
//void	start_create(t_general *gen, int sav);
//key_press
void	free_gen(t_general *gen, int fl);
int	press_keys(int key, t_general *gen);
//error_mes
int errors_mes(int n, char **help);
//points_funs
void	find_point_sq(t_square sq, t_vector (*P)[]);
//PARSE_PUT_CANVAS
t_vector	*rotation_matrix(t_vector cam, t_vector orig, t_vector coord);
int			parse_put_canvas(t_scene *scene, t_scobjs objs, t_camera *c);//(t_general gen);//
t_vector	trans_pixv(t_general gen);
//utils
t_vector		ft_write_xyz(t_vector *vec, float x, float y, float z);
unsigned int	ft_colorvec_unsint(float br, t_vector vec);
unsigned int	rescolcy(t_vector cycl, t_vector sum, t_vector acl, float br);
//PARSE_FILE
int		parse_file(t_scobjs *objs, char *argv);
int		parse_resplution(char **line, t_scobjs *scene);
int		parse_ambient(char **line, t_scobjs *scene);
int		parse_camera(char **line, t_scobjs *scene);
int		parse_light(char **line, t_scobjs *scene);
int		parse_sphere(char **line, t_scobjs *scene);
int		parse_plane(char **line, t_scobjs *scene);
int		parse_square(char **line, t_scobjs *scene);
int		parse_cylinder(char **line, t_scobjs *scene);
int		parse_triangle(char **line, t_scobjs *scene);
int		sep_fl(float *num, char **line, int fl);

int	check_normal(t_vector normal);
int	check_color(t_vector color);
//OPERAT_VECS
t_vector	mult_m_v(t_vector *mat, t_vector vec);
float		dot_prv(t_vector vec1, t_vector vec2);
t_vector	cross_prv(t_vector vec1, t_vector vec2);
t_vector	sum_vs(float t1, t_vector vec1, float t2, t_vector vec2);
float		len_vec(t_vector vec);
//LIGHT_CHANGE
float	light_change_sp(t_general gen, t_vector p, t_sphere sp, int num_sp);
float	light_change_pl(t_general gen, t_vector p, t_plane pl, int num_pl);
float	light_change_sq(t_general gen, t_vector p, t_square sq, int num_sq);
float	light_change_tr(t_general gen, t_vector p, t_triangle tr, int num_tr);
float	light_change_cy(t_general gen, t_vector p, int num_cy, int fl);
//CHECK_SHADOWS
float		check_shadow(t_light num_l, int num_sp, t_scobjs objects, t_vector p);
float		check_shadow_sp(t_light num_l, int num_sp, t_scobjs objects, t_vector p);
float		check_shadow_pl(t_light num_l, int num_pl, t_scobjs objects, t_vector p);
float		check_shadow_sq(t_light num_l, int num_sq, t_scobjs objects, t_vector p);
float		check_shadow_tr(t_light num_l, int num_tr, t_scobjs objects, t_vector p);
float		check_shadow_cy(t_light num_l, int num_cy, t_scobjs objects, t_vector p);
float		check_orient(t_vector normal, t_vector l, t_vector cor_0, t_vector p);
//CHECK_SEE_OBJS
int		check_see_objs(t_general gen, t_vector ptr, int num_sp);
int		check_see_sp(t_general gen, t_vector ptr, int num_sp);
int		check_see_pl(t_general gen, t_vector ptr, int num_pl);
int		check_see_sq(t_general gen, t_vector ptr, int num_sq);
int		check_see_tr(t_general gen, t_vector ptr, int num_tr);
int		check_see_cy(t_general gen, t_vector ptr, int num_cy);
//BELONG_TO_OBJ
int		belong_to_sphere(t_general *gen, t_sphere *sp);
int		belong_to_plane(t_general *gen, t_plane *pl);
int		belong_to_square(t_general *gen, t_square *sq);
int		belong_to_triangle(t_general *gen, t_triangle *tr);
int		belong_to_cylinder(t_general *gen, t_cylinder *cy);

int		belong_to_cyhead0(t_general gen, t_cylinder cy, t_vector *pcy, int fl);
int		belong_to_cyhead1(t_general gen, t_cylinder cy, t_vector *pcy, int fl);
int		shadow_cyhead0(t_cylinder cy, t_vector pcy, t_light num_l);
int		shadow_cyhead1(t_cylinder cy, t_vector pcy, t_light num_l);
int		point_in_square(t_square sq, t_vector p);
int		point_in_triangle(t_triangle tr, t_vector p);

#endif
