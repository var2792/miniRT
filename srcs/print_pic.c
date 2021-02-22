#include "../incs/funct_def.h"

void	point_with_objs(t_general *gen)
{
		gen->scene.cdv = trans_pixv(*gen);
		gen->cl = -5;
		//printf("\nAA\n\n");
		if (gen->objs.sp != NULL)
			belong_to_sphere(gen, gen->objs.sp->content);
		gen->pix.z = 0;
		if (gen->objs.pl != NULL)
			belong_to_plane(gen, gen->objs.pl->content);
		gen->pix.z = 0;
		if (gen->objs.sq != NULL)
			belong_to_square(gen, gen->objs.sq->content);
		gen->pix.z = 0;
		if (gen->objs.tr != NULL)
			belong_to_triangle(gen, gen->objs.tr->content);
		gen->pix.z = 0;
		if (gen->objs.cy != NULL)
			belong_to_cylinder(gen, gen->objs.cy->content);
}

void	print_pic(t_general *gen, t_camera *cam)
{
	gen->scene = parse_put_canvas(gen->objs, cam);
	ft_write_xyz(&(gen->pix), 0, 0, 0);
	while (gen->pix.x < gen->objs.r.x)
	{
		while (gen->pix.y < gen->objs.r.y)
		{
			point_with_objs(gen);
			if (gen->cl >= 0)
				my_mlx_pixel_put(&(gen->img), gen->pix.x, gen->pix.y, (int)(gen->cl));
			else
				my_mlx_pixel_put(&(gen->img), gen->pix.x, gen->pix.y, 0);
			gen->pix.z = 0;
			gen->pix.y += 1;
		}
		gen->pix.y = 0;
		gen->pix.x += 1;
	}

	mlx_put_image_to_window(gen->mlx.ptr, gen->mlx.win, gen->img.img, 0, 0);
	printf("\nc.x = %f, c.y = %f, c.z = %f\n", cam->cd.x, cam->cd.y, cam->cd.z);
	//printf("c.n.x = %f, c.n.y = %f, c.n.z = %f,\n", gen->objs.c[gen->num_cam].nm.x, gen->objs.c[gen->num_cam].nm.y, gen->objs.c[gen->num_cam].nm.z);
}

void	start_create(t_general *gen)
{
	gen->mlx.ptr = mlx_init();
	gen->mlx.win = mlx_new_window(gen->mlx.ptr, gen->objs.r.x, gen->objs.r.y, "miniRT");
	gen->img.img = mlx_new_image(gen->mlx.ptr, gen->objs.r.x, gen->objs.r.y);
	gen->img.addr = mlx_get_data_addr(gen->img.img, &(gen->img.bits_per_pixel), &(gen->img.line_length), &(gen->img.endian));
	//printf("\nAA\n\n");

	print_pic(gen, gen->objs.c->content);


}
