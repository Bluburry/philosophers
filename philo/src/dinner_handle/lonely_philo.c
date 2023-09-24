/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lonely_philo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-e <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 18:51:12 by tpinto-e          #+#    #+#             */
/*   Updated: 2023/09/12 18:51:13 by tpinto-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philos.h"

/**
 * @brief checks stop condition for 1 philosopher
 * @param t_philo* philosopher
 * @param int time to die
 * @return 0 to stop, 1 to continue
*/
int	lonely_stop(t_philo *philo, int d_time)
{
	if (timer_handler(philo->start_hunger) >= d_time)
		return (0);
	else
		return (1);
}

/**
 * @brief handles the thread behavious when there is 
 * only one philosopher
 * @param void* pointer to philosopher to be used in the function
 * @return NULL
*/
void	*lonely_philo(void *arg)
{
	t_philo	*philo;
	int		ttd;

	philo = (t_philo *)arg;
	ttd = philo->ancient_texts->time_die;
	gettimeofday(&philo->start_hunger, NULL);
	announcement(philo, 2);
	announcement(philo, 3);
	while (1)
	{
		if (!lonely_stop(philo, ttd))
			break ;
	}
	printf("%ld %d died", timer_handler(philo->ancient_texts->start_time), \
		philo->number);
	return (NULL);
}

/**
 * @brief alternate behaviour for when there is only one philosopher
 * @param t_ctrl controller structure that holds all the information
*/
void	solo_dining(t_ctrl *ctrl)
{
	t_philo	*temp;

	temp = ctrl->philos;
	gettimeofday(&ctrl->info.start_time, NULL);
	pthread_create(&(temp->thread), NULL, &lonely_philo, temp);
	pthread_join(temp->thread, NULL);
}
