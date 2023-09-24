/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dinner_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-e <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 18:51:21 by tpinto-e          #+#    #+#             */
/*   Updated: 2023/09/12 18:51:23 by tpinto-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philos.h"

/**
 * @brief alters the behaviour that some philosophers start with, 
 * making odd numbered philosophers eat immediately (except
 * when there are an odd number of philosophers, where the last
 * one will also have to wait)
 * @param t_philo* philosopher struct
 * @param int number assigned to philosopher
 * @param int number of philosophers
*/
void	start_behaviour(t_philo *philo, int number, int max_number)
{
	if ((max_number % 2 == 0 && number % 2 != 0) || \
		(max_number % 2 != 0 && number != max_number && number % 2 != 0))
	{
		pthread_mutex_lock(&philo->fork);
		announcement(philo, 3);
		pthread_mutex_lock(&philo->prev->fork);
		announcement(philo, 3);
		got_food(philo);
	}
}

/**
 * @brief checks if the thread may continue
 * @param t_info struct that contains stop condition
*/
int	continue_check(t_info *info)
{
	int	ret;

	pthread_mutex_lock(info->muted);
	ret = 1;
	if (info->stop == 1)
		ret = 0;
	pthread_mutex_unlock(info->muted);
	return (ret);
}

/**
 * @brief has the philosopher attempt to grab the forks
 * while attempting to respect mutex order so as to avoid
 * lock order inversion
 * @param t_philo* a philosopher
 * @param int number assigned to philosopher
*/
void	get_fork(t_philo *philo, int philo_num)
{
	announcement(philo, 2);
	usleep(500);
	if (philo_num % 2 != 0)
	{
		pthread_mutex_lock(&philo->fork);
		announcement(philo, 3);
		pthread_mutex_lock(&philo->prev->fork);
		announcement(philo, 3);
	}
	else
	{
		pthread_mutex_lock(&philo->prev->fork);
		announcement(philo, 3);
		pthread_mutex_lock(&philo->fork);
		announcement(philo, 3);
	}
}

/**
 * @brief handles philosopher behaviour while eating and sleeping
 * @param t_philo* philosopher that is eating
*/
void	got_food(t_philo *philo)
{
	gettimeofday(&philo->start_hunger, NULL);
	announcement(philo, 0);
	usleep(philo->ancient_texts->time_eat * 1000);
	pthread_mutex_unlock(&philo->prev->fork);
	pthread_mutex_unlock(&philo->fork);
	announcement(philo, 1);
	usleep(philo->ancient_texts->time_sleep * 1000);
}

/**
 * @brief philosopher thread function,
 * stops when stop condition has been reached
 * @param t_philo* philosopher whose thread was created
 * @return NULL
*/
void	*dining(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	gettimeofday(&philo->start_hunger, NULL);
	start_behaviour(philo, philo->number, philo->ancient_texts->num);
	while (continue_check(philo->ancient_texts))
	{
		get_fork(philo, philo->number);
		got_food(philo);
	}
	return (NULL);
}
