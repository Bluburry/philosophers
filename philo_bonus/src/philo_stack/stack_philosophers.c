/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_philosophers.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-e <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 20:08:04 by tpinto-e          #+#    #+#             */
/*   Updated: 2023/09/18 20:10:31 by tpinto-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philos_bonus.h"

/**
 * @brief initiates a single philosopher
 * @param int philosopher number
 * @param t_ctrl control structure
 * @return philosopher
*/
t_philo	*init_philosopher(int num, t_info info)
{
	t_philo	*philo;

	philo = (t_philo *) malloc(sizeof(t_philo));
	philo->number = num + 1;
	philo->times_eaten = 0;
	philo->stop = 0;
	philo->ancient_texts = info;
	return (philo);
}

/**
 * @brief Create a literature object from parameters
 * passed to program at launch
 * 
 * @param int argc 
 * @param char** argv 
 * @return t_info 
 */
t_info	create_literature(int argc, char **argv)
{
	t_info	info;

	info.num = ft_atoi(argv[1]);
	info.time_die = ft_atoi(argv[2]);
	info.time_eat = ft_atoi(argv[3]);
	info.time_sleep = ft_atoi(argv[4]);
	info.times_eat = -1;
	if (argc == 6)
		info.times_eat = ft_atoi(argv[5]);
	sem_unlink(SEM_FORKS);
	sem_unlink(SEM_MUTE);
	sem_unlink(SEM_CLOSE);
	info.forks = sem_open(SEM_FORKS, O_CREAT, O_RDWR, info.num);
	info.muted = sem_open(SEM_MUTE, O_CREAT, O_RDWR, 1);
	info.close = sem_open(SEM_CLOSE, O_CREAT, O_RDWR, 0);
	return (info);
}
