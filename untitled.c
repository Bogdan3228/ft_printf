/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgres <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 14:18:13 by bgres             #+#    #+#             */
/*   Updated: 2018/01/24 14:18:20 by bgres            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stdio.h>
#include <unistd.h>
#include "libft/libft.h"
#include "ft_printf.h"
int parsing_two(t_param *param, char *txt);
void	parsing_three(t_param *param, char *txt, char *f, int * i);
void	check_p_end(t_param *param, char *txt, int *i);

void parsing_one(char *txt);

int		ft_pf_atoi(char *a, int i)
{
	unsigned long	result;
	int				g;

	result = 0;
	g = 0;
	while (g < i)
	{
		if ((result > 922337203685477580 || (result == 922337203685477580
			&& (*a - '0') > 7)))
			return (-1);
			return (0);
		result = (result * 10) + (*a - '0');
		a++;
		g++;
	}
	return ((int)(result));
}


int main (int ac, char **argv)
{
	int i = 0;
	int g = -55;
	char	a[10] = "1111111\0";
	parsing_one(argv[1]);
	return 0;
}
char	*ft_strndup(const char *src, int n)
{
	size_t	i;
	char	*c;

	i = 0;
	while (src[i] != '\0' && (int)i < n)
		i++;
	c = (char *)malloc(sizeof(char) * i + 1);
	if (!c)
		return (NULL);
	i = 0;
	while (src[i] != '\0' && (int)i < n)
	{
		c[i] = src[i];
		i++;
	}
	c[i] = '\0';
	return (c);
}


t_param		*prmcrt()
{
	t_param *a;
	a = (t_param*)malloc(sizeof(t_param));
	a->next = NULL;
	return (a);
}
void ft_fprint(char *fmt, ...)
{
	va_list		ap;

	va_start(ap, fmt);

}
void setflag(t_param *param, char f)
{

}
void	setflag_dva(t_param *param, char * txt, int j, int flag)
{
	if (flag == 1)
		param->wdth = ft_pf_atoi(txt, j);
	else if (flag == 2)
		param->prcsn = ft_pf_atoi(txt, j);
}
void parsing_one(char *txt)
{
	int		*i;
	int		j;
	int 	a;
	int		g;

	g = 0;
	a = 0;
	i  =&a;
	j = 0;
	t_param *head;
	t_param *param;
	param = prmcrt();

	head = param;
	while(txt[*i] != '\0')
	{
	
		if (txt[*i] == '%')
		{
			*i = *i + parsing_two(param, &txt[*i]);
		
	
		}
		else
		{
			while(txt[*i + j] != '\0' && txt[*i + j] != '%')
				j++;
			write(1,(txt + *i), j);
			*i = *i + j;
			j = 0;
		}
		
	}	
}
int		parsing_two(t_param *param, char *txt)
{
		//printf("i v parsing_two =%i\n",*i );
	char	*flag;
	char	*lm;
	int		i;
	int 	j;

	i = 1;
	j = 0;
	flag = " +-0#\0";
	lm = "hljz\0";
	parsing_three(param, txt, flag, &i);
	while (txt[i + j] != '\0' && ft_isdigit(txt[i]))
		j++;
	if (j > 0)
		setflag_dva(param, &txt[i], j, 1);
	i = i + j;
	j = 0;
	if (txt[i] == '.')
	{
		param->tchka = 1;
		i++;
	}
	while (txt[i + j] != '\0' && ft_isdigit(txt[i]))
		j++;
	if (j > 0)
		setflag_dva(param, &txt[i], j, 2);
	i = i + j;
	j = 0;
	parsing_three(param, txt, lm, &i);
	check_p_end(param, txt, &i);
	return (i );	
}
void	check_p_end(t_param *param, char *txt, int *i)
{
	char	*f;
	int		j;
	int		a;
	f = "sSpdDioOuUxXcC\0";
	a = 0;
	j = 0;
	while (txt[*i] != '\0' && f[j] != '\0' && a == 0)
	{
		if (txt[*i] == f[j])
		{
		
			setflag(param, f[j]);
			a++;
			*i = *i + 1;
		}
		else
			j++;
	}
	if (a == 0)
	{
		*i = *i + 1;
		param->ror = 1;
	}

	param->next = prmcrt();
	param = param->next;
}

void	parsing_three(t_param *param, char *txt, char *f, int * i)
{
	int		j;
	
	j = 0;
	while (txt[*i] != '\0' && f[j] != '\0')
	{

		if (txt[*i] == f[j])
		{
			if ((txt[*i] == 'h' && txt[*i + 1] =='h') || (txt[*i] == 'l' && txt[*i + 1] =='l'))
			{
				setflag(param, txt[*i] - 32);
				*i = *i + 2;
			} 
			else
			{
			setflag(param, f[j]);
			j = 0;
			*i = *i + 1;
			}
		}
		else
			j++;
	}
}
