/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_pointer.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maherraz <maherraz@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/05 07:22:39 by maherraz          #+#    #+#             */
/*   Updated: 2026/03/05 07:25:39 by maherraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_putpt_base(unsigned long addr, char *base)
{
	int	len;

	len = 0;
	if (addr >= 16)
		len += ft_putpt_base(addr / 16, base);
	len += ft_putchar(base[addr % 16]);
	return (len);
}

int	ft_print_pointer(void *ptr)
{
	int				len;
	unsigned long	addr;

	len = 0;
	if (!ptr)
	{
		write(1, "(nil)", 5);
		return (5);
	}
	addr = (unsigned long)ptr;
	write(1, "0x", 2);
	len += 2;
	len += ft_putpt_base(addr, "0123456789abcdef");
	return (len);
}
