/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lonely_philosopher.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-e <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 20:09:02 by tpinto-e          #+#    #+#             */
/*   Updated: 2023/09/18 20:09:03 by tpinto-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philos_bonus.h"

/**
 * @brief alternative handler for when there is only 1 philosopher
 * 
 * @param t_philo philosopher struct
 */
void	solo_dinner(t_philo *philo)
{
	gettimeofday(&philo->ancient_texts.start_time, NULL);
	gettimeofday(&philo->start_hunger, NULL);
	announcement(philo, 2);
	sem_wait(philo->ancient_texts.forks);
	announcement(philo, 3);
	usleep(philo->ancient_texts.time_die * 1000);
	sem_wait(philo->ancient_texts.muted);
	printf("%ld %d died\n", timer_handler(philo->ancient_texts.start_time), \
		philo->number);
	sem_post(philo->ancient_texts.muted);
	sem_post(philo->ancient_texts.forks);
}
