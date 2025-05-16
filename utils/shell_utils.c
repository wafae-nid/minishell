/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shell_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnid-hsa <wnid-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 15:43:28 by bzinedda          #+#    #+#             */
/*   Updated: 2025/05/08 02:56:55 by wnid-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	print_token(t_token *token)
{
	t_token	*current;

	if (!token)
	{
		printf("empty token!\n");
		return ;
	}
	current = token;
	while (current)
	{
		printf("\e[32mType:\e[0m %d", current->type);
		if (current->value)
			printf("| \e[34mValue:\e[0m %s", current->value);
		printf("\n\e[33m****************************\e[0m\n");
		current = current->next;
	}
}

void	print_opp(t_opp *opera)
{
	t_opp	*current;

	if (!opera)
		printf("\n\t\e[31mx empty operations!\e[0m\n");
	else
	{
		current = opera;
		while (current)
		{
			printf("\t\e[36m- Redirection Type:\e[0m %d", current->operator);
			if (current->arg)
				printf("\t | \e[94mFile:\e[0m %s", current->arg);
			printf("\n\t\e[95m--------------------------\e[0m\n");
			current = current->next;
		}
	}
}

void	print_command(t_com *command)
{
	t_com	*current;
	int		i;

	if (!command)
	{
		printf("\e[31mNo Command!\e[0m\n");
		return ;
	}
	current = command;
	while (current)
	{
		i = 0;
		printf("\n");
		printf("\e[35m+ args:\e[0m");
		while ((current->command)[i])
			printf(" %s", (current->command)[i++]);
		printf("\n");
		print_opp(current->operator);
		printf("\n\e[32m****************************\e[0m\n");
		current = current->next;
	}
}

void	ft_set_mini_env_config(t_env **path, t_env **pwd,
		t_env **shlvl, t_env **last_command)
{
	char	cwd[1024];

	if (!path || !pwd || !shlvl || !last_command)
		return ;
	(*path)->key = ft_strdup("PATH");
	(*path)->value = ft_strdup("/usr/gnu/bin:/usr/local/bin:/bin:/usr/bin:.");
	(*path)->next = *pwd;
	(*pwd)->key = ft_strdup("PWD");
	(*pwd)->value = ft_strdup(getcwd(cwd, sizeof(cwd)));
	(*pwd)->next = *shlvl;
	(*shlvl)->key = ft_strdup("SHLVL");
	(*shlvl)->value = ft_strdup("1");
	(*shlvl)->next = *last_command;
	(*last_command)->key = ft_strdup("_");
	(*last_command)->value = ft_strdup("/usr/bin/env");
	(*last_command)->next = NULL;
}

t_env	*create_mini_env(void)
{
	t_env	*path;
	t_env	*pwd;
	t_env	*shlvl;
	t_env	*last_command;

	path = gc_malloc(sizeof(t_env), GLOBAL);
	if (!path)
		return (NULL);
	pwd = gc_malloc(sizeof(t_env), GLOBAL);
	if (!pwd)
		return (NULL);
	shlvl = gc_malloc(sizeof(t_env), GLOBAL);
	if (!shlvl)
		return (NULL);
	last_command = gc_malloc(sizeof(t_env), GLOBAL);
	if (!last_command)
		return (NULL);
	ft_set_mini_env_config(&path, &pwd, &shlvl, &last_command);
	return (path);
}
