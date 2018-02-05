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
void getd(t_param **list, char c, long long l, va_list vl);
int ft_printf(char *fmt, ...);
void get_decimal(t_param **list, va_list vl);
char n = 's';
void parsing_one(char *txt, va_list ap);
void	itoa_printf(size_t n, t_param *a, int zn);
void	p_printf(size_t n, t_param *a);
size_t	get_p(va_list vl);
char	*for_bits(wint_t ch, t_param *a);
void	p_utf(t_param *a, va_list vl);
void 	c_print(t_param *a, va_list vl, char t);
void	s_print(t_param *a, va_list vl);
void	s_print_for_unic(t_param *a, char *ch);
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


// int main (void)
// {
// 	int g = 1234;
// 	int *p;
// 	p = &g;
// 	//char	a[10] = "1111111\0";
// 	setlocale(LC_ALL, "");
// 	printf("%S\n", L"хуййй");
// 	ft_printf("%S", L"хуййй");
// 	return 0;
// }
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

void	prmprnt(t_param **a)
{
	printf("\n%c\n",(*a)->n );
	printf("%i\n",(*a)->pls);
	printf("%i\n",(*a)->mns);
	printf("%i\n",(*a)->nol);
	printf("%i\n",(*a)->ht);
	printf("%i\n",(*a)->prbl);
	printf("%c\n",(*a)->lm);
	printf("%c\n",(*a)->type);
	printf("%i\n",(*a)->tchka);
	printf("%i\n",(*a)->ror);
	printf("%i\n",(*a)->wdth);
	printf("%i\n",(*a)->prcsn);
}
int ft_printf(char *fmt, ...)
{
	va_list ap;
	g_iter = 0;
	g_rr = 0;
	va_start(ap, fmt);
	parsing_one(fmt, ap);
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
	// param->type = f;
	// param->tchka = -1;
	// param->ror = -1;
	// param->wdth = -1; ///sSpdDioOuUxXcC
	// param->prcsn = -1;
}
void	setflag_dva(t_param **param, char * txt, int j, int flag)
{
	j++;
	if (flag == 1)
		(*param)->wdth = ft_atoi(txt);
	else if (flag == 2)
		(*param)->prcsn = ft_atoi(txt);
}
void parsing_one(char *txt, va_list vl)
{
	int		*i;
	int		j;
	int 	a;
	int		g;

	g = 0;
	a = 0;
	i  =&a;
	j = 0;
	t_param *param;
	param = prmcrt();
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
			{
				*i = *i + 1;
			}
			else
			*i = *i + parsing_two(&param, &txt[*i], vl);
		}
		else
		{
			while(txt[*i + j] != '\0' && txt[*i + j] != '%')
				j++;
			write(1,(txt + *i), j);
			g_iter += j;
			*i = *i + j;
			j = 0;
		}
		
	}	
}
int		parsing_two(t_param **param, char *txt, va_list vl)
{
	int		i;
	int 	j;

	i = 1;
	j = 0;
	parsing_three(param, txt, " +-0#\0", &i);
	while (txt[i + j] != '\0' && ft_isdigit(txt[i + j]) == 1)
		j++;
	if (j > 0)
		setflag_dva(param, &txt[i], j, 1);
	i = i + j;
	j = 0;
	if (txt[i] == '.')
	{
		(*param)->tchka = 1;
		i++;
	}
	while (txt[i + j] != '\0' && ft_isdigit(txt[i + j]))
		j++;
	if (j > 0)
		setflag_dva(param, &txt[i], j, 2);
	i = i + j;
	j = 0;
	parsing_three(param, txt, "hljz\0", &i);
	check_p_end(param, txt, &i, vl);
	return (i);	
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
		//write(1, &txt[*i], 1);
		*i = *i + 1;
		//g_iter++;
		(*param)->ror = 1;
	}
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
	(*param)->next = prmcrt();
	*param = (*param)->next;
}


