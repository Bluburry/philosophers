/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-e <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 20:07:38 by tpinto-e          #+#    #+#             */
/*   Updated: 2023/09/18 20:07:39 by tpinto-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philos_bonus.h"

/**
 * @brief initiates the child processes and 
 * waits for them to finish
 * 
 * @param t_info info structure
 */
void	debate(t_info info)
{
	int		i;
	int		pid;
	t_philo	*temp;

	i = -1;
	while (++i < info.num)
	{
		temp = init_philosopher(i, info);
		pid = fork();
		if (!pid && info.num != 1)
			start_process(temp);
		else if (!pid && info.num == 1)
			solo_dinner(temp);
		free(temp);
	}
	i = -1;
	while (++i < info.num)
		waitpid(0, NULL, 0);
	clear_all(info);
}

int	main(int argc, char **argv)
{
	if (argc < 5 || argc > 6 || !validate_input(argc, argv))
		return (0);
	debate(create_literature(argc, argv));
	return (0);
}
