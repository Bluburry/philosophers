/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-e <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/29 20:14:44 by tpinto-e          #+#    #+#             */
/*   Updated: 2023/08/29 20:25:37 by tpinto-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOS_H
# define PHILOS_H

# include <stdio.h>
# include <pthread.h>
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <semaphore.h>
# include <fcntl.h>
# include <sys/time.h> 
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>

typedef struct s_info
{
	int				num;
	int				stop;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				times_eat;
	struct timeval	start_time;
	pthread_mutex_t	*muted;
}	t_info;

typedef struct s_philosophers
{
	int						number;
	int						times_eaten;
	int						full;
	int						eating;
	t_info					*ancient_texts;
	struct s_philosophers	*next;
	struct s_philosophers	*prev;
	pthread_t				thread;
	pthread_mutex_t			fork;
	struct timeval			start_hunger;
}	t_philo;

typedef struct controller
{
	t_info			info;
	t_philo			*philos;
	pthread_t		stop_thread;
	pthread_mutex_t	muting;
}	t_ctrl;

int			ft_isdigit(int c);
int			ft_atoi(const char *str);
int			end_dinner(t_ctrl *ctrl);
int			continue_check(t_info *info);
int			over_checker(const char *str);
int			validate_input(int num, char **strs);
int			lonely_stop(t_philo *philo, int d_time);
int			satiated_check(t_philo *philo, int num_p, int t_eat);
int			stop_check(t_philo *philo, int num_p, int d_time, int t_eat);
long		timer_handler(struct timeval time);
void		got_food(t_philo *philo);
void		clear_ctrl(t_ctrl *ctrl);
void		list_philos(t_ctrl *ctrl);
void		solo_dining(t_ctrl *ctrl);
void		start_dinner(t_ctrl *ctrl);
void		print_philo(t_philo *philo);
void		funeral_bell(t_philo *philo);
void		announcement(t_philo *philo, int opt);
void		get_fork(t_philo *philo, int philo_num);
void		clear_philosophers(t_philo *philos, int num_philos);
void		start_behaviour(t_philo *philo, int number, int max_number);
void		*dining(void *arg);
void		*stop_checker(void *arg);
void		*lonely_philo(void *arg);
t_philo		*init_philosopher(int num, t_ctrl *ctrl);
t_philo		*create_philos(int num_philos, t_ctrl *ctrl);
t_ctrl		*odissey(int argc, char **argv);

#endif