char	*for_bits(wint_t ch, t_param *a)
{
	unsigned int 	i;
	int 			j;
	char			*buf;
	int            p;
	if (ch == 0)
	{
		if (a->type == 'C')
		{
		write(1, "\0", 1);
		g_iter++;
		}
		return ("\0");
	}
	buf = ft_strnew(5);
	j = 0;
	i = 0x80000000;
	while((i & ch) == 0)
	{
		j++;
		i = i / 2;
	}
	j = 32 - j;
	if (MB_CUR_MAX == 1 && j > 7)
	{
		printf("mbcurmax = %d\n", MB_CUR_MAX);
		printf("%U\n",ch );
		g_rr = -1;
		j = 1;
	}
	else if (MB_CUR_MAX ==2 && j> 11)
	{
		printf("mbcurmax = %d\n", MB_CUR_MAX);
		g_rr = -1;
		j = 1;
	}
	else if (MB_CUR_MAX == 3 && j >16)
	{
		printf("mbcurmax = %d\n", MB_CUR_MAX);
		g_rr = -1;
		j = 1;
	}
	if (j <= 7 )
	{
		buf[0] = ch & 0x7f;
		if (a->type == 'C' || a->type == 'c')
		{
			g_iter++;
			write(1, buf, 1);
		}
		else if(a->type == 's' || a->type == 'S')
		{
			if (a->prcsn - 1 >= 0 || a->tchka == -1)
			{
					//	g_iter++;
				a->prcsn -= 1;
				return (buf);
			}
		}
	}
	else if (j <= 11)
	{
		buf[1] = ((ch & 0x3f) | 0x80) & 0xffffffbf;
		buf[0] = (((0x00000fc0 & ch) >> 6) | 0x000000c0) & 0xfffffdf;
		if (a->type == 'C' || a->type == 'c')
		{
			g_iter = g_iter + 2;
		write(1, buf, 2);
		}
		else if (a->type == 's' || a->type =='S')
		{
			if (a->prcsn -2 >= 0 || a->tchka == -1)
			{
				//g_iter = g_iter + 2;
				a->prcsn -= 2;
				return (buf);
			}
		}
	}
	else if (j <= 16)
	{
		buf[2] = ((ch & 0x0000003f) | 0x00000080) & 0xffffffbf;
		buf[1] = (((0x00000fc0 & ch) >> 6) | 0x00000080) & 0xffffffbf;
		buf[0] =   ((0x0000f000 & ch) >> 12 | 0x000000e0) & 0xffffffef;
		if (a->type == 'C' || a->type == 'c')
		{
			g_iter = g_iter + 3;
		write(1, buf, 3);
		}
		else if (a->type == 's' || a->type =='S')
		{
			if (a->prcsn - 3 >= 0 || a->tchka == -1) 
			{
						//g_iter = g_iter + 3;
				a->prcsn -= 3;
				return (buf);
			}
		}
	}
	else
	{
		buf[3] = ((ch & 0x0000003f) | 0x00000080) & 0xffffffbf;
		buf[2] = (((0x00000fc0 & ch) >> 6) | 0x00000080) & 0xffffffbf;
		buf[1] =   ((0x0003f000 & ch) >> 12 | 0x00000080) & 0xffffffbf;
		buf[0] =  (((0x00007000 & ch)  >> 18) | 0x000000f0) & 0xfffffff7;
		if (a->type == 'C' || a->type == 'c')
		{g_iter = g_iter + 4;
		write(1, buf, 4);
		}
		else if (a->type == 's' || a->type =='S')
		{
			if (a->prcsn - 4 >= 0 || a->tchka == -1)
			{		//g_iter = g_iter + 4;
				a->prcsn -= 4;
				return (buf);
			}
		}
	}
	return("");
	// write(1, &(buf[3]), 1);
	// write(1, &(buf[2]), 1);
	// write(1, &(buf[1]), 1);
	// write(1, &(buf[0]), 1);

}
void	p_utf(t_param *a, va_list vl)
{
	wchar_t	*s;
	wint_t	ch;
	char	*stroka;

	stroka = ft_strnew(0);
	if (a->type == 'C' || a->type =='c'){
		ch = va_arg(vl, wint_t);
		for_bits(ch, a);
	}
	else
	{
		s = va_arg(vl, wchar_t *);
		if (s == NULL)
			g_iter = g_iter + write(1, "(null)", 6);
		else
		{
			while (*s != '\0')
			{
				stroka = ft_strjoin(stroka, for_bits(*s, a));
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
	{
		itoa_printf(-1 * l, (*list), -1);
	}
	else if (c == 'd' && l >= 0)
	{
 		itoa_printf(l, (*list), 1);
	}
	else if (c != 'd')
	{
 		itoa_printf(s, (*list), 1);	}
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
	char	*chh;
	char		*wdth;
	wdth = " ";
	if (a->nol == 1 )
		wdth = "0";
	if ((int)ft_strlen(ch) < a->wdth)
	{	
		if (a->mns == 1)
			ch = ft_strjoin( ch,ft_stranew(a->wdth - (int)ft_strlen(ch), wdth));
		else
			ch = ft_strjoin(ft_stranew(a->wdth - (int)ft_strlen(ch), wdth), ch);
	}
	g_iter = g_iter +(int)ft_strlen(ch);
	ft_putstr(ch);
}

void 	c_print(t_param *a, va_list vl, char o)
{
	char	*ch;
	char		*wdth;
	int r = 0;
	wdth = " ";
	if (a->nol == 1 )
		wdth = "0";
	ch = ft_strnew(2);
	if (o > 0)
		ch[0] = o;
	else if (a->type == 'c')
		ch[0] = (char)va_arg(vl, int);
	else
		ch[0] = '%';
	if (ch[0] == 0)
		r = 1;
	//printf("tu syda zashol%d\n", a->mns);
		if (1 < a->wdth)
		{
			if (a->mns == -1)
				ch = ft_strjoin(ft_stranew(a->wdth  - r - (int)ft_strlen(ch), wdth), ch);
			else
				ch = ft_strjoin(ch, ft_stranew(a->wdth - r - (int)ft_strlen(ch), wdth));
		}
		 //printf("ch = -%s-\n",ch );
	ft_putstr(ch);
	if (r == 1)
	{
		g_iter++;
		write(1,"\0",1);
	}
	g_iter= g_iter +ft_strlen(ch);
}
void	s_print(t_param *a, va_list vl)
{
	char	*ch;
	char	*chh;
	char		*wdth;
	wdth = " ";
	if (a->nol == 1 )
		wdth = "0";
	ch = (char *)va_arg(vl, char *);
	if (ch == NULL)
	{
		ch = ft_strdup("(null)");
	}
	// if (ft_strlen(ch) == 0)
	// 	return ;
	if (a->tchka == 1 && a->prcsn <= 0)
		ch = ft_strnew(1);
	if (a->prcsn > -1)
		ch = ft_strndup(ch, a->prcsn);
	if ((int)ft_strlen(ch) < a->wdth)
	{	
		if (a->mns == 1)
			ch = ft_strjoin( ch,ft_stranew(a->wdth - (int)ft_strlen(ch), wdth));
		else
			ch = ft_strjoin(ft_stranew(a->wdth - (int)ft_strlen(ch), wdth), ch);
	}
	g_iter = g_iter +(int)ft_strlen(ch);
	ft_putstr(ch);
}
void	p_printf(size_t n, t_param *a)
{
	char			*str;
	size_t		b;
	char		ch;
	size_t		len;
	size_t		tmp = 0;
	char		*wdth;


	ch = 'a';
	b = 16;
	wdth = " ";
	if (a->prcsn <= 0 &&  a->tchka == 1 && n == 0)
	 	str = ft_strnew(1);
	else
	{
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
	}
	len = tmp;
	if (a->nol == 1 && a->tchka == -1 && a->mns == -1)
		wdth = "0";
	if (a->prcsn >= 0 && (int)ft_strlen(str)  < a->prcsn && a->tchka == 1)
		str = ft_strjoin(ft_stranew(-(int)ft_strlen(str) + a->prcsn , "0"), str);
	if (wdth[0] == ' ' )
		{
				str = ft_strjoin("0x", str);
		if ((int)ft_strlen(str) < a->wdth)
		{
			if (a->mns == 1)
				str = ft_strjoin(str, ft_stranew(a->wdth - ft_strlen(str) , wdth));
			else
				str = ft_strjoin(ft_stranew(a->wdth - ft_strlen(str), wdth), str);
		}
	}
	else if (wdth[0] == 48 )
	{
		a->wdth = a->wdth - 2;
		if ((int)ft_strlen(str) < a->wdth)
		{
			if (a->mns != 1)
			{
				str = ft_strjoin( ft_stranew(a->wdth - ft_strlen(str) , wdth), str);
				str = ft_strjoin("0x", str);
			}
		}
		else
			str = ft_strjoin("0x", str);
	}
	g_iter = g_iter + (int)ft_strlen(str);
	ft_putstr(str);
}
void	itoa_printf(size_t n, t_param *a, int zn)
{
	char			*str;
	size_t			len;
	size_t			tmp;
	char			*wdth;
	size_t b = 10;
	char ch;
	size_t w = n;
	if (a->type == 'x' || a->type == 'X')
		b = 16;
	if (a->type == 'o' || a->type =='O')
		b = 8;
	wdth = " ";
	len = ft_get_len(n, b);
	tmp = len;
	if (a->prcsn <= 0 &&  a->tchka == 1 && n == 0 && a->type == 'o' && a->ht == 1)
	str = ft_stranew(1, "0");
	else if (a->prcsn <= 0 &&  a->tchka == 1 && n == 0)
	 	str = ft_strnew(1);
	else
	{
	if (a->type == 'x')
		ch = 'a';
	else if (a->type == 'X')
		ch = 'A';
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
	len = tmp;
	}

	if (a->nol == 1 && a->tchka == -1 && a->mns == -1)
		wdth = "0";
	if (ft_strchr("XxOo", a->type) == NULL)
	{
		if ((int)len < a->prcsn && a->prcsn != -1)
			str = ft_strjoin(ft_stranew(a->prcsn - len, "0"), str);
		if (zn == -1 && ((a->nol != 1 || (int)ft_strlen(str)>a->wdth) || a->wdth <0 || a->mns == 1))
			str = ft_strjoin("-", str);
		else if (a->pls == 1 && (a->nol != 1 || (int)ft_strlen(str)>a->wdth) && ft_strchr("dDi", a->type) && zn >0 )
			str = ft_strjoin("+", str);
		else if (a->prbl == 1 && (a->nol != 1 || (int)ft_strlen(str)>a->wdth) && ft_strchr("dDi", a->type))
			str = ft_strjoin(" ", str);
		if ((int)ft_strlen(str) < a->wdth && a->wdth != -1)
		{
			if (a->mns == 1)
				str = ft_strjoin(str, ft_stranew(a->wdth - ft_strlen(str) , wdth));
			else
			{
				str = ft_strjoin(ft_stranew(a->wdth - ft_strlen(str), wdth), str);
				if ((a->pls == 1) && a->nol == 1 && zn >0)
					str[0] = '+';
				else if ((a->prbl == 1) && a->nol == 1)
					str[0] = ' ';
				else if (zn == -1 && a->nol == 1)
					str[0] = '-';
			}
		}
	}
	else
	{
		if (a->prcsn >= 0 && (int)ft_strlen(str)  < a->prcsn && a->tchka == 1)
			str = ft_strjoin(ft_stranew(-(int)ft_strlen(str) + a->prcsn , "0"), str);
		if (a->ht == 1 && wdth[0] == ' ' && w != 0)
		{
			if (a->type == 'x')
				str = ft_strjoin("0x", str);
			else if (a->type == 'X')
				str = ft_strjoin("0X", str);
			else if (a->type == 'o' && str[0] != '0')
					str = ft_strjoin("0", str);
		if ((int)ft_strlen(str) < a->wdth)
		{
			if (a->mns == 1)
				str = ft_strjoin(str, ft_stranew(a->wdth - ft_strlen(str) , wdth));
			else
				str = ft_strjoin(ft_stranew(a->wdth - ft_strlen(str), wdth), str);
		}
	}
	else if (a->ht == 1 && wdth[0] == 48 && w!=0)
	{
		a->wdth -= (a->type == 'o') ? 1 : 2; 
		if ((int)ft_strlen(str) < a->wdth)
		{
			if (a->mns != 1)
			{
				str = ft_strjoin( ft_stranew(a->wdth - ft_strlen(str) , wdth), str);
				if (a->type == 'x')
				str = ft_strjoin("0x", str);
			else if (a->type == 'X')
				str = ft_strjoin("0X", str);
			else if (a->type == 'o' && str[0] != '0')
					str = ft_strjoin("0", str);
			}
		}
	}
	else
	{
		if ((int)ft_strlen(str) < a->wdth)
		{
			if (a->mns == 1)
				str = ft_strjoin(str, ft_stranew(a->wdth - ft_strlen(str) , wdth));
			else
				str = ft_strjoin(ft_stranew(a->wdth - ft_strlen(str), wdth), str);
		}
	}	
	}
	g_iter = g_iter + (int)ft_strlen(str);
	ft_putstr(str);
}

