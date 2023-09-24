/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-e <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 18:51:45 by tpinto-e          #+#    #+#             */
/*   Updated: 2023/09/12 18:51:46 by tpinto-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philos.h"

/**
 * @brief warns of philosopher death and activates stop condition
 * @param t_philo* philo that died
*/
void	funeral_bell(t_philo *philo)
{
	pthread_mutex_lock(philo->ancient_texts->muted);
	if (philo->ancient_texts->stop != 1)
	{
		if (philo->eating == 0 || (philo->eating == 1 && \
			timer_handler(philo->start_hunger) >= \
			philo->ancient_texts->time_die))
		{
			philo->ancient_texts->stop = 1;
			printf("%ld %d died\n", \
				timer_handler(philo->ancient_texts->start_time), \
					philo->number);
		}
	}
	pthread_mutex_unlock(philo->ancient_texts->muted);
}

/***
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

/***
 * @brief Function checks if the program has satisfied stop conditions, 
 * by using a static variable to count how many philosophers
 * have eaten their fill
 * @param t_philo* a philosopher
 * @param int total number of philosophers
 * @param int times a philo must eat before the program can stop
 * @return 1 to stop the program, 0 to continue
*/
int	satiated_check(t_philo *philo, int num_p, int t_eat)
{
	static int	satiated = 0;

	pthread_mutex_lock(philo->ancient_texts->muted);
	if (philo->times_eaten >= t_eat && !philo->full)
	{
		philo->full = 1;
		satiated++;
	}
	pthread_mutex_unlock(philo->ancient_texts->muted);
	if (satiated < num_p)
		return (0);
	else
	{
		pthread_mutex_lock(philo->ancient_texts->muted);
		if (philo->ancient_texts->stop != 1)
			philo->ancient_texts->stop = 1;
		pthread_mutex_unlock(philo->ancient_texts->muted);
		return (1);
	}
}

/***
 * @brief Function checks if the program has satisfied stop conditions, 
 * checking if the philosophers have eaten enough, 
 * as well as checking if any of them have
 * surpassed how long they can survive without eating
 * @param t_philo* a philosopher
 * @param int total number of philosophers
 * @param int time it takes for the philosopher to die of hunger
 * @param int times a philo must eat before the program can stop
 * @return 1 to stop the program, 0 to continue
*/
int	stop_check(t_philo *philo, int num_p, int d_time, int t_eat)
{
	if (timer_handler(philo->start_hunger) >= d_time)
	{
		funeral_bell(philo);
		return (1);
	}
	else if (t_eat == -1)
		return (0);
	else
		return (satiated_check(philo, num_p, t_eat));
}

/**
 * @brief thread function that constantly checks if the threads should stop, 
 * checks both if a philosopher dies and if all of
 * them have eaten enough
 * @param t_philo* any philosopher
 * @return NULL
*/
void	*stop_checker(void *arg)
{
	t_philo	*philo;
	int		num;
	int		ttd;
	int		tte;

	philo = (t_philo *)arg;
	num = philo->ancient_texts->num;
	ttd = philo->ancient_texts->time_die;
	tte = philo->ancient_texts->times_eat;
	while (1)
	{
		if (stop_check(philo, num, ttd, tte))
			break ;
		philo = philo->next;
	}
	return (NULL);
}
