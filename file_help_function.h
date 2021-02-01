
#ifndef FILE_HELP_FUNCTION_H
# define FILE_HELP_FUNCTION_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>

void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char *s, int fd);
void			ft_putnbr_fd(int n, int fd);
unsigned int	ft_strlen(void *str);
int				ft_check_isspace(char s);
float			ft_atoi_float(char **str);

#endif
