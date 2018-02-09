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
#include "libft.h"
#include "ft_printf.h"
#include <wchar.h>
#include <locale.h>
int parsing_two(t_param **param, char *txt, va_list vl);
void	parsing_three(t_param **param, char *txt, char *f, int * i);
void	check_p_end(t_param **param, char *txt, int *i, va_list ap);
void	prmssgn(t_param **a);
size_t	ft_get_len(size_t n, int b);
void	getd(t_param **list, char c, long long l, va_list vl);
int ft_printf(char *fmt, ...);
void	get_decimal(t_param **list, va_list vl);
char n = 's';
void parsing_one(char *txt, va_list ap, t_param *param);
void	itoa_printf(size_t n, t_param *a, int zn);
void	p_printf(size_t n, t_param *a);
size_t	get_p(va_list vl);
void	for_bits(wint_t ch, t_param *a, char **stroka);
void	p_utf(t_param *a, va_list vl);
void 	c_print(t_param *a, va_list vl, char t);
void	s_print(t_param *a, va_list vl);
void	s_print_for_unic(t_param *a, char *ch);
void	parsing_one_need(int **i, int *g, int *a, int *j);
void	parsing_one_write(char *txt, int *i, int j);
int	parsing_two_need(int *i, int *j, int flag);
void	check_p_end_need(t_param **param, va_list vl);
int	for_bits_need(wint_t ch);

int for_bits_check_mcm(int j);
char	*for_bits_check_m(wint_t ch, t_param *a);
char	*for_bits_check_mm(wint_t ch, t_param *a);
char	*for_bits_check_mmm(wint_t ch, t_param *a);
char	*for_bits_check_mmmm(wint_t ch, t_param *a);
void	s_print_for_unic(t_param *a, char *ch);
char	c_print_need(char o, va_list vl, t_param *a);
char	*for_digits(size_t n,  t_param *a);
void	p_printf_need(char **str, t_param *a, char *wdth);
void	p_printf_needd(char **str, t_param *a, char *wdth);
void	itoa_printf_need_dva(t_param *a, char **str, char *wdth, size_t w);
void	razraz(t_param *a, char **str, char *wdth);
void	razdva(t_param *a, char **str, char *wdth);


void	for_free_one(char **line, char *buf)
{
	char	*tmp;

	tmp = *line;
	*line = ft_strjoin(*line, buf);
	free(tmp);
}

void	for_free_two(char *buf, char **line)
{
	char	*tmp;

	tmp = *line;
	*line = ft_strjoin(buf, *line);
	free(tmp);
}
void	for_free_oned(char **line, char *buf)
{
	*line = ft_strjoin(*line, buf);
	free(buf);
}

void	for_free_twod(char *buf, char **line)
{
	*line = ft_strjoin(buf, *line);
	free(buf);
}
void	for_free_three(char **line, char *buf)
{
	char	*tmp;

	tmp = *line;
	*line = ft_strjoin(*line, buf);
	free(tmp);

}
void	for_free_three_d( char *buf, char **line)
{
	char	*tmp;

	tmp = *line;
	*line = ft_strjoin(buf, *line);
	free(tmp);


}
char	*ft_strndup(char *src, int n)
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
	if (ft_strequ("(null)", src))
			free(src);
	return (c);
}


t_param		*prmcrt()
{
	t_param *a;

	a = (t_param*)malloc(sizeof(t_param));
	a->n = n ;
	n = n + 1;
	prmssgn(&a);
	a->next = NULL;
	return (a);
}
void	prmssgn(t_param **a)
{
	(*a)->pls = -1;
	(*a)->mns = -1;
	(*a)->nol = -1;
	(*a)->ht = -1;
	(*a)->prbl = -1;
	(*a)->lm = -1;
	(*a)->type = -1;
	(*a)->tchka = -1;
	(*a)->ror = -1;
	(*a)->wdth = -1;
	(*a)->prcsn = -1;
}

