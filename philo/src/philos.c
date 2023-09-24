/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-e <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 18:49:13 by tpinto-e          #+#    #+#             */
/*   Updated: 2023/09/12 18:49:33 by tpinto-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philos.h"

/**
 * @brief initiates the controller structure
 * @param int number of arguments passed to program
 * @param char** arguments passed to program
 * @return controller structure
*/
t_ctrl	*odissey(int argc, char **argv)
{
	t_ctrl		*ctrl;

	ctrl = (t_ctrl *) malloc(sizeof(t_ctrl));
	pthread_mutex_init(&(ctrl->muting), NULL);
	ctrl->info.num = ft_atoi(argv[1]);
	ctrl->info.time_die = ft_atoi(argv[2]);
	ctrl->info.time_eat = ft_atoi(argv[3]);
	ctrl->info.time_sleep = ft_atoi(argv[4]);
	ctrl->info.times_eat = -1;
	if (argc == 6)
		ctrl->info.times_eat = ft_atoi(argv[5]);
	ctrl->info.stop = 0;
	ctrl->info.muted = &(ctrl->muting);
	ctrl->philos = create_philos(ctrl->info.num, ctrl);
	return (ctrl);
}

int	main(int argc, char **argv)
{
	t_ctrl		*ctrl;

	if (argc < 5 || argc > 6 || !validate_input(argc, argv))
		return (0);
	ctrl = odissey(argc, argv);
	if (ctrl->info.num == 1)
		solo_dining(ctrl);
	else
		start_dinner(ctrl);
	clear_ctrl(ctrl);
	return (0);
}
