/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysingh <ysingh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 18:48:44 by ysingh            #+#    #+#             */
/*   Updated: 2023/07/07 16:08:24 by ysingh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	call_signal(void)
{
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handle_sigint);
}

void	handle_sigint(int sig)
{
	if (sig == SIGINT)
	{
		rl_on_new_line();
		rl_redisplay();
		ft_putstr_fd("   ", 1);
		ft_printf("\n");
		//rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	handle_eof(void)
{
	rl_on_new_line();
	rl_redisplay();
	ft_putstr_fd("exit", 1);
	ft_putstr_fd("\n", 1);
	exit(0);
}