int ft_printf(char *fmt, ...)
{
	va_list ap;
	t_param	*param;

	param = prmcrt();
	g_iter = 0;
	g_rr = 0;
	va_start(ap, fmt);
	parsing_one(fmt, ap, param);
	va_end(ap);
	if (g_rr < 0)
		g_iter = -1;
	return (g_iter);
}
void setflag(t_param **param, char f)
{
	if (f == '+')
		(*param)->pls = 1;
	else if (f == '-')
		(*param)->mns = 1;
	else if (f == '0')
		(*param)->nol = 1;
	else if (f == '#')
		(*param)->ht = 1;
	else if (f ==' ')
		(*param)->prbl = 1;
	else if (f == 'l' || f == 'L' || f == 'h' || f == 'H' || f == 'j' || f == 'z')
		(*param)->lm = f;
	else if (ft_strchr("sSpdDioOuUxXcC%", f))
		(*param)->type = f;
}
void	setflag_dva(t_param **param, char * txt, int j, int flag)
{
	j++;
	if (flag == 1)
		(*param)->wdth = ft_atoi(txt);
	else if (flag == 2)
		(*param)->prcsn = ft_atoi(txt);
}
void parsing_one(char *txt, va_list vl, t_param *param)
{
	int		*i;
	int		j;
	int 	a;
	int		g;

	parsing_one_need(&i, &g, &a, &j);
	while(txt[*i] != '\0')
	{
		if (txt[*i] == '%')
		{
			if (txt[*i + 1] == '%')
			{
				*i = *i + 1 + write(1, "%", 1);
				g_iter++;
			}
			else if (txt[*i + 1] == '\0')
				*i = *i + 1;
			else
				*i = *i + parsing_two(&param, &txt[*i], vl);
		}
		else
			parsing_one_write(txt, i, j);
	}	
}
void	parsing_one_need(int **i, int *g, int *a, int *j)
{
	*g = 0;
	*a = 0;
	*i = a;
	*j = 0;
}
void	parsing_one_write(char *txt, int *i, int j)
{
	while(txt[*i + j] != '\0' && txt[*i + j] != '%')
		j++;
	g_iter += write(1,(txt + *i), j);
	*i = *i + j;
}

int		parsing_two(t_param **param, char *txt, va_list vl)
{
	int		i;
	int 	j;

	j = parsing_two_need(&i, &j, 1);
	parsing_three(param, txt, " +-0#\0", &i);
	while (txt[i + j] != '\0' && ft_isdigit(txt[i + j]) == 1)
		j++;
	if (j > 0)
		setflag_dva(param, &txt[i], j, 1);
	j = parsing_two_need(&i, &j, 2);
	if (txt[i] == '.')
	{
		(*param)->tchka = 1;
		i++;
	}
	while (txt[i + j] != '\0' && ft_isdigit(txt[i + j]))
		j++;
	if (j > 0)
		setflag_dva(param, &txt[i], j, 2);
	j = parsing_two_need(&i, &j, 2);
	parsing_three(param, txt, "hljz\0", &i);
	check_p_end(param, txt, &i, vl);
	return (i);	
}

int parsing_two_need(int *i, int *j, int flag)
{
	if (flag == 1)
	{
		*i = 1;
		return (0);
	}
	else
	{
		*i = *i + *j;
		return(0);
	}
}


void	check_p_end(t_param **param, char *txt, int *i, va_list vl)
{
	char	*f;
	int		j;
	int		a;

	f = "sSpdDioOuUxXcC%\0";
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
		c_print(*param, vl, txt[*i]);
		*i = *i + 1;
		(*param)->ror = 1;
	}
	check_p_end_need(param, vl);
}
void	check_p_end_need(t_param **param, va_list vl)
{
	t_param	*tmp;

	if (ft_strchr("dDioOuUxX",(*param)->type) && (*param)->ror != 1)
		get_decimal(param, vl);
	else if ((*param)->type == 'p' && (*param)->ror != 1)
		p_printf(get_p(vl), *param);
	else if (ft_strchr("SC", (*param)->type) || (((*param)->lm == 'L' || (*param)->lm == 'l') && ft_strchr("sc", (*param)->type)))
		p_utf(*param, vl);
	else if ((*param)->type == 'c' || (*param)->type == '%')
		c_print(*param, vl, -42);
	else if ((*param)->type == 's')
		s_print(*param, vl);
	tmp = *param;
	(*param)->next = prmcrt();
	*param = (*param)->next;
	free(tmp);
}

