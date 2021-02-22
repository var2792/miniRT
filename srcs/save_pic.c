#include "../incs/funct_def.h"

void	bitmap_file_header(t_general *gen, int padding_size, int fd)
{
	unsigned char	*file_header;
	int				file_size;

	if (!(file_header = ft_calloc(14, sizeof(unsigned char))))
	{
		errors_mes(7,0);
		return ;
	}
	file_size = 14 + 40
		+ (gen->img.bits_per_pixel / 8 * gen->objs.r.x + padding_size) * gen->objs.r.y;
	file_header[0] = (unsigned char)('B');
	file_header[1] = (unsigned char)('M');
	file_header[2] = (unsigned char)(file_size);
	file_header[3] = (unsigned char)(file_size >> 8);
	file_header[4] = (unsigned char)(file_size >> 16);
	file_header[5] = (unsigned char)(file_size >> 24);
	file_header[10] = (unsigned char)(14
		+ 40);
	write(fd, file_header, 14);
	free(file_header);
}

void	bitmap_info_header(t_general *gen, int fd)
{
	unsigned char	*info_header;

	if (!(info_header = ft_calloc(40, sizeof(unsigned char))))
	{
		errors_mes(7,0);
		return ;
	}
	info_header[0] = (unsigned char)(40);
	info_header[4] = (unsigned char)(gen->objs.r.x);
	info_header[5] = (unsigned char)(gen->objs.r.x >> 8);
	info_header[6] = (unsigned char)(gen->objs.r.x >> 16);
	info_header[7] = (unsigned char)(gen->objs.r.x >> 24);
	info_header[8] = (unsigned char)(gen->objs.r.y);
	info_header[9] = (unsigned char)(gen->objs.r.y >> 8);
	info_header[10] = (unsigned char)(gen->objs.r.y >> 16);
	info_header[11] = (unsigned char)(gen->objs.r.y >> 24);
	info_header[12] = (unsigned char)(1);
	info_header[14] = (unsigned char)(gen->img.bits_per_pixel);
	write(fd, info_header, 40);
	free(info_header);
}

int		bmp_image(t_general *gen)
{
	int				i;
	int				fd;
	int				padding_size;
	unsigned char	padding[3];

	i = gen->objs.r.y;
	ft_bzero(padding, 3);
	if (!(fd = open(gen->savename, O_CREAT | O_WRONLY | O_TRUNC, 0644)))
		return (errors_mes(7, 0));
	padding_size = (4 - (gen->objs.r.x * gen->img.bits_per_pixel / 8) % 4) % 4;
	bitmap_file_header(gen, padding_size, fd);
	bitmap_info_header(gen, fd);
	while (i >= 0)
	{
		write(fd, gen->img.addr + (i * gen->objs.r.x * gen->img.bits_per_pixel / 8), gen->img.line_length);
		write(fd, padding, padding_size);
		i--;
	}
	close(fd);
	return (0);
}

void	save_pic(t_general *gen, t_camera *cam)
{
	if (parse_put_canvas(&(gen->scene), gen->objs, cam))
		return ;
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
	bmp_image(gen);
	exit_program(gen);
	free_gen(gen, 1);
}

char	*create_bmp_name(char *file)
{
	char	*newname;
	int		n;
	int		i;

	n = ft_strilen(file);
	if ((newname = malloc(sizeof(char) * (n - 2 + 3))) == 0)
		return (0);
	i = -1;
	while (++i < n - 2)
		newname[i] = file[i];
	newname[i] = 'b';
	newname[++i] = 'm';
	newname[++i] = 'p';
	newname[++i] = '\0';
	return (newname);
}
