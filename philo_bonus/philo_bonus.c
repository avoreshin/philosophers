/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlamonic <jlamonic@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 23:06:53 by jlamonic          #+#    #+#             */
/*   Updated: 2022/01/06 23:40:43 by jlamonic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	monitor(t_all *all, t_list *philo)
{
	while (1)
	{
		usleep (100);
		if (all->table->num_to_eat < philo->eat_times)
		{
			sem_wait(all->table->message);
			write (1, "Meal over", 9);
			sem_close(all->table->message);
			exit (1);
		}
		if (all->table->time_to_die < get_time() - philo->last_meal)
		{
			message (all, philo, "has died");
			exit (1);
		}
	}
}

int	child_process(t_all *all)
{
	if (pthread_create(&all->philo->thread_id, NULL, life, all))
		return (-1);
	monitor(all, all->philo);
	return (0);
}

int	fork_and_life(t_all *all)
{
	int	i;

	i = 0;
	all->table->start_time = get_time();
	while (i < all->table->philo_num)
	{
		usleep (50);
		all->philo_count = i;
		all->philo[i].pid = fork();
		if (all->philo[i].pid == 0)
		{
			if (child_process(all))
				return (1);
			exit (1);
		}
		else
			i++;
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_tab	table;
	t_all	all;

	all.table = &table;
	if (argc < 5 || argc > 6)
		error("Wrong number of arguments");
	if (argv_parsing(&table, argv))
		error("Wrong argument");
	if (philo_alloc(&all))
		error("Allocation failed");
	if (fork_and_life(&all))
		error("Failed to fork()");
	wait(0);
	if (ft_thread_detach(&all))
		exit (1);
	free(all.philo);
	kill_process(&all);
	return (0);
}
