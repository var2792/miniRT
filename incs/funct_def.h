/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   funct_def.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tarneld <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/03/07 21:55:19 by tarneld           #+#    #+#             */
/*   Updated: 2021/03/07 22:37:28 by tarneld          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCT_DEF_H
# define FUNCT_DEF_H

# include "type_def.h"
# include "../mlx_linux/mlx.h"

char			*create_bmp_name(char *file);
int				errors_mes(int n, char **help);
void			save_pic(t_general *gen, t_camera *cam);
void			print_pic(t_general *gen, t_camera *cam);
int				press_keys(int key, t_general *gen);
void			show_null_file(t_general *gen, int sav);
int				parse_put_canvas(t_scene *scene, t_scobjs objs, t_camera *cam);
t_vector		ft_write_xyz(t_vector *vec, float x, float y, float z);
void			point_with_objs(t_general *gen);
void			my_mlx_pixel_put(t_data *data, int x, int y, int color);
t_vector		trans_pixv(t_general gen);
t_vector		mult_m_v(t_vector *mat, t_vector vec);
float			dot_prv(t_vector vec1, t_vector vec2);
t_vector		cross_prv(t_vector vec1, t_vector vec2);
t_vector		sum_vs(float t1, t_vector vec1, float t2, t_vector vec2);
float			len_vec(t_vector vec);
int				belong_to_sphere(t_general *gen, t_sphere *sp);
int				check_see_objs(t_general gen, t_vector ptr, int num_ob);
float			check_shadow(t_light num_l, int num_ob,
t_scobjs objects, t_vector p);
float			find_discr(t_vector vec1, t_vector vec2, float last, float *t1);
float			check_shadow_sp(t_light num_l, int num_sp,
t_scobjs objects, t_vector p);
unsigned int	rescolobj(t_vector cycl, t_vector sum, t_vector acl, float br);
int				belong_to_plane(t_general *gen, t_plane *pl);
float			check_shadow_pl(t_light num_l, int num_pl,
t_scobjs objects, t_vector p);
float			check_orient(t_vector normal, t_vector l,
t_vector cor_0, t_vector p);
float			perpend_to_plane(t_vector cd, t_vector nm, t_vector lig);
int				belong_to_square(t_general *gen, t_square *sq);
float			check_shadow_sq(t_light num_l, int num_sq,
t_scobjs objects, t_vector p);
int				point_in_square(t_square sq, t_vector p);
int				belong_to_triangle(t_general *gen, t_triangle *tr);
int				point_in_triangle(t_triangle tr, t_vector p);
float			check_shadow_tr(t_light num_l, int num_tr,
t_scobjs objects, t_vector p);
int				belong_to_cylinder(t_general *gen, t_cylinder *cy);
int				belong_to_cyhead0(t_general gen, t_cylinder cy,
t_vector *pcy, int fl);
int				belong_to_cyhead1(t_general gen, t_cylinder cy,
t_vector *pcy, int fl);
int				check_see_cy(t_general gen, t_vector ptr, int num_cy);
int				check_head_orient(t_vector pcy, t_cylinder cy, t_light num_l);
float			check_shadow_cy(t_light num_l, int num_cy,
t_scobjs objects, t_vector pt);
float			perpend_heads(t_cylinder cy, t_vector p, t_light num_l);
int				parse_file(t_scobjs *objs, char *argv);
int				sep_fl(float *num, char **line, int fl);
int				parse_resplution(char **line, t_scobjs *scene);
int				parse_ambient(char **line, t_scobjs *scene);
int				parse_camera(char **line, t_scobjs *scene);
int				parse_light(char **line, t_scobjs *scene);
int				parse_sphere(char **line, t_scobjs *scene);
int				parse_plane(char **line, t_scobjs *scene);
int				parse_square(char **line, t_scobjs *scene);
int				parse_cylinder(char **line, t_scobjs *scene);
int				parse_triangle(char **line, t_scobjs *scene);
int				check_color(t_vector color);
int				check_normal(t_vector normal);
void			free_gen(t_general *gen, int fl);
int				exit_program(t_general *gen);
int				bmp_image(t_general *gen);
void			find_point_sq(t_square sq, t_vector (*p)[]);
t_vector		*rotation_matrix(t_vector cam, t_vector orig, t_vector coord);
int				check_see_pl(t_general gen, t_vector ptr, int num_pl);
int				check_see_sp(t_general gen, t_vector ptr, int num_sp);
int				check_see_sq(t_general gen, t_vector ptr, int num_sq);
int				check_see_tr(t_general gen, t_vector ptr, int num_tr);

#endif
