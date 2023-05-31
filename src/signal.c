/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysingh <ysingh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 18:48:44 by ysingh            #+#    #+#             */
/*   Updated: 2023/05/31 19:08:54 by ysingh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_sigquit(int sig)
{
	(void)sig;
	exit(0);
}

void	handle_sigint(int sig)
{
	if (sig == SIGINT)
	{
		rl_on_new_line();
		rl_redisplay();
		ft_putstr_fd("   ", 1);
		ft_printf("\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}
