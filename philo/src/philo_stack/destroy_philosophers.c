/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_philosophers.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-e <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 18:50:19 by tpinto-e          #+#    #+#             */
/*   Updated: 2023/09/12 18:50:21 by tpinto-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philos.h"

/**
 * @brief clears and deallocates all philosophers in 
 * the circular linked list
 * @param t_philo* pointer to first philosopher
 * @param int number of philosophers
*/
void	clear_philosophers(t_philo *philos, int num_philos)
{
	t_philo			*temp;
	t_philo			*helper;

	if (num_philos > 1)
	{
		temp = philos->next;
		while (temp != philos)
		{
			helper = temp;
			temp = temp->next;
			pthread_mutex_destroy(&(helper->fork));
			free(helper);
		}
	}
	else
	{
		pthread_mutex_destroy(&(philos->fork));
	}
	free(philos);
}

/**
 * @brief clears and deallocates control structure
 * @param t_ctrl control structure
*/
void	clear_ctrl(t_ctrl *ctrl)
{
	clear_philosophers(ctrl->philos, ctrl->info.num);
	pthread_mutex_destroy(&(ctrl->muting));
	free(ctrl);
	exit (0);
}