int	for_bits_need(wint_t ch)
{
	int j;
	unsigned int i;

	j = 0;
	i = 0x80000000;
	while((i & ch) == 0 && i > 0)
	{
		j++;
		i = i / 2;
	}
	return(32 - j);
}
int	for_bits_check_mcm(int j)
{
	if (MB_CUR_MAX == 1 && j > 7)
	{
		g_rr = -1;
		return (6);
	}
	else if (MB_CUR_MAX ==2 && j> 11)
	{
		g_rr = -1;
		return(10);
	}
	else if (MB_CUR_MAX == 3 && j >16)
	{
		g_rr = -1;
		return(15);
	}
	else
		return (j);
}
char	*for_bits_check_m(wint_t ch, t_param *a)
{
	char	*buf;

	buf = ft_strnew(5);
	buf[0] = ch & 0xff;
	if (ch == 0 && (a->type == 'S' || a->type == 's'))
		return ("\0");
	else if (a->type == 'C' || a->type == 'c')
	{
		g_iter++;
		write(1, buf, 1);
	}
	else if(a->type == 's' || a->type == 'S')
	{
		if (a->prcsn - 1 >= 0 || a->tchka == -1)
		{
			a->prcsn -= 1;
			return (buf);
		}
	}
	free(buf);
	buf = ft_strnew(0);
	return (buf);
}
char	*for_bits_check_mm(wint_t ch, t_param *a)
{
	char	*buf;

	buf = ft_strnew(5);
	buf[1] = ((ch & 0x3f) | 0x80) & 0xffffffbf;
	buf[0] = (((0x00000fc0 & ch) >> 6) | 0x000000c0) & 0xfffffdf;
	if (ch == 0 && (a->type == 'S' || a->type == 's'))
		return ("\0");
	else if (a->type == 'C' || a->type == 'c')
	{
		g_iter = g_iter + 2;
		write(1, buf, 2);
	}
	else if (a->type == 's' || a->type =='S')
	{
		if (a->prcsn -2 >= 0 || a->tchka == -1)
		{
			a->prcsn -= 2;
			return (buf);
		}
	}
	free(buf);
	buf = ft_strnew(0);
	return (buf);
}

char	*for_bits_check_mmm(wint_t ch, t_param *a)
{
	char	*buf;

	buf = ft_strnew(5);
	buf[2] = ((ch & 0x0000003f) | 0x00000080) & 0xffffffbf;
	buf[1] = (((0x00000fc0 & ch) >> 6) | 0x00000080) & 0xffffffbf;
	buf[0] = ((0x0000f000 & ch) >> 12 | 0x000000e0) & 0xffffffef;
	if (ch == 0 && (a->type == 'S' || a->type == 's'))
		return ("\0");
	else if (a->type == 'C' || a->type == 'c')
	{
		g_iter = g_iter + 3;
		write(1, buf, 3);
	}
	else if (a->type == 's' || a->type =='S')
	{
		if (a->prcsn - 3 >= 0 || a->tchka == -1) 
		{
			a->prcsn -= 3;
			return (buf);
		}
	}
	free(buf);
	buf = ft_strnew(0);
	return (buf);
}

char	*for_bits_check_mmmm(wint_t ch, t_param *a)
{
	char	*buf;

	buf = ft_strnew(5);
	buf[3] = ((ch & 0x0000003f) | 0x00000080) & 0xffffffbf;
	buf[2] = (((0x00000fc0 & ch) >> 6) | 0x00000080) & 0xffffffbf;
	buf[1] = ((0x0003f000 & ch) >> 12 | 0x00000080) & 0xffffffbf;
	buf[0] = (((0x00007000 & ch)  >> 18) | 0x000000f0) & 0xfffffff7;
	if (ch == 0 && (a->type == 'S' || a->type == 's'))
		return ("\0");
	else if (a->type == 'C' || a->type == 'c')
	{
		g_iter = g_iter + 4;
		write(1, buf, 4);
	}
	else if (a->type == 's' || a->type =='S')
	{
		if (a->prcsn - 4 >= 0 || a->tchka == -1)
		{
			a->prcsn -= 4;
			return (buf);
		}
	}
	free(buf);
	buf = ft_strnew(0);
	return (buf);
}


