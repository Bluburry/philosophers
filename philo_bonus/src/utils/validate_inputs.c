/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_inputs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-e <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 20:34:20 by tpinto-e          #+#    #+#             */
/*   Updated: 2023/09/18 20:34:22 by tpinto-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philos_bonus.h"

/**
 * @brief validates program inputs for the purpose 
 * of this program
 * 
 * @param int argc 
 * @param char** argv
 * @return 1 if acceptable, 0 otherwise
 */
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
	}
	return (1);
}

/**
 * @brief checks if input is over max_int
 * @param char* string to check
*/
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

/**
 * @brief same function as isdigit
 * 
 * @param int character to check
 * @return 0 if not a digit, 1 otherwise
 */
int	ft_isdigit(int c)
{
	if (!(c >= '0' && c <= '9'))
		return (0);
	return (1);
}

/**
 * @brief same function and atoi, converts a string 
 * int a number
 * 
 * @param char* 
 * @return int 
 */
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
