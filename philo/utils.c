/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlamonic <jlamonic@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 23:06:53 by jlamonic          #+#    #+#             */
/*   Updated: 2022/01/06 23:40:43 by jlamonic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	message(t_all *all, t_list *philo, char *msg)
{
	unsigned long long	time;

	time = get_time() - all->table->start_time;
	if (time >= 0)
	{
		pthread_mutex_lock(&all->table->message);
		ft_putnbr(time);
		write(1, " ", 1);
		ft_putstr("philo ");
		ft_putnbr(philo->id);
		write(1, " ", 1);
		ft_putstr(msg);
		ft_putstr("\n");
	}
	if (ft_strncmp(msg, "has died"))
		pthread_mutex_unlock(&all->table->message);
}

void	waiting(unsigned long long time)
{
	unsigned long long	start;

	start = get_time();
	while (time > get_time() - start)
		usleep(50);
	return ;
}

void	eating(t_all *all, t_list *philo)
{
	pthread_mutex_lock(philo->left_fork);
	message(all, philo, "has taken a left fork");
	pthread_mutex_lock(philo->right_fork);
	message(all, philo, "has taken a right fork");
	if (all->table->time_to_die > get_time() - all->philo->last_meal)
	{
		message(all, philo, "is eating");
		philo->eat_times++;
	}
	waiting(all->table->time_to_eat);
	philo->last_meal = get_time();
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void	error(char *msg)
{
	int	i;

	i = ft_strlen(msg);
	write(1, "Error: ", 7);
	write(1, msg, i);
	write(1, "\n", 1);
	exit (1);
}

unsigned long long	get_time(void)
{
	struct timeval	current_time;

	gettimeofday(&current_time, NULL);
	return (current_time.tv_sec * 1000 + current_time.tv_usec / 1000);
}
