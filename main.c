/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgres <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 04:43:37 by bgres             #+#    #+#             */
/*   Updated: 2018/02/02 04:48:23 by bgres            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdio.h>
#include <limits.h>
#include <locale.h>
#include <stdlib.h>
int main()
{
	char *a;
	a=NULL;
	int aaa = 0;
	int aa = 1;
	char ch = 'g';
    setlocale(LC_ALL,"");
	ft_printf("%S", L"плиз покажи мне лики");

	return (0);
}

// void	p_printf(size_t n, t_param *a)
// {
// 	char			*str;
// 	size_t		b;
// 	char		ch;
// 	size_t		len;
// 	size_t		tmp = 0;
// 	char		*wdth;

// 	ch = 'a';
// 	b = 16;
// 	wdth = " ";
// 	if (a->prcsn <= 0 &&  a->tchka == 1 && n == 0)
// 	 	str = ft_strnew(1);
// 	else
// 	{
// 	len = ft_get_len(n, b);
// 	str = (char *)ft_memalloc(len + 1);
// 	if (n % b > 9)
// 		str[--len] = n % b + ch - 10;
// 	else
// 		str[--len] = n % b + '0';
// 	while (n /= b)
// 	{
// 		if (n % b > 9)
// 		str[--len] = n % b + ch - 10;
// 	else
// 		str[--len] = n % b + '0';
// 	}
// 	}
// 	len = tmp;
// 	if (a->nol == 1 && a->tchka == -1 && a->mns == -1)
// 		wdth = "0";
// 	if (a->prcsn >= 0 && (int)ft_strlen(str)  < a->prcsn && a->tchka == 1)
// 		str = ft_strjoin(ft_stranew(-(int)ft_strlen(str) + a->prcsn , "0"), str);
	
// 	if ((int)ft_strlen(str) < a->wdth)
// 	{
// 		if (a->mns == 1)
// 		{
// 			str = ft_strjoin("0x", str);
// 			str = ft_strjoin(str, ft_stranew(a->wdth - ft_strlen(str) , wdth));
// 		}
// 		else
// 		{
// 			if (a->nol != 1) 
// 			{
// 				str = ft_strjoin("0x", str);
// 				str = ft_strjoin(ft_stranew(a->wdth - ft_strlen(str), wdth), str);
// 			}
// 			else
// 			{
// 				if (a->wdth - 2 > 0)
// 					str = ft_strjoin(ft_stranew(a->wdth -2 - ft_strlen(str), wdth), str);
// 				str = ft_strjoin("0x", str);
// 			}
// 		}
// 	}
// 	g_iter = g_iter + (int)ft_strlen(str);
// 	ft_putstr(str);
// }