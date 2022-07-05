/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 16:49:14 by yoyohann          #+#    #+#             */
/*   Updated: 2022/07/05 04:32:23 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_thread_create(t_rules *rules)
{
	t_philo	*phi;
	int		i;

	i = 0;
	phi = rules->philosopher;
//	rules->time_start = ft_current_time();
	if (rules->num_philo == 1)
	{
		if (ft_one_philo(phi))
			return (1);
	}
	else
	{
		rules->time_start = ft_current_time();
		while (i < rules->num_philo)
		{
			if (pthread_create(&(phi[i].thr), NULL, mythread, &(phi[i])))
				return (1);
			usleep(100);
			phi[i].time_end = ft_current_time();
			i++;
		}
	}
	ft_check_death(rules, rules->philosopher);
	ft_thread_exit(rules, phi);
	return (0);
}

void 	*ft_single_thread(void *philo)
{
	t_rules	*rules;
	t_philo	*phi;
	phi = (t_philo*)philo;
	rules = phi->rules;
	pthread_mutex_lock(&(rules->fork[phi->left_fork]));
	ft_display_message(rules, phi->id, "has taken a fork.");
	pthread_mutex_unlock(&(rules->fork[phi->left_fork]));
	return (NULL);
}

int 	ft_one_philo(t_philo *philo)
{
	t_rules *rules;
	rules = philo->rules;
	rules->time_start = ft_current_time();

	if (pthread_create(&(philo[0].thr), NULL, ft_single_thread, &(philo[0])))
		return (1);
	usleep(100);
	philo[0].time_end = ft_current_time();
	return (0);
}
void	*mythread(void *philo)
{
	int		i;
	t_rules	*rules;
	t_philo	*phi;

	phi = (t_philo*)philo;
	i = 0;
	rules = phi->rules;
	if (phi->id % 2)
		usleep(150);
	while (!(rules->died))
	{
		ft_philo_eat(phi);
		if (rules->meal_count)
			break ;
		ft_display_message(rules, phi->id, "is sleeping.");
		ft_sleep(rules, rules->time_sleep);
		ft_display_message(rules, phi->id, "is thinking.");
		i++;
	}
	return (NULL);
}

void	ft_philo_eat(t_philo *phi)
{
	t_rules	*rules;

	rules = phi->rules;
	pthread_mutex_lock(&(rules->fork[phi->left_fork]));
	ft_display_message(rules, phi->id, "has taken a fork.");
	pthread_mutex_lock(&(rules->fork[phi->right_fork]));
	ft_display_message(rules, phi->id, "has taken a fork.");
	ft_display_message(rules, phi->id, "is eating.");
	phi->time_end = ft_current_time();
	ft_sleep(rules, rules->time_eat);
	phi->x_ate++;
	pthread_mutex_unlock(&(rules->fork[phi->left_fork]));
	pthread_mutex_unlock(&(rules->fork[phi->right_fork]));
}
