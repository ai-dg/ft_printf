/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dagudelo <dagudelo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 14:45:58 by dagudelo          #+#    #+#             */
/*   Updated: 2023/12/14 16:51:25 by dagudelo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int	ft_check_3(const char str, va_list *args, t_print flag)
{
	int	len;

	len = 0;
	if (str == 'c')
		(len += ft_char(va_arg(*args, int), flag));
	if (str == 's')
		(len += ft_string(va_arg(*args, char *), flag));
	else if (str == 'p')
		len += ft_hex((unsigned long long)va_arg(*args, void *), str, flag);
	else if (str == 'd')
		(len += ft_int(va_arg(*args, int), flag));
	else if (str == 'i')
		(len += ft_int(va_arg(*args, int), flag));
	else if (str == 'u')
		(len += ft_unsigned(va_arg(*args, unsigned int), flag));
	else if (str == 'X' || str == 'x')
		(len += ft_hex(va_arg(*args, unsigned int), str, flag));
	else if (str == '%')
		(len += ft_char_sub('%'));
	return (len);
}

static void	ft_check_2(const char *str, int *index, t_print *flag)
{
	if (str[0] == '#')
		flag->hash = 1;
	else if (str[0] == ' ')
	{
		flag->space = 1;
		flag->space_width = ft_space_count(str);
	}
	else if (str[0] == '+')
		flag->plus = 1;
	else if (str[0] == '0')
	{
		flag->zero_width = ft_atoi_flag(str + 1, index);
		flag->zero = 1;
	}
	else if (str[0] == '-')
	{
		flag->width_minus = ft_atoi_flag(str + 1, index);
		flag->minus = 1;
	}
	else if (str[0] == '.')
	{
		flag->point_width = ft_atoi_flag(str + 1, index);
		flag->point = 1;
	}
}

static void	handle_flags(const char *str, int *index, t_print *flag)
{
	if (ft_check_list(str[(*index) + 1], "-0.# +"))
		ft_check_2(str + (*index) + 1, index, flag);
	else
	{
		flag->width_nbr = ft_atoi_flag(str + (*index) + 1, index);
		(*index)--;
	}
}

static int	ft_check_1(const char *str, int *index, va_list *args)
{
	int		total;
	t_print	flag;

	total = 0;
	ft_set_list(&flag);
	while (ft_check_list(str[(*index) + 1], "123456789-0.# +"))
	{
		handle_flags(str, index, &flag);
		(*index)++;
	}
	total += ft_check_3(str[*index + 1], args, flag);
	(*index)++;
	return (total);
}

int	ft_printf(const char *str, ...)
{
	int		index;
	int		count;
	va_list	args;

	va_start(args, str);
	index = 0;
	count = 0;
	while (str[index] != '\0')
	{
		if (str[index] == '%')
			count += ft_check_1(str, &index, &args);
		else
			count += ft_char_sub(str[index]);
		index++;
	}
	va_end(args);
	return (count);
}

// int	main(void)
// {
// 	printf("Int retourne : %d\n", printf(" %.11ld ", LONG_MIN));
// 	printf("Int retourne : %d\n", ft_printf(" %.11d ", LONG_MIN));
// 	// char	*s2;
// 	// char	*str;
// 	// str = "hvgjbknl";
// 	// puts("\033[1;35mTest 1 avec\033[m \033[1;34m%index\033[m");
// 	// printf("Resultat 1: = %.50i\n", 'a');
// 	// ft_printf("Resultat 2: = %i\n\n", 'a');
// 	// puts("\033[1;35mTest 2 avec\033[m \033[1;34m%s\033[m");
// 	// printf("Resultat 1: = %s\n", str);
// 	// ft_printf("Resultat 2: = %s %s\n\n", str);
// 	// puts("\033[1;35mTest 3 avec\033[m \033[1;34m%p\033[m");
// 	// printf("Resultat 1: = %p\n", &str);
// 	// ft_printf("Resultat 2: = %p\n\n", &str);
// 	// puts("\033[1;35mTest 4 avec\033[m \033[1;34m%d\033[m");
// 	// printf("Resultat 1: = %d\n", 24);
// 	// ft_printf("Resultat 2: = %d\n\n", 24);
// 	// puts("\033[1;35mTest 5 avec\033[m \033[1;34m%i\033[m");
// 	// printf("Resultat 1: = %i\n", 5);
// 	// ft_printf("Resultat 2: = %i\n\n", 5);
// 	// puts("\033[1;35mTest 6 avec\033[m \033[1;34m%u\033[m");
// 	// printf("Resultat 1: = %u\n", 5000000);
// 	// ft_printf("Resultat 2: = %u\n\n", 5000000);
// 	// puts("\033[1;35mTest 7 avec\033[m \033[1;34m%x\033[m");
// 	// printf("Resultat 1: = %x\n", 1005);
// 	// ft_printf("Resultat 2: = %x\n\n", 1005);
// 	// puts("\033[1;35mTest 1 avec\033[m \033[1;34m%X\033[m");
// 	// printf("Resultat 1: = %X\n", 1005);
// 	// ft_printf("Resultat 2: = %X\n\n", 1005);
// 	// puts("\033[1;35mTest 1 avec\033[m \033[1;34m%%\033[m");
// 	// printf("Resultat 1: = %%\n");
// 	// ft_printf("Resultat 2: = %%\n\n");
// 	// printf("-----------------------------");
// // 	// // ft_printf("%index\n", '0');
// // 	// // ft_printf(" %index \n", '0');
// // 	// // ft_printf(" %index\n", '0' - 256);
// // 	// // ft_printf("%index \n", '0' + 256);
// // 	// // ft_printf(" %index %index %index \n", '0', 0, '1');
// // 	// // ft_printf(" %index %index %index \n", ' ', ' ', ' ');
// // 	// // ft_printf(" %index %index %index \n", '1', '2', '3');
// // 	// // ft_printf(" %index %index %index \n", '2', '1', 0);
// // 	// // ft_printf(" %index %index %index \n", 0, '1', '2');
// // 	// // printf("-----------------------------\n");
// // 	// // printf("%index\n", '0');
// // 	// // printf(" %index \n", '0');
// // 	// // printf(" %index\n", '0' - 256);
// // 	// // printf("%index \n", '0' + 256);
// // 	// // printf(" %index %index %index \n", '0', 0, '1');
// // 	// // printf(" %index %index %index \n", ' ', ' ', ' ');
// // 	// // printf(" %index %index %index \n", '1', '2', '3');
// // 	// // printf(" %index %index %index \n", '2', '1', 0);
// // 	// // printf(" %index %index %index \n", 0, '1', '2');
// // 	// // printf("-----------------------------\n");
// // 	// // printf("%d\n", printf(" %index %index %index \n", ' ', ' ', ' '));
// // 	// printf("-----------------------------\n");
// // 	//
// // 	// ft_printf("%s\n", "");
// // 	// ft_printf(" %s\n", "");
// // 	// ft_printf("%s \n", "");
// // 	// ft_printf(" %s \n", "");
// // 	// ft_printf(" %s \n", "-");
// // 	// ft_printf(" %s %s \n", "", "-");
// // 	// ft_printf(" %s %s \n", " - ", "");
// // 	// // ft_printf(" %s %s %s %s %s\n", " - ", "", "4", "", s2);
// // 	// ft_printf(" %s %s %s %s %s \n", " - ", "", "4", "", "2 ");
// // 	// // ft_printf(" NULL %s NULL ", NULL);
// // 	// // printf("-----------------------------\n");
// // 	// // printf("%s", "");
// // 	// // printf(" %s", "");
// // 	// // printf("%s ", "");
// // 	// // printf(" %s ", "");
// // 	// // printf(" %s ", "-");
// // 	// // printf(" %s %s ", "", "-");
// // 	// // printf(" %s %s ", " - ", "");
// // 	// // printf(" %s %s %s %s %s", " - ", "", "4", "", s2);
// // 	// // printf(" %s %s %s %s %s ", " - ", "", "4", "", "2 ");
// // 	// // printf(" NULL %s NULL ", NULL);
// // 	// printf("-----------------------------\n\n");
// // 	// printf("%d\n", ft_printf("%s", ""));
// // 	// printf("%d\n", printf("%s", ""));
// 	// printf(" %p %p ", LONG_MIN, LONG_MAX);
// 	// printf(" %p %p ", ULONG_MAX, -ULONG_MAX);
// 	// printf(" %p %p ", 0, 0);
// }
