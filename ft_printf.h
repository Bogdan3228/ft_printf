/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bgres <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/24 18:38:42 by bgres             #+#    #+#             */
/*   Updated: 2018/01/26 21:31:57 by bgres            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>
int ft_printf(char *fmt, ...);
// http://www.pixelbeat.org/programming/gcc/format_specs.html
//f = 's' || f = 'S' || f = 'p' || f = 'd' || f = 'i' || f = 'D' || f = 'o' || f = 'O' || f = 'u' || f = 'U' || f = 'x' || f = 'X' || f = 'c' || f = 'C' ||
typedef	struct		s_param
{
	char			n;
	int				pls; // +
	int				mns; // -
	int				nol; // 0
	int				ht;  // #
	int				prbl; // ' '
	char			lm; //"hhll.."
	char			type; //"sSdi..
	int				tchka;
	int				ror;
	int				wdth;
	int				prcsn;
	struct s_param  *next;
}					t_param;
int 	g_iter;
int 	g_rr;


#endif
