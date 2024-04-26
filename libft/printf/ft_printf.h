/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nneto-de <nneto-de@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 17:19:17 by nneto-de          #+#    #+#             */
/*   Updated: 2024/01/23 19:48:17 by nneto-de         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

// --------------------------------- INCLUDES ----------------------------------

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>

// -------------------------------- PROTOTYPES ---------------------------------

int	ft_printf(const char *data, ...);
int	ft_print_c(char c);
int	ft_print_s(char *s);
int	ft_print_p(unsigned long n);
int	ft_print_n(long n);
int	ft_print_u(unsigned int n);
int	ft_print_x(unsigned long n, char base);

#endif
