
#include "minishell.h"

char	*ft_readline()
{
	char *line;

	if (ft_strcmp(g_global.user, "root") == 0 || ft_strcmp(g_global.user,
			"admin") == 0)
		line = readline(FRED "minishell$ " NONE);
	else
		line = readline(FGREEN "minishell> " NONE);
	return (line);
}