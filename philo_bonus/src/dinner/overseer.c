/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   overseer.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-e <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 20:09:08 by tpinto-e          #+#    #+#             */
/*   Updated: 2023/09/18 20:10:46 by tpinto-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philos_bonus.h"

/**
 * @brief warns of philosopher death and activates stop condition
 * @param t_philo* philo that died
*/
void	funeral_bell(t_philo *philo)
{
	if (!philo->stop)
	{
		if (philo->eating == 0 || (philo->eating == 1 && \
			timer_handler(philo->start_hunger) >= \
			philo->ancient_texts.time_die))
		{
			philo->stop = 1;
			printf("%ld %d died\n", \
				timer_handler(philo->ancient_texts.start_time), \
				philo->number);
			sem_post(philo->ancient_texts.close);
		}
	}
}

/**
 * @brief Function checks if the program has satisfied stop conditions, 
 * checking if the philosophers have eaten enough, 
 * as well as checking if any of them have
 * surpassed how long they can survive without eating
 * @param t_philo* a philosopher
 * @param int total number of philosophers
 * @param int time it takes for the philosopher to die of hunger
 * @param int times a philo must eat before the program can stop
 * @return 1 to stop the program, 0 to continue
 * @bug sometimes triggers the stop condition on having eaten enough
 * times without that actually being the case
*/
void	stop_check(t_philo *philo, int d_time, int t_eat)
{
	sem_wait(philo->ancient_texts.muted);
	if (timer_handler(philo->start_hunger) >= d_time)
		funeral_bell(philo);
	else if (t_eat != -1 && philo->times_eaten >= t_eat)
		philo->stop = 1;
	sem_post(philo->ancient_texts.muted);
}

/**
 * @brief continously checks philosopher timer and 
 * how many times it ate (if it's relevant) to 
 * determine if the process should stop
 * 
 * @param void* philospher struct 
 * @return NULL
 */
void	*oversee(void *arg)
{
	t_philo	*philo;
	int		ttd;
	int		tte;

	philo = (t_philo *)arg;
	ttd = philo->ancient_texts.time_die;
	tte = philo->ancient_texts.times_eat;
	while (continue_check(philo))
		stop_check(philo, ttd, tte);
	return (NULL);
}

/**
 * @brief waits for the death semaphore so it 
 * can stop the ongoing process and thread
 * 
 * @param void* philosopher struct 
 * @return NULL
 */
void	*wait_close(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (!philo_may_die(philo))
		return (NULL);
	sem_wait(philo->ancient_texts.close);
	sem_wait(philo->ancient_texts.muted);
	if (!philo->stop)
		philo->stop = 1;
	sem_post(philo->ancient_texts.close);
	sem_post(philo->ancient_texts.muted);
	return (NULL);
}
