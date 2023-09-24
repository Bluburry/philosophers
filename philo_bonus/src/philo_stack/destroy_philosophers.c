/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_philosophers.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-e <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 20:07:58 by tpinto-e          #+#    #+#             */
/*   Updated: 2023/09/18 20:07:59 by tpinto-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/philos_bonus.h"

/**
 * @brief clears t_info struct semaphores
 * @param t_info info struct
*/
void	clear_all(t_info info)
{
	if (info.forks != NULL)
		sem_close(info.forks);
	if (info.muted != NULL)
		sem_close(info.muted);
	if (info.close != NULL)
		sem_close(info.close);
	exit (0);
}