void	for_bits(wint_t ch, t_param *a, char **stroka)
{
	int 			j;
	char	*tmp1;
	char 	*tmp2;

	if (ch == 0 && (a->type == 'c' || a->type == 'C'))
	{
		if (a->type == 'C')
		{
			g_iter = g_iter + write(1, "\0", 1);
			return ;
		}
	}
	j = for_bits_need(ch);
	j = for_bits_check_mcm(j);
	if (j <= 7 )
	{
		tmp1 = *stroka;
		tmp2 = for_bits_check_m(ch, a);
		*stroka = ft_strjoin(*stroka, tmp2);
		free(tmp1);
		free(tmp2);
	}
	else if (j <= 11)
	{
		tmp1 = *stroka;
		tmp2 = for_bits_check_mm(ch, a);
		*stroka = ft_strjoin(*stroka, tmp2);

		free(tmp1);
		free(tmp2);
	}
	else if (j <= 16)
	{
		tmp1 = *stroka;
		tmp2 = for_bits_check_mmm(ch, a);
		*stroka = ft_strjoin(*stroka, tmp2);
		free(tmp1);
		free(tmp2);
	}
	else
	{
		tmp1 = *stroka;
		tmp2 = for_bits_check_mmmm(ch, a);
		*stroka = ft_strjoin(*stroka, tmp2);
		free(tmp1);
		free(tmp2);
	}
}
void	p_utf(t_param *a, va_list vl)
{
	wchar_t	*s;
	wint_t	ch;
	char	*stroka;

	stroka = ft_strnew(1);
	if (a->type == 'C' || a->type =='c')
	{
		ch = va_arg(vl, wint_t);
		for_bits(ch, a, &stroka);
	}
	else
	{
		s = va_arg(vl, wchar_t *);
		if (s == NULL)
			g_iter = g_iter + write(1, "(null)", 6);
		else
		{
			while (*s != '\0' && (a->prcsn > 0 || a->tchka == -1))
			{
				for_bits(*s, a, &stroka) ;
				s++;
			}
			s_print_for_unic(a,stroka);
		}
	}
	
}

void	parsing_three(t_param **param, char *txt, char *f, int * i)
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
				if (txt[*i] != '\0') *i = *i + 2;
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

void	get_decimal(t_param **list, va_list vl)
{
	long long l;
	char  c;
	char  fl;

	if (ft_strchr("DOU", (*list)->type))
	{
 		(*list)->type += 32;
 		if ((*list)->lm == -1)
			(*list)->lm = 'l';
		else
  			(*list)->lm = 'L';
	}
	c = (*list)->type;
	fl = (*list)->lm;
	(c == 'i') ? (c = 'd') : 1;
	(c == 'd' && fl == -1) ? l = (int)va_arg(vl, int) : 1;
	(c == 'd' && fl == 'H') ? l = (signed char)va_arg(vl, int) : 1;
	(c == 'd' && fl =='h') ? l = (short)va_arg(vl, int) : 1;
	(c == 'd' && fl == 'l') ? l = va_arg(vl,  long int) : 1;
	(c == 'd' && fl == 'L') ? l = va_arg(vl, long long) : 1;
	(c == 'd' && fl == 'j') ? l = va_arg(vl, intmax_t) : 1;
	(c == 'd' && fl == 'z') ? l = va_arg(vl, size_t) : 1;
	getd(list, c, l, vl);
}

void getd(t_param **list, char c, long long l, va_list vl)
{
	char fl;
	size_t s;

	fl = (*list)->lm;
	s = 0;
	(c != 'd' && fl == -1) ? s = va_arg(vl, unsigned int) : 1;
	(c != 'd' && fl == 'H') ? s = (unsigned char)va_arg(vl, int) : 1;
	(c != 'd' && fl =='h') ? s = (unsigned short)va_arg(vl, int) : 1;
	(c != 'd' && fl == 'l') ? s = va_arg(vl, unsigned long) : 1;
	(c != 'd' && fl == 'L') ? s = va_arg(vl, unsigned long long) : 1;
	(c != 'd' && fl == 'j') ? s = va_arg(vl, uintmax_t) : 1;
	(c != 'd' && fl == 'z') ? s = va_arg(vl, size_t) : 1;
	if (c == 'd' && l < 0)
		itoa_printf(-1 * l, (*list), -1);
	else if (c == 'd' && l >= 0)
 		itoa_printf(l, (*list), 1);
	else if (c != 'd')
 		itoa_printf(s, (*list), 1);
 }


