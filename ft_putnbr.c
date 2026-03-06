/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maherraz <maherraz@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 10:23:41 by maherraz          #+#    #+#             */
/*   Updated: 2026/03/05 07:44:20 by maherraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_putnbr_base(unsigned long number)
{
	int				count;
	unsigned long	digit;

	count = 0;
	digit = number;
	if (number >= 0)
	{
		if (number >= 10)
			count += ft_putnbr_base(number / 10);
		count += ft_putchar((char)(digit % 10 + '0'));
	}
	return (count);
}

int	ft_putnbr(int nb)
{
	int		count;
	long	n;

	count = 0;
	n = nb;
	if (n == 0)
		return (ft_putchar('0'));
	if (n < 0)
	{
		count += ft_putchar('-');
		n = -n;
	}
	count += ft_putnbr_base((unsigned long)n);
	return (count);
}

int	ft_putnbr_unsigned(unsigned int nb)
{
	if (nb == 0)
		return (ft_putchar('0'));
	return (ft_putnbr_base((unsigned long)nb));
}
