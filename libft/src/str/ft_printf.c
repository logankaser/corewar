/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaser <lkaser@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/06 20:23:36 by lkaser            #+#    #+#             */
/*   Updated: 2018/07/06 20:23:39 by lkaser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <wchar.h>
#include <unistd.h>
#include <stdarg.h>

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

static void		parse_specifiers(t_printf *pf, char **f)
{
	MATCH(**f == 'C' || (**f == 'c' && pf->len == l_l),
		pf->type = t_wchar);
	OR(**f == 'S' || (**f == 's' && pf->len == l_l), pf->type = t_wstr);
	OR(**f == 'c', pf->type = t_char);
	OR(**f == 's', pf->type = t_str);
	OR(**f == 'p', pf->type = t_ptr);
	OR(ANY3(**f, 'i', 'd', 'D'), pf->type = t_int);
	OR(ANY2(**f, 'u', 'U'), pf->type = t_uint);
	OR(ANY2(**f, 'o', 'O'), pf->type = t_octal);
	OR(**f == 'x', pf->type = t_hex);
	OR(**f == 'X', pf->type = t_hex_up);
	if (ANY3(**f, 'U', 'O', 'D'))
		pf->len = l_l;
	if (pf->type == t_ptr)
		pf->pre = 1;
	if (pf->type)
		++*f;
}

static unsigned	read_num(char **f)
{
	unsigned	num;

	num = 0;
	while (**f && ft_isdigit(**f))
	{
		num *= 10;
		num += **f - '0';
		++*f;
	}
	return (num);
}

static void		format_parse(char **f, va_list args, t_uvector *s)
{
	t_printf	pf;

	pf = ((t_printf){va_arg(args, t_data), 0, 0, 0, 0, 0, 0, 0, 0, 0});
	while (**f && ANY5(**f, '#', '0', '-', '+', ' '))
	{
		MATCH(**f == '#', pf.pre = 1);
		OR(**f == '0', pf.pad_zero = 1);
		OR(**f == '-', pf.left_align = 1);
		OR(**f == '+', pf.pre_plus = 1);
		OR(**f == ' ', pf.pad_pos = 1);
		++*f;
	}
	pf.width = read_num(f);
	MATCH(!ft_strncmp(*f, "hh", 2), pf.len = l_hh);
	OR(**f == 'h', pf.len = l_h);
	OR(!ft_strncmp(*f, "ll", 2), pf.len = l_ll);
	OR(**f == 'l', pf.len = l_l);
	OR(**f == 'j', pf.len = l_j);
	OR(**f == 'z', pf.len = l_z);
	MATCH(pf.len, ++*f);
	MATCH(ANY2(pf.len, l_hh, l_ll), ++*f);
	parse_specifiers(&pf, f);
	format_print(pf, s);
}

void			format_iter(t_uvector *s, char *f, va_list args)
{
	size_t		d;

	d = 0;
	while (f[d])
	{
		if (f[d] == '%' && f[d + 1] == '%')
		{
			ft_string_appendn(s, f, ++d);
			f += ++d;
			d = 0;
		}
		else if (f[d] == '%')
		{
			ft_string_appendn(s, f, d);
			f += d + 1;
			format_parse(&f, args, s);
			d = 0;
		}
		else
			d += f[d] != 0;
	}
	ft_string_appendn(s, f, d);
}

int				ft_printf(char *format, ...)
{
	t_uvector	s;
	va_list		args;

	if (format)
	{
		ft_uvector_init(&s, 1);
		va_start(args, format);
		format_iter(&s, format, args);
		va_end(args);
		write(STDOUT_FILENO, s.data, s.length);
		free(s.data);
		return (s.length);
	}
	return (0);
}