size_t	ft_get_len(size_t n, int b)
{
	size_t		i;

	i = 1;
	while (n /= b)
		i++;
	return (i);
}

char	*ft_stranew(size_t size, char *aa)
{
	char	*a;
	size_t	i;
	i = 0;
	a = (char *)ft_memalloc(size + 1);
	while (i < size)
	{
		a[i] = aa[0];
		i++;
	}
	return (a);
}

size_t	get_p(va_list vl)
{
	size_t	s;
	s = va_arg(vl, unsigned long);
	return(s);
}

void	s_print_for_unic(t_param *a, char *ch)
{
	char	*wdth;
	
	if (a->nol == 1 )
		wdth = "0";
	else
		wdth = " ";
	if ((int)ft_strlen(ch) < a->wdth)
	{	
		if (a->mns == 1)
			for_free_three(&ch,ft_stranew(a->wdth - (int)ft_strlen(ch), wdth));
		else
			for_free_three_d(ft_stranew(a->wdth - (int)ft_strlen(ch), wdth), &ch);
	}
	g_iter = g_iter +write(1, ch, ft_strlen(ch));
	free(ch);
}

char	c_print_need(char o, va_list vl, t_param *a)
{
	if (o > 0)
		return (o);
	else if (a->type == 'c')
		return((char)va_arg(vl, int));
	else
		return ('%');

}

void 	c_print(t_param *a, va_list vl, char o)
{
	char	*ch;
	char	*wdth;
	int 	r;
	char	*tmp;
	char	*tmpp;

	r = 0; 
	tmp = NULL;
	wdth = " ";
	if (a->nol == 1 )
		wdth = "0";
	ch = ft_strnew(2);
	ch[0] = c_print_need(o, vl, a);
	if (ch[0] == 0)
		r = 1;
	if (1 < a->wdth)
	{
		tmp = (char *)ft_stranew(a->wdth  - r - (int)ft_strlen(ch), wdth);
		if (a->mns == -1)
		{
			tmpp = ch;
			ch = ft_strjoin(tmp, ch);
			free(tmpp);
		}
		else
			{
				tmpp = ch;
			ch = ft_strjoin(ch, tmp);
			free(tmpp);
			}
	}
	ft_putstr(ch);
	if (r == 1)
		g_iter = g_iter + write(1,"\0",1);
	g_iter= g_iter +ft_strlen(ch);
	free(ch);
	if (tmp)
		free(tmp);
}

void	s_print(t_param *a, va_list vl)
{
	char	*ch;
	char	*wdth;
	char		*tmp;
	char		*tmpp;
	int g;

	g = 0;
	wdth = " ";
	if (a->nol == 1 )
		wdth = "0";
	ch = (char *)va_arg(vl, char *);
	if (ch == NULL)
	{
		ch = ft_strdup("(null)");
		g = 1;
	}
	if (a->tchka == 1 && a->prcsn <= 0)
	{
		if (g == 1)
			free(ch);
		ch = ft_strnew(1);
		g = 1;
	}
	if (a->prcsn > -1)
	{
		tmp = ch;
		ch = ft_strndup(ch, a->prcsn);
		if (g == 1)
			free(tmp);
		g = 1;
	}
	if ((int)ft_strlen(ch) < a->wdth)
	{	
		if (a->mns == 1)
		{
			tmp = ch;
			tmpp = ft_stranew(a->wdth - (int)ft_strlen(ch), wdth);
			ch = ft_strjoin(tmp, tmpp);
			free(tmpp);
			if (g == 1)
				free(tmp);
		}
		else
			{
				tmp = ch;
			tmpp = ft_stranew(a->wdth - (int)ft_strlen(ch), wdth);
			ch = ft_strjoin(tmpp, tmp);
			free(tmpp);
			if (g == 1)
				free(tmp);
			}
	}
	g_iter = g_iter + write(1, ch, ft_strlen(ch));
	if (g == 1)
		free (ch);
}

