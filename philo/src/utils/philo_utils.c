/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-e <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 18:51:50 by tpinto-e          #+#    #+#             */
/*   Updated: 2023/09/12 18:51:51 by tpinto-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philos.h"

/**
 * @brief utility function that loops throught the 
 * circular list to print all philosophers
 * @param t_ctrl control structure
*/
void	list_philos(t_ctrl *ctrl)
{
	int		i;
	t_philo	*temp;

	temp = ctrl->philos;
	i = -1;
	while (++i < ctrl->info.num)
	{
		printf("Philosopher number %d ", temp->number);
		printf("time to die: %d ", temp->ancient_texts->time_die);
		printf("time to eat: %d ", temp->ancient_texts->time_eat); 
		printf("time to sleep: %d ", temp->ancient_texts->time_sleep);
		printf("number of times to eat: %d\n", temp->ancient_texts->times_eat);
		temp = temp->next;
	}
}

/**
 * @brief utility function that prints the information 
 * on the philosopher that called it
 * @param t_philo philosopher
*/
void	print_philo(t_philo *philo)
{
	pthread_mutex_lock(philo->ancient_texts->muted);
	printf("Philosopher number %d ", philo->number);
	printf("time to die: %d ", philo->ancient_texts->time_die);
	printf("time to eat: %d ", philo->ancient_texts->time_eat); 
	printf("time to sleep: %d ", philo->ancient_texts->time_sleep);
	printf("number of times to eat: %d\n", philo->ancient_texts->times_eat);
	pthread_mutex_unlock(philo->ancient_texts->muted);
}
