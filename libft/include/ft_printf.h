/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaser <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/12/18 19:06:03 by lkaser            #+#    #+#             */
/*   Updated: 2019/04/17 11:42:14 by lkaser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**%[%][flags][width][(dot)precision][length]specifier
**
**Specifiers:
**	c	int converted to char
**	C	int converted to wide char
**	s	string
**	S	wide char string
**	p	pointer
**	di	int, D = ld
**	u	unsigned, U = lu
**	o	unsigned in octal, O = lo
**	x	unsigned in hexadecimal
**	X	unsigned in hexadecimal uppercase
**
**Flags:
**	#		(o,O) prepend '0', x prepend "0x", X prepend "0X"
**	0		Prepend pad with '0' to width (if specified) for numeric types
**	-		Left align within width (if specified)
**	+		Prepend '+' for positive numeric types
**	(space)	Prepend pad positive numbers with a space
**
**Width:
**	<n>	Minimum of n characters are printed
**	*	(Bonus) Width is an int arg before the specifed arg
**
**Precision:
**	(dot)<n>	(idD, uU, oO, xX) Pad with leading zeros if less than n
**	(dot)*		(Bonus) Precision is an int arg before the specifed arg
**
**Length (Aka cast as this):
**	hh	(idD) char,			(uU, oO, xX) unsigned char
**	h	(idD) short,		(uU, oO, xX) unsigned short
**	l	(idD) long,			(uU, oO, xX) unsigned long
**	ll	(idD) long long,	(uU, oO, xX) unsigned long long
**	j	(idD) intmax_t,		(uU, oO, xX) uintmax_t
**	z	(idD) size_t,		(uU, oO, xX) size_t
**
**Return Value:
**	Length of printed string
**.
*/

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include "libft.h"

enum					e_type {
	t_char = 1, t_wchar,
	t_str, t_wstr, t_ptr, t_int,
	t_uint, t_octal, t_hex, t_hex_up};

enum	e_length { l_hh = 1, l_h, l_l, l_ll, l_j, l_z };

typedef union			u_data
{
	char				c;
	unsigned char		uc;
	wchar_t				wc;
	short				s;
	unsigned short		us;
	int					i;
	unsigned			ui;
	char				*str;
	wchar_t				*wstr;
	long				l;
	unsigned long		ul;
	long long			ll;
	unsigned long long	ull;
	intptr_t			p;
	size_t				st;
	intmax_t			im;
	uintmax_t			um;
}						t_data;

typedef struct			s_printf
{
	t_data				data;
	enum e_type			type;
	enum e_length		len;
	bool				pre;
	bool				pad_zero;
	bool				left_align;
	bool				pre_plus;
	bool				pad_pos;
	int					width;
	int					prec;
}						t_printf;

void					format_print(t_printf pf, t_uvector *s);
void					format_iter(t_uvector *s, char *f, va_list args);
int						ft_printf(char *format, ...);
int						ft_fprintf(FILE *stream, const char *format, ...);
char					*ft_strf(const char *format, ...);

#endif
