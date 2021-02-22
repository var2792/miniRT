#include "../incs/funct_def.h"

char	*create_bmp_filename(char *file, int i)
{
	char		*filename;
	int			n;

	if (!(filename = malloc(sizeof(char) * (i + 5))))
		print_error_and_exit(-7);
	n = -1;
	while (++n <= i)
		*(filename + n) = *(file + n);
	*(unsigned int *)(filename + n) =
	*(const unsigned int *)(unsigned long)"bmp\0";
	return (filename);
}
