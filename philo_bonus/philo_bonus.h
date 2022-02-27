/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jlamonic <jlamonic@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/24 23:06:53 by jlamonic          #+#    #+#             */
/*   Updated: 2022/01/06 23:40:43 by jlamonic         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_BONUS_H
# define PHILO_BONUS_H

# include <pthread.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <limits.h>
# include <semaphore.h>
# include <signal.h>

typedef struct s_list
{
	pid_t			pid;
	int				id;
	int				eat_times;
	uint64_t		last_meal;
	pthread_t		thread_id;
}				t_list;

typedef struct s_tab
{
	int					philo_num;
	int					num_to_eat;
	unsigned long		time_to_die;
	unsigned long		time_to_eat;
	unsigned long		time_to_sleep;
	uint64_t			start_time;
	sem_t				*pfork;
	sem_t				*message;
	pthread_mutex_t		sleep;
}				t_tab;

typedef struct s_all
{
	t_tab	*table;
	t_list	*philo;
	int		philo_count;
}				t_all;

//init_alloc
int					philo_alloc(t_all *all);
int					argv_parsing(t_tab *table, char **argv);
int					sem_create(t_all *all);
void				kill_process(t_all *all);
int					ft_thread_detach(t_all *all);

//actions
void				message(t_all *all, t_list *philo, char *msg);
void				waiting(unsigned long long time);
void				eating(t_all *all, t_list *philo);
void				*life(void *argc);

//actions
void				message(t_all *all, t_list *philo, char *msg);
void				*life(void *argc);

//utils
int					ft_atoi(const char *str);
void				ft_putnbr(unsigned long long n);
void				ft_putstr(char *s);
void				ft_putchar(char c);
int					ft_strncmp(const char *s1, const char *s2);

//utils_2
size_t				ft_strlen(const char *str);
void				error(char *msg);
unsigned long long	get_time(void);

#endif