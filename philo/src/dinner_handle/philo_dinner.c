/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_dinner.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-e <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 18:51:30 by tpinto-e          #+#    #+#             */
/*   Updated: 2023/09/12 18:51:31 by tpinto-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philos.h"

/**
 * @brief prints a message according to chosen option:  
 * 0 - eating, 
 * 1 - sleeping, 
 * 2 - thinking, 
 * 3 - taken a fork
 * 
 * @param t_philo* philosopher that has performed an action
 * @param int option to print
*/
void	announcement(t_philo *philo, int opt)
{
	pthread_mutex_lock(philo->ancient_texts->muted);
	if (philo->ancient_texts->stop != 1)
	{
		printf("%ld %d ", timer_handler(philo->ancient_texts->start_time), \
			philo->number);
		if (opt == 0)
		{
			printf("is eating\n");
			philo->times_eaten++;
			philo->eating = 1;
		}
		else if (opt == 1)
		{
			printf("is sleeping\n");
			philo->eating = 0;
		}
		else if (opt == 2)
			printf("is thinking\n");
		else if (opt == 3)
			printf("has taken a fork\n");
	}
	pthread_mutex_unlock(philo->ancient_texts->muted);
}

/**
 * @brief starts the philosophers threads and stop checker thread
 * @param t_ctrl controller structure that holds all the information
*/
void	start_dinner(t_ctrl *ctrl)
{
	int		i;
	t_philo	*temp;

	i = -1;
	temp = ctrl->philos;
	gettimeofday(&ctrl->info.start_time, NULL);
	while (++i < ctrl->info.num)
	{
		pthread_create(&(temp->thread), NULL, &dining, temp);
		if (i % 2 != 0)
			usleep(100);
		temp = temp->next;
	}
	pthread_create(&(ctrl->stop_thread), NULL, &stop_checker, temp);
	pthread_detach(ctrl->stop_thread);
	i = -1;
	temp = ctrl->philos;
	while (++i < ctrl->info.num)
	{
		pthread_join(temp->thread, NULL);
		temp = temp->next;
	}
}