void	p_printf(size_t n, t_param *a)
{
	char		*str;
	char		*wdth;
	char		*tmp;
	char		*tmpp;

	wdth = " ";
	if (a->prcsn <= 0 &&  a->tchka == 1 && n == 0)
	 	str = ft_strnew(1);
	else
		str = for_digits(n, a);
	if (a->nol == 1 && a->tchka == -1 && a->mns == -1)
		wdth = "0";
	if (a->prcsn >= 0 && (int)ft_strlen(str)  < a->prcsn && a->tchka == 1)
	{
		tmp = str;
		tmpp = ft_stranew(-(int)ft_strlen(str) + a->prcsn , "0");
		str  = ft_strjoin(tmpp, tmp);
		free(tmp);
		free(tmpp);
		//for_free_three_d(ft_stranew(-(int)ft_strlen(str) + a->prcsn , "0"), &str);
	}
	if (wdth[0] == ' ' )
		p_printf_need(&str, a, wdth);
	else if (wdth[0] == 48 )
		p_printf_needd(&str, a, wdth);
	
	g_iter = g_iter +write(1, str, ft_strlen(str));
	free(str);
}


char	*for_digits(size_t n,t_param *a)
{
	size_t	len;
	char	*str;
	size_t	b;
	char	ch;

	b = 10;
	ch = (a->type == 'x' || a->type == 'p') ?  'a' : 'A';
	if (a->type == 'x' || a->type == 'X' || a->type == 'p')
		b = 16;
	if (a->type == 'o' || a->type =='O')
		b = 8;
	len = ft_get_len(n, b);
	str = (char *)ft_memalloc(len + 1);
	if (n % b > 9)
		str[--len] = n % b + ch - 10;
	else
		str[--len] = n % b + '0';
	while (n /= b)
	{
		if (n % b > 9)
			str[--len] = n % b + ch - 10;
		else
			str[--len] = n % b + '0';
	}
	return (str);
}

void	p_printf_need(char **str, t_param *a, char *wdth)
{
	char *tmp;
	char *tmpp;

	for_free_two("0x", str);
	if ((int)ft_strlen(*str) < a->wdth)
	{
		if (a->mns == 1)
		{
			tmp = *str;
			tmpp = ft_stranew(a->wdth - ft_strlen(*str) , wdth);
			*str  = ft_strjoin(tmp, tmpp);
			free(tmp);
			free(tmpp);
		}
		else
		{
			tmp = *str;
			tmpp = ft_stranew(a->wdth - ft_strlen(*str) , wdth);
			*str  = ft_strjoin(tmpp, tmp);
			free(tmp);
			free(tmpp);
		}
	}
}

void	p_printf_needd(char **str, t_param *a, char *wdth)
{
	char *tmp;
	char *tmpp;

	a->wdth = a->wdth - 2;
	if ((int)ft_strlen(*str) < a->wdth)
	{
		if (a->mns != 1)
		{
			tmp = *str;
			tmpp = ft_stranew(a->wdth - ft_strlen(*str) , wdth);
			*str  = ft_strjoin(tmpp, tmp);
			free(tmp);
			free(tmpp);
			for_free_two("0x", str);
		}
	}
	else
		for_free_two("0x", str);
}


void	itoa_printf_need(t_param *a, char **str, char *wdth, int zn)
{
	char *tmp;
	char *tmpp;

	if ((int)ft_strlen(*str) < a->prcsn && a->prcsn != -1)
	{
		tmp = *str;
		tmpp = ft_stranew(a->prcsn - (int)ft_strlen(*str), "0");
		*str  = ft_strjoin(tmpp, tmp);
		free(tmp);
		free(tmpp);
	}
	if (zn == -1 && ((a->nol != 1 || (int)ft_strlen(*str) > a->wdth) || a->wdth < 0 || a->mns == 1))
		for_free_two("-", str);
	else if (a->pls == 1 && (a->nol != 1 || (int)ft_strlen(*str) > a->wdth) && ft_strchr("dDi", a->type) && zn > 0 )
		for_free_two("+", str);
	else if (a->prbl == 1 && (a->nol != 1 || (int)ft_strlen(*str) > a->wdth) && ft_strchr("dDi", a->type))
		for_free_two(" ", str);
	if ((int)ft_strlen(*str) < a->wdth && a->wdth != -1)
	{
		if (a->mns == 1)
		{
			tmp = *str;
			tmpp = ft_stranew(a->wdth - ft_strlen(*str) , wdth);
			*str  = ft_strjoin(tmp, tmpp);
			free(tmp);
			free(tmpp);
		}
		else
		{
			tmp = *str;
			tmpp = ft_stranew(a->wdth - ft_strlen(*str) , wdth);
			*str  = ft_strjoin(tmpp, tmp);
			free(tmp);
			free(tmpp);
			if ((a->pls == 1) && a->nol == 1 && zn > 0)
				*str[0] = '+';
			else if ((a->prbl == 1) && a->nol == 1)
				*str[0] = ' ';
			else if (zn == -1 && a->nol == 1)
				*str[0] = '-';
		}
	}
}

