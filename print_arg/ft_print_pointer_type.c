/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_pointer_type.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: apending <apending@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/24 20:51:25 by apending          #+#    #+#             */
/*   Updated: 2020/12/25 21:40:57 by apending         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../printf.h"

void ft_print_pointer_hex(unsigned long num, s_arg s_arg, int *print_c)
{
	int hex;
	char c;

	hex = num % 16;
	if (hex < 10)
		c = hex + '0';
	else
		c = hex - 10 + 'a';
	num /= 16;
	(*print_c)++;
	if (num != 0)
		ft_print_pointer_hex(num, s_arg, print_c);
	else
	{
		if ((s_arg.precision - *print_c) > 0 || (FLG_MINUS & s_arg.flag) || (s_arg.width - (*print_c) - 2) < 0)
			write(1, "0x", 2);
		while ((s_arg.precision - *print_c) > 0)
		{
			write(1, "0", 1);
			(*print_c)++;
		}
		if (!(FLG_MINUS & s_arg.flag) && (s_arg.width - (*print_c)) > 0)
		{
			if (*print_c == 1 && s_arg.precision == 0)
				*print_c = 0;
			while ((s_arg.width - (*print_c) - 2) > 0)
			{
				write(1, " ", 1);
				(*print_c)++;
			}
			if ((s_arg.precision - *print_c) < 0)
				write(1, "0x", 2);
		}
		(*print_c) += 2;
	}
	if (!(s_arg.precision == 0 && c == '0'))
		write(1, &c, 1);
	else
		(*print_c)--;
}

int ft_print_pointer_type(s_arg s_arg, va_list *arg_ptr)
{
	int print_c;
	unsigned long num;

	num = (unsigned long)va_arg(*arg_ptr, void*);
	print_c = 0;
	if (s_arg.precision > s_arg.width)
		s_arg.width = 0;
	if (s_arg.width == 2 && !num)
	{
		write(1, "0x", 2);
		print_c += 2;
		if (!s_arg.precision)
			return (print_c);
		else
			write(1, "0", 1);
		return (print_c + 1);
	}
	ft_print_pointer_hex(num, s_arg, &print_c);
	if (!(FLG_MINUS & s_arg.flag) && print_c == s_arg.width - 1 && s_arg.precision == 0)
		print_c = s_arg.width;
	if (FLG_MINUS & s_arg.flag)
	{
		while ((s_arg.width - print_c) > 0)
		{
			write(1, " ", 1);
			print_c++;
		}
	}
	return (print_c);
}