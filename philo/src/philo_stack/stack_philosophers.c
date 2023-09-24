/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_philosophers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-e <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 18:51:02 by tpinto-e          #+#    #+#             */
/*   Updated: 2023/09/12 18:51:03 by tpinto-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philos.h"

/**
 * @brief initiates a single philosopher
 * @param int philosopher number
 * @param t_ctrl control structure
 * @return philosopher
*/
t_philo	*init_philosopher(int num, t_ctrl *ctrl)
{
	t_philo	*philo;

	philo = (t_philo *) malloc(sizeof(t_philo));
	philo->number = num + 1;
	philo->times_eaten = 0;
	philo->full = 0;
	philo->eating = 0;
	philo->prev = NULL;
	philo->next = NULL;
	philo->ancient_texts = &(ctrl->info);
	pthread_mutex_init(&(philo->fork), NULL);
	return (philo);
}

/**
 * @brief initiates a double circular linked list of philosophers
 * @param int total number of philosophers
 * @param t_ctrl control structure
 * @return first philosopher
*/
t_philo	*create_philos(int num_philos, t_ctrl *ctrl)
{
	t_philo	*philo;
	t_philo	*temp;
	int		num;

	num = 0;
	philo = init_philosopher(num, ctrl);
	while (++num < num_philos)
	{
		temp = init_philosopher(num, ctrl);
		philo->next = temp;
		temp->prev = philo;
		philo = philo->next;
	}
	if (num_philos > 1)
	{
		temp = philo;
		while (philo->number != 1)
			philo = philo->prev;
		temp->next = philo;
		philo->prev = temp;
	}
	return (philo);
}
