/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-e <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 20:09:51 by tpinto-e          #+#    #+#             */
/*   Updated: 2023/09/18 20:09:53 by tpinto-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philos_bonus.h"

/**
 * @brief utility function that prints the information 
 * on the philosopher that called it
 * @param t_philo philosopher
*/
void	print_philo(t_philo *philo)
{
	sem_wait(philo->ancient_texts.muted);
	printf("Philosopher number %d ", philo->number);
	printf("time to die: %d ", philo->ancient_texts.time_die);
	printf("time to eat: %d ", philo->ancient_texts.time_eat); 
	printf("time to sleep: %d ", philo->ancient_texts.time_sleep);
	printf("number of times to eat: %d\n", philo->ancient_texts.times_eat);
	sem_post(philo->ancient_texts.muted);
}
