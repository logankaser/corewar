/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   format.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lkaser <lkaser@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/06 20:20:56 by lkaser            #+#    #+#             */
/*   Updated: 2018/07/06 20:20:59 by lkaser           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void			handle_flags(t_printf pf, char **out, uintmax_t nbr)
{
	if (pf.pre)
	{
		MATCH(pf.type == t_octal && nbr, ft_strprepend("0", out));
		OR(ANY2(pf.type, t_hex, t_ptr), ft_strprepend("0x", out));
		OR(pf.type == t_hex_up, ft_strprepend("0X", out));
	}
	MATCH(pf.pad_pos && pf.type == t_int && (intmax_t)nbr >= 0,
		ft_strprepend(" ", out));
	pf.width -= ft_strlen(*out) + pf.pre_plus;
	if (pf.width && pf.width > 0)
	{
		if (pf.left_align)
			while (pf.width--)
				ft_strappend(out, " ");
		else
			while (pf.width--)
				ft_strprepend(pf.pad_zero ? "0" : " ", out);
	}
	MATCH(pf.pre_plus && pf.type == t_int && (intmax_t)nbr >= 0,
		ft_strprepend("+", out));
}

static uintmax_t	apply_length(t_printf pf)
{
	uintmax_t nbr;

	nbr = 0;
	if (pf.type == t_int)
	{
		MATCH(!pf.len, nbr = pf.data.i);
		OR(pf.len == l_hh, nbr = pf.data.c);
		OR(pf.len == l_h, nbr = pf.data.s);
		OR(pf.len == l_l, nbr = pf.data.l);
		OR(pf.len == l_ll, nbr = pf.data.ll);
		OR(pf.len == l_z, nbr = pf.data.st);
		OR(pf.len == l_j, nbr = pf.data.im);
	}
	else
	{
		MATCH(!pf.len, nbr = pf.data.ui);
		OR(pf.len == l_hh, nbr = pf.data.uc);
		OR(pf.len == l_h, nbr = pf.data.us);
		OR(pf.len == l_l, nbr = pf.data.ul);
		OR(pf.len == l_ll, nbr = pf.data.ull);
		OR(pf.len == l_z, nbr = pf.data.st);
		OR(pf.len == l_j, nbr = pf.data.um);
	}
	return (nbr);
}

static char			*wchar_to_str(wchar_t wc)
{
	static char str[8];

	*((uint64_t*)str) = 0;
	*((wchar_t *)str) = wc;
	return (str);
}

static char			*char_to_str(int c)
{
	static char str[8];

	*((uint64_t*)str) = 0;
	*((int*)str) = c;
	return (str);
}

void				format_print(t_printf pf, t_uvector *s)
{
	uintmax_t	nbr;
	char		*str;

	nbr = pf.type >= t_ptr ? apply_length(pf) : 0;
	MATCH(pf.type == t_wstr, str = ft_wchar_utf8(pf.data.wstr));
	OR(pf.type == t_wchar, str = wchar_to_str(pf.data.wc));
	OR(pf.type == t_str, str = pf.data.str);
	OR(pf.type == t_char, str = char_to_str(pf.data.i));
	OR(pf.type == t_int, str = FT_ITOA_BASE(nbr, "0123456789"));
	OR(pf.type == t_uint, str = FT_UTOA_BASE(nbr, "0123456789"));
	OR(pf.type == t_hex, str = FT_UTOA_BASE(nbr, "0123456789abcdef"));
	OR(pf.type == t_ptr, str = FT_UTOA_BASE(pf.data.p, "0123456789abcdef"));
	OR(pf.type == t_hex_up, str = FT_UTOA_BASE(nbr, "0123456789ABCDEF"));
	OR(pf.type == t_octal, str = FT_UTOA_BASE(nbr, "01234567"));
	if (pf.type)
	{
		if (pf.type > t_wstr)
			handle_flags(pf, &str, nbr);
		ft_string_append(s, str ? str : "(null)");
		if (pf.type != t_str && pf.type != t_char && pf.type != t_wchar)
			free(str);
	}
}
