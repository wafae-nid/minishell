/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agaladi <agaladi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 04:32:42 by agaladi           #+#    #+#             */
/*   Updated: 2024/11/20 19:03:58 by agaladi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

extern int	g_signal_received;

char	**fill_heredoc_files(int count)
{
	int		i;
	char	**new;

	new = gc_malloc(sizeof(char *) * (count + 1), LOCAL);
	if (!new)
		return (NULL);
	i = 0;
	while (i < count)
	{
		new[i] = ft_strjoin("/tmp/.tmpheredocfile", ft_itoa(i), LOCAL);
		i++;
	}
	new[i] = NULL;
	return (new);
}

void	handle_heredoc_sig(int sig)
{
	(void)sig;
	close(0);
	g_signal_received = 1;
}

void	open_heredoc(char **files, t_opp *op, int *count, t_shell *data)
{
	char	*str;
	char	*tmp;
	int		fd;

	open_heredoc_helper(files, &fd, count);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		signal(SIGINT, handle_heredoc_sig);
		rl_catch_signals = 1;
		str = readline("> ");
		if (g_signal_received)
		{
			open_tty();
			break ;
		}
		if (!str || ft_strcmp(str, op->arg) == 0)
			return (close(fd), free(str));
		tmp = str;
		if (op->operator == HERE_DOC_EXP)
			expand(&tmp, data->env, &data->exit_status, true);
		ft_printf(fd, "%s\n", tmp);
		free (str);
	}
	heredoc_cleanup(&fd, str);
}

void	handle_heredoc(t_shell *data)
{
	int		count;
	t_com	*curr;
	t_opp	*op;

	count = heredoc_count(data->command);
	data->heredoc_count = count;
	heredoc_count_check(count);
	data->heredoc_files = fill_heredoc_files(count);
	(1 && (curr = data->command), (count = 0));
	while (curr)
	{
		op = curr->operator;
		while (op)
		{
			if (op->operator == HERE_DOC || op->operator == HERE_DOC_EXP)
				open_heredoc(data->heredoc_files, op, &count, data);
			if (g_signal_received)
				return ;
			op = op->next;
		}
		curr = curr->next;
	}
}

int	ft_read_from_heredoc(t_shell *data)
{
	int	new;

	if (data->heredoc_index >= data->heredoc_count)
		return (0);
	new = open(data->heredoc_files[data->heredoc_index], O_RDONLY);
	if (new < 0)
		return (perror("open heredeoc failed!"), 1);
	if (unlink(data->heredoc_files[data->heredoc_index]) < 0)
		return (perror("unlink"), 1);
	data->heredoc_index++;
	if (dup2(new, STDIN_FILENO) < 0)
		return (perror("dup failed!"), 1);
	close(new);
	return (0);
}
