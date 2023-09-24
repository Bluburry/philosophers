/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-e <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 20:09:44 by tpinto-e          #+#    #+#             */
/*   Updated: 2023/09/18 20:10:59 by tpinto-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philos_bonus.h"

/**
 * @brief returns difference between given time and current time
 * @param timeval timeval to use as comparison
 * @return time difference in miliseconds
*/
long	timer_handler(struct timeval time)
{
	struct timeval	c_time;
	long			diff;

	gettimeofday(&c_time, NULL);
	diff = ((c_time.tv_sec * 1000) + (c_time.tv_usec / 1000)) \
		- ((time.tv_sec * 1000) + (time.tv_usec / 1000));
	return (diff);
}

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
	sem_wait(philo->ancient_texts.muted);
	if (philo->stop == 1)
	{
		sem_post(philo->ancient_texts.muted);
		return ;
	}
	printf("%ld %d ", timer_handler(philo->ancient_texts.start_time), \
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
	sem_post(philo->ancient_texts.muted);
}

/**
 * @brief checks if the philosopher processes and chcker 
 * thread can continue based on a stop condition saved 
 * to the t_philo struct
 * 
 * @param t_philo philosopher struct to check
 * @return 1 to continue, 0 to stop
 */
int	continue_check(t_philo *philo)
{
	int	ret;

	sem_wait(philo->ancient_texts.muted);
	ret = philo->stop;
	sem_post(philo->ancient_texts.muted);
	return (!ret);
}

/**
 * @brief handles the start behaviour for the processes, 
 * launching the detachd threads and starting the necessary timers
 * 
 * @param t_philo* philospher struct
 */
void	start_process(t_philo *philo)
{
	gettimeofday(&philo->ancient_texts.start_time, NULL);
	gettimeofday(&philo->start_hunger, NULL);
	pthread_create(&philo->checker, NULL, &oversee, philo);
	pthread_detach(philo->checker);
	pthread_create(&philo->stopper, NULL, &wait_close, philo);
	pthread_detach(philo->stopper);
	dinner(philo);
}

/**
 * @brief rudimentary function to check if the philosopher 
 * can die based on the passed parameters
 * 
 * @param t_philo* philosopher struct
 * @return 1 if it's possible for the philosopher to die 
 * with the set parameters
 */
int	philo_may_die(t_philo *philo)
{
	int	ttd;
	int	tte;
	int	tts;

	ttd = philo->ancient_texts.time_die;
	tte = philo->ancient_texts.time_eat;
	tts = philo->ancient_texts.time_sleep;
	return (tte * 2 >= ttd || tte + tts >= ttd);
}
