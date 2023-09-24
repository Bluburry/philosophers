/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tpinto-e <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 20:07:30 by tpinto-e          #+#    #+#             */
/*   Updated: 2023/09/18 20:07:32 by tpinto-e         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOS_BONUS_H
# define PHILOS_BONUS_H

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

# define SEM_FORKS	"semaphore_forks"
# define SEM_MUTE	"semaphore_mute"
# define SEM_CLOSE	"semaphore_close"
# define PHILO_DIED	256

typedef struct s_info
{
	int				num;
	int				time_die;
	int				time_eat;
	int				time_sleep;
	int				times_eat;
	sem_t			*muted;
	sem_t			*forks;
	sem_t			*close;
	struct timeval	start_time;
}	t_info;

typedef struct s_philosophers
{
	int				number;
	int				stop;
	int				eating;
	int				times_eaten;
	t_info			ancient_texts;
	pthread_t		checker;
	pthread_t		stopper;
	struct timeval	start_hunger;
}	t_philo;

int		ft_isdigit(int c);
int		ft_atoi(const char *str);
int		philo_may_die(t_philo *philo);
int		over_checker(const char *str);
int		continue_check(t_philo *philo);
int		validate_input(int num, char **strs);
long	timer_handler(struct timeval time);
void	debate(t_info info);
void	dinner(t_philo *philo);
void	clear_all(t_info info);
void	solo_dinner(t_philo *philo);
void	print_philo(t_philo *philo);
void	funeral_bell(t_philo *philo);
void	start_process(t_philo *philo);
void	npc_behaviour(t_philo *philo);
void	announcement(t_philo *philo, int opt);
void	start_behaviour(t_philo *philo, int num, int max);
void	stop_check(t_philo *philo, int d_time, int t_eat);
void	*oversee(void *arg);
void	*wait_close(void *arg);
t_info	create_literature(int argc, char **argv);
t_philo	*init_philosopher(int num, t_info info);

#endif
