/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-e <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 20:30:08 by tpinto-e          #+#    #+#             */
/*   Updated: 2023/09/18 20:30:10 by tpinto-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philos.h"

int	validate_input(int num, char **strs)
{
	int	i;
	int	j;

	i = 0;
	while (++i < num)
	{
		j = -1;
		while (strs[i][++j])
			if (!ft_isdigit(strs[i][j]))
				return (0);
		if (!over_checker(strs[i]))
			return (0);
	}
	return (1);
}

int	over_checker(const char *str)
{
	int	number;
	int	i;

	number = 0;
	i = 1;
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-')
	{
		i *= -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (*str != '\0' && *str <= 57 && *str >= 48)
	{
		if (number > 214748364 || (number == 214748364 && *str - 48 > 7))
			return (0);
		number *= 10;
		number += *str - 48;
		str++;
	}
	return (1);
}

int	ft_isdigit(int c)
{
	if (!(c >= '0' && c <= '9'))
		return (0);
	return (1);
}

int	ft_atoi(const char *str)
{
	int	number;
	int	i;

	number = 0;
	i = 1;
	while (*str == 32 || (*str >= 9 && *str <= 13))
		str++;
	if (*str == '-')
	{
		i *= -1;
		str++;
	}
	else if (*str == '+')
		str++;
	while (*str != '\0' && *str <= 57 && *str >= 48)
	{
		number *= 10;
		number += *str - 48;
		str++;
	}
	return (number * i);
}