void	itoa_printf_need_dva(t_param *a, char **str, char *wdth, size_t w)
{
	char	*tmp;
	char	*tmpp;

	if (a->prcsn >= 0 && (int)ft_strlen(*str) < a->prcsn && a->tchka == 1)
	{
		tmp = *str;
		tmpp = ft_stranew(-(int)ft_strlen(*str) + a->prcsn , "0");
		*str = ft_strjoin(tmpp, tmp);
		free(tmp);
		free(tmpp);
	}
	if (a->ht == 1 && wdth[0] == ' ' && w != 0)
		razraz(a, str, wdth);
	else if (a->ht == 1 && wdth[0] == 48 && w!=0)
		razdva(a, str, wdth);
	else
	{
		if ((int)ft_strlen(*str) < a->wdth)
		{
			tmp = *str;
			tmpp = ft_stranew(a->wdth - ft_strlen(*str) , wdth);
			if (a->mns == 1)
				*str = ft_strjoin(*str, tmpp);
			else
				*str = ft_strjoin(tmpp, *str);
			free(tmp);
			free(tmpp);
		}
	}	
}

void razraz(t_param *a, char **str, char *wdth)
{
	char	*tmp;
	char	*tmpp;

	if (a->type == 'x')
		for_free_two("0x", str);
	else if (a->type == 'X')
		for_free_two("0X", str);
	else if (a->type == 'o' && *str[0] != '0')
		for_free_two("0", str);
	if ((int)ft_strlen(*str) < a->wdth)
	{
		tmp = *str;
		tmpp = ft_stranew(a->wdth - ft_strlen(*str) , wdth);
		if (a->mns == 1)
			*str = ft_strjoin(*str, tmpp);
		else
			*str = ft_strjoin(tmpp, *str);
		free(tmp);
		free(tmpp);
	}
}

void razdva(t_param *a, char **str, char *wdth)
{
	char	*tmp;
	char	*tmpp;

	a->wdth -= (a->type == 'o') ? 1 : 2; 
	if ((int)ft_strlen(*str) < a->wdth)
	{
		if (a->mns != 1)
		{
			tmp = *str;
			tmpp = ft_stranew(a->wdth - ft_strlen(*str) , wdth);
			*str = ft_strjoin(tmpp, *str);
			free(tmpp);
			free(tmp);
			if (a->type == 'x')
			for_free_two("0x", str);
		else if (a->type == 'X')
			for_free_two("0X", str);
		else if (a->type == 'o' && *str[0] != '0')
				for_free_two("0", str);
		}
	}
}

void	itoa_printf(size_t n, t_param *a, int zn)
{
	char			*str;
	char			*wdth;
	size_t			w;

	w = n;
	if (a->prcsn <= 0 &&  a->tchka == 1 && n == 0 && a->type == 'o' && a->ht == 1)
		str = ft_stranew(1, "0");
	else if (a->prcsn <= 0 &&  a->tchka == 1 && n == 0)
	 	str = ft_strnew(1);
	else
		str = for_digits(n, a);
	wdth = " ";
	if (a->nol == 1 && a->tchka == -1 && a->mns == -1)
		wdth = "0";
	if (ft_strchr("XxOo", a->type) == NULL)
		itoa_printf_need(a, &str, wdth, zn);
	else
		itoa_printf_need_dva(a, &str, wdth, w);
	g_iter = g_iter + write(1, str, ft_strlen(str));
	free(str);
}

