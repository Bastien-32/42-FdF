/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi_base.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: badal-la <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 12:13:17 by badal-la          #+#    #+#             */
/*   Updated: 2025/02/04 15:05:17 by badal-la         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	fill_result(char *str, char *base, int i)
{
	int	result;
	
	result = 0;
	while (str[i])
	{
		if (str[i] >= '0' && str[i] <= '9')
			result = result * ft_strlen(base) + (str[i] - '0');
		else if (str[i] >= 'A' && str[i] <= 'F')
			result = result * ft_strlen(base) + (str[i] - 'A' + 10);
		else if (str[i] >= 'a' && str[i] <= 'f')
			result = result * ft_strlen(base) + (str[i] - 'a' + 10);
		else
			break ;
		i++;
	}
	return (result);
}

int	ft_atoi_base(char *str, char *base)
{
	int		i;
	int		result;
	int		sign;

	i = 0;
	sign = 1;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	if (str[i] == '0' && (str[i + 1] == 'x' || str[i + 1] == 'X'))
		i += 2;
	result = fill_result(str, base, i);
	return (result * sign);
}
