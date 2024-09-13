/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarin-j <rmarin-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 17:33:49 by rmarin-j          #+#    #+#             */
/*   Updated: 2024/09/13 20:08:23 by rmarin-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H


# include <unistd.h>
# include <stddef.h>
# include <stdlib.h>
# include <stdio.h>
# include <limits.h>
# include <pthread.h>
# include <sys/time.h>
# include <sys/types.h>
# include <sys/wait.h>

# define FORK "has taken a fork\n"
# define THINK "is thinking \n"
# define SLEEP "is sleeping\n"
# define DEAD "died\n"
# define EAT "is eating\n"


typedef struct s_table
{
	int	t_eat;
	int	t_sleep;
	int	t_die;
	int	count;
	int death;
	int	n_meals;
	long	start;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print;

}	t_table;

typedef struct s_philo
{
	int	nb;
	int	last_food;
	int	times_eat;
	pthread_mutex_t	own_fork;
	pthread_mutex_t	r_fork;
	pthread_t	thread;
	struct s_table *table;

}	t_philo;


/*----------philo----------*/
t_table	*table_init(char **argv);
void	*routine(void *param);
t_philo	*philo_init(t_table *table);
void	mutex_init(t_table *table);
/*------------times------------*/
long	get_now(void);
long	time_diff(long past, long now);
 int	check_death(t_philo * philo);
/*----------utils----------*/
int		ft_atoi(const char *str);
void	ft_error(char *text);
void	ft_wdoing(t_philo *philo, char *doing);

#endif