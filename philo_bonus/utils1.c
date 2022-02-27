/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlamonic <jlamonic@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 23:06:53 by jlamonic          #+#    #+#             */
/*   Updated: 2022/01/06 23:40:43 by jlamonic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	philo_alloc(t_all *all)
{
	all->philo = malloc(sizeof(*all->philo) * all->table->philo_num);
	if (!all->philo)
		return (-1);
	if (sem_create(all))
		return (1);
	return (0);
}

int	argv_parsing(t_tab *table, char **argv)
{
	table->philo_num = ft_atoi(argv[1]);
	table->time_to_die = ft_atoi(argv[2]);
	table->time_to_eat = ft_atoi(argv[3]);
	table->time_to_sleep = ft_atoi(argv[4]);
	if (argv[5])
	{
		table->num_to_eat = ft_atoi(argv[5]);
		if (table->num_to_eat == 0)
			return (1);
	}
	else
		table->num_to_eat = INT_MAX;
	if (table->philo_num <= 0 || table->time_to_die <= 0 \
		|| table->time_to_eat <= 0 || table->time_to_sleep <= 0)
		return (1);
	return (0);
}

int	sem_create(t_all *all)
{
	all->table->pfork = sem_open("forks", O_CREAT, \
		S_IRWXU, all->table->philo_num);
	if (all->table->pfork == 0)
		return (1);
	all->table->message = sem_open("message", O_CREAT, S_IRWXU, 1);
	if (all->table->message == 0)
		return (1);
	sem_unlink("forks");
	sem_unlink("message");
	return (0);
}

void	kill_process(t_all *all)
{
	int	i;

	i = 0;
	while (i < all->table->philo_num)
	{
		kill(all->philo[i].pid, SIGKILL);
		i++;
	}
}

int	ft_thread_detach(t_all *all)
{
	int	i;

	i = 0;
	while (i < all->table->philo_num)
	{
		if (pthread_detach(all->philo[i].thread_id))
			return (-1);
		i++;
	}
	return (0);
}
