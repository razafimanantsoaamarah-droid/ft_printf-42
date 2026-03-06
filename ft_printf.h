/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maherraz <maherraz@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 10:31:42 by maherraz          #+#    #+#             */
/*   Updated: 2026/03/05 07:27:00 by maherraz         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdarg.h>

int		ft_putchar(char c);
int		ft_putstr(char *str);
int		ft_putnbr(int number);
int		ft_putnbr_unsigned(unsigned int nb);
int		ft_print_hex(unsigned int n, int maj);
int		ft_print_pointer(void *ptr);
int		ft_printf(const char *format, ...);

#endif
