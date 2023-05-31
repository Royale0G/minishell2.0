/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysingh <ysingh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 18:59:41 by ysingh            #+#    #+#             */
/*   Updated: 2023/05/31 22:11:50 by ysingh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_parser(char *prompt)
{
	char	**cmd;

	cmd = ft_cmdtrim(prompt);
	for (int i = 0; i < ft_charpplen(cmd); i++)
		printf("before: %s\n", cmd[i]);
	cmd = ft_expand_vars(cmd);
	for (int i = 0; i < ft_charpplen(cmd); i++)
		printf("after: %s\n", cmd[i]);
	ft_charppfree(cmd);
}

char	*ft_call_noq(char *prompt, int *i)
{
	char	*aux;

	aux = ft_noq(prompt, *i);
	*i += strlen(aux);
	return (aux);
}

char	**ft_cmdtrim(char *prompt)
{
	char	**ret;
	char	*aux;
	int		i;

	i = 0;
	ret = NULL;
	while (i < (int)ft_strlen(prompt))
	{
		while (prompt[i] == ' ')
			i++;
		if (prompt[i] == DQ)
			aux = ft_call_dq(prompt, &i);
		else if (prompt[i] == SQ)
			aux = ft_call_sq(prompt, &i);
		else if (prompt[i] == '<')
			aux = ft_call_red(prompt, &i);
		else if (prompt[i] == '>')
			aux = ft_call_redback(prompt, &i);
		else if (prompt[i] == '|')
			aux = ft_call_pipe(prompt, &i);
		else
			aux = ft_call_noq(prompt, &i);
		ret = ft_str_add_back(ret, aux);
	}
	return (ret);
}

char	**ft_expand_vars(char **cmd)
{
	char	**ret;
	int		i;

	i = -1;
	ret = NULL;
	if (!cmd)
		return (NULL);
	while (cmd[++i])
		ret = ft_str_add_back(ret, ft_get_var(cmd[i]));
	ft_charppfree(cmd);
	return (ret);
}
