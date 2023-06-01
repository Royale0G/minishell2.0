/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ysingh <ysingh@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/31 18:59:03 by ysingh            #+#    #+#             */
/*   Updated: 2023/06/01 17:16:27 by ysingh           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*line;

	(void)argc;
	(void)argv;
	printcustomascii();
	ft_init_global(envp);
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, handle_sigint);
	while (1)
	{
		line = ft_readline();
		if (!line)
			return (ft_putendl_fd("Exit", 2), 0);
		add_history(line);
		if (ft_check_cmd(line))
		{
			ft_parser(line);
			free(line);
		}
		else
		{
			free(line);
			ft_putstr_fd("minishell: syntax error\n", 2);
		}
	}
}

t_envp	*ft_get_node(char *str)
{
	t_list	*list;
	t_envp	*node;

	list = g_global.envp;
	while (list)
	{
		node = list->content;
		if (!ft_strcmp(str, node->key))
			return (free(str), node);
		list = list->next;
	}
	return (free(str), NULL);
}

void	ft_aux_get_var(t_master *mas)
{
	mas->strs.aux2 = ft_strchrs(mas->strs.aux + 1, " $=\n\t?\'\"|");
	mas->var = ft_get_node(ft_substr(mas->strs.cpy, ft_get_index(mas->strs.cpy,
					mas->strs.aux), ft_get_index(mas->strs.cpy, mas->strs.aux2)
				- ft_get_index(mas->strs.cpy, mas->strs.aux)));
	if (!mas->var)
		mas->strs.cpy = ft_replace(mas->strs.cpy, mas->strs.aux, mas->strs.aux2,
				"");
	else
	{
		mas->strs.cpy = ft_replace(mas->strs.cpy, mas->strs.aux, mas->strs.aux2,
				mas->var->value);
		mas->count.i = mas->count.j + (int)ft_strlen(mas->var->value);
	}
}

char	*ft_get_var(char *cmd)
{
	t_master	mas;

	mas.count.i = 0;
	mas.strs.cpy = ft_strdup(cmd);
	if ((cmd[0] == SQ && cmd[ft_strlen(cmd) - 1] == SQ)
		|| !ft_strchr(mas.strs.cpy, '$'))
		return (mas.strs.cpy);
	while (mas.strs.cpy[mas.count.i])
	{
		mas.strs.aux = ft_strchr(mas.strs.cpy + mas.count.i, '$');
		if (!mas.strs.aux)
			break ;
		mas.count.j = ft_get_index(mas.strs.cpy,
									ft_strchr(mas.strs.cpy + mas.count.i, '$'));
		if (ft_isspace(mas.strs.aux[1]) || mas.strs.aux[1] == '\0'
			|| mas.strs.aux[1] == '$' || mas.strs.aux[1] == '='
			|| mas.strs.aux[1] == '\"' || mas.strs.aux[1] == '\''
			|| mas.strs.aux[1] == '?' || mas.strs.aux[1] == '|')
		{
			mas.count.i++;
			continue ;
		}
		ft_aux_get_var(&mas);
	}
	return (mas.strs.cpy);
}
