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


/* int	check_argvs(char **argv)
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
} */

void	routine(t_table *table) //¿necesitara el philo especifico?
{
	while(table->death == 0)
	{
	//if (ft_comen(t_eat)) tiene q chekear  los tenedore,si no  puede comer pasa  a  pensar;
		//usleep(50); ta pensando
	
	usleep(table->t_sleep);//duerme, necesita algo  mas?
	//ft_printeacion(table->text);
	}
}

 void	table_init(t_table *table, char **argv)
{
	/*table = malloc(sizeof(t_table));
	if (!table)
		ft_error("fail malloc of the table struct\n");*/
	table->count = ft_atoi(argv[1]);
	table->t_die = ft_atoi(argv[2]);
	table->t_eat = ft_atoi(argv[3]);
	table->t_sleep = ft_atoi(argv[4]);
	table->start = get_now();
	table->death = 0;
	if (table->t_die < 0 || table->t_sleep < 0 || table->t_eat < 0 || table->count < 2)
		ft_error ("Arguments aren't valid\n");
	if (argv[5])
	{
		if ((table->n_meals = ft_atoi(argv[5])) < 0)
			ft_error("Arguments can`t be negative\n");
	}
	else
		table->n_meals = -1;
	mutex_init(table);
	philo_init(table);
	
}

void	mutex_init(t_table *table)
{
	
}

 void	philo_init(t_table *table)
{
	int	i;

	i = table->count;
	while (i > 0)
	{
		table->philos[i] = i;
		table->philos[i]->
		//philo->thread = funcion inicio thread?
		i--;
	}
	

	
}

int	main(int argc, char **argv)
{
	t_table table;
	//t_philo philo;

	if(argc == 5 || argc == 6)
	{
		//if (!check_argvs(argv));
			//mensaje error;
		table = table__init(&table, argv);
	}
	else
		ft_error("argument count is not correct\n")
	return (0);
}