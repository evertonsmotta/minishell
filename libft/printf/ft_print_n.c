/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_n.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneto-de <nneto-de@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 17:19:17 by nneto-de          #+#    #+#             */
/*   Updated: 2024/01/23 19:47:51 by nneto-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_print_n(long n)
{
	int	len;

	len = 0;
	if (n < 0)
	{
		len += ft_print_c('-');
		n = -n;
	}
	if (n >= 10)
	{
		len += ft_print_n((n / 10));
		len += ft_print_n((n % 10));
	}
	else
		len += ft_print_c(n + '0');
	return (len);
}
