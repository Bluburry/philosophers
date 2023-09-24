/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_dinner.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-e <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 20:09:26 by tpinto-e          #+#    #+#             */
/*   Updated: 2023/09/18 20:09:27 by tpinto-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philos_bonus.h"

/**
 * @brief helps with process start, making sure there is 
 * no issue at the start of the process, such as all 
 * philosophers taking a fork at the same time
 * 
 * @param t_philo* philosopher struct
 * @param int philosopher number
 * @param int total number of philosophers
 */
void	start_behaviour(t_philo *philo, int num, int max)
{
	if ((num % 2 == 0) || \
		(max % 2 != 0 && num == max))
	{
		announcement(philo, 2);
		usleep(philo->ancient_texts.time_eat * 1000);
		return ;
	}
	npc_behaviour(philo);
	announcement(philo, 1);
	usleep(philo->ancient_texts.time_sleep * 1000);
}

/**
 * @brief handles the philospher behaviour as it is 
 * trying to get forks to eat
 * 
 * @param t_philo* philosopher struct
 */
void	npc_behaviour(t_philo *philo)
{
	sem_wait(philo->ancient_texts.forks);
	announcement(philo, 3);
	sem_wait(philo->ancient_texts.forks);
	announcement(philo, 3);
	gettimeofday(&philo->start_hunger, NULL);
	announcement(philo, 0);
	usleep(philo->ancient_texts.time_eat * 1000);
	sem_post(philo->ancient_texts.forks);
	sem_post(philo->ancient_texts.forks);
}

/**
 * @brief loops the process behaviour
 * 
 * @param t_philo* philosopher struct*
 */
void	dinner(t_philo *philo)
{
	start_behaviour(philo, philo->number, \
		philo->ancient_texts.num);
	while (continue_check(philo))
	{
		if (philo->times_eaten != 0)
			announcement(philo, 2);
		npc_behaviour(philo);
		announcement(philo, 1);
		usleep(philo->ancient_texts.time_sleep * 1000);
	}
	clear_all(philo->ancient_texts);
	free(philo);
	exit(0);
}
