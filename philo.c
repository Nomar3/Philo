/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rmarin-j <rmarin-j@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/04 18:53:14 by rmarin-j          #+#    #+#             */
/*   Updated: 2024/09/06 17:39:35 by rmarin-j         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


int	check_argvs(char **argv)
{
	int	i;
	int	j;

	i = 1;
	while (argv[i])
	{
		j = 0;
		while (argv[i][j])
		{
			if (argv[i][j] < '0' || argv[i][j] > '9')
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

 void	table_init(t_table *table, char **argv)
{
	table = malloc(sizeof(t_table));
	if (!table)
		ft_error("fail malloc of the table struct\n");
	table->start = get_now();
	table->count = ft_atoi(argv[1]);
	table->t_die = ft_atoi(argv[2]);
	table->t_eat = ft_atoi(argv[3]);
	table->t_sleep = ft_atoi(argv[4]);
	
}

 void	philo_init(t_philo *philo, char **argv)
{
	int	i;
	int	count;

	i = 1;
	count = ft_atoi(argv[1]);
	while (i != count)
	{
		philo->nb = count;
		//philo->thread = funcion inicio thread?
		i++;
	}
	

	
}

int	main(int argc, char **argv)
{
	t_table table;
	t_philo philo;

	if(argc == 5 || argc == 6)
	{
		//if (!check_argvs(argv));
			//mensaje error;
		table = table__init(&table, argv);
		//philo_init(&philo, argv);
	}
	else
		ft_error("argument count is not correct\n")
	return (0);
}