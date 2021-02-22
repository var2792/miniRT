
#include "libft.h"

int	ft_check_isspace(char s)
{
	if (s == '\t' || s == 32)
		return (1);
	return (0);
}
float		ft_atoi_float(char **str)
{
	float	num;
	float	n;
	int		m;
	int		f;
	int		dec;

	num = 0;
	m = 1;
	f = 0;
	dec = 1;
	while (ft_check_isspace(**str) && **str != '\0')
		(*str)++;
	if (**str == '-' || **str == '+')
	{
		if (**str == '-')
			m = -1;
		(*str)++;
	}
	while ((**str > 47 && **str < 58) && **str)
	{
		if (f)
		{
			dec *= 10;
			n = (**str - 48);
			num = num + m * n / dec;
		}
		else
			num = num * 10 + m * (**str - 48);
		(*str)++;
		if (**str == '.')
		{
			f = 1;
			(*str)++;
		}
	}
	num = round(num * dec) / dec;
	return (num);
}
