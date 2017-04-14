/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbauer <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/11 18:44:49 by bbauer            #+#    #+#             */
/*   Updated: 2017/04/11 19:23:45 by bbauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int					minishell_builtin(char **args, char **env)
{
	if (ft_strequ(args[1], "cd"))
		return (builtin_cd(args, env));
	else if (ft_strequ(args[1], "exit"))
		return (MINISHELL_EXIT);
	else if (ft_strequ(args[1], "env"))
		return (builtin_env(args, env));
	else if (ft_strequ(args[1], "setenv"))
		return (builtin_setenv(args, env));
	else if (ft_strequ(args[1], "unsetenv"))
		return (builtin_unsetenv(args, env));
	else if (ft_strequ(args[1], "echo"))
		return (builtin_echo(args, env));
	else
		return (NOT_BUILTIN);
}

int					minishell_exec(char **args, char **env)
{
	int			status;

	// If empty command was issued...
	if (args[0] == NULL || *(args[0]) == '\0')
		return (MINISHELL_CONTINUE);

	// Check if command is a builtin function
	if ((status = minishell_builtin(args, env)) == NOT_BUILTIN)
		return (minishell_launcher(args, env));
	else
		return (status);
}

int					minishell_launcher(char **args, char **env)
{
	pid_t	pid;
	pid_t	wpid;
	int status;

	pid = fork();
	if (pid == 0)
	{
		// Child process
		// CHANGE PROCESS NAME HERE -- (args[0] ???)
		if (execve(args[0], args, env) == -1)
			ft_putstr_fd("minishell: execve() failed!", 2);
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
		ft_putstr_fd("minishell: fork() error!", 2);
	else
	{
		// Parent process
		wpid = waitpid(pid, &status, WUNTRACED);
		while (!WIFEXITED(status) && !WIFSIGNALED(status))
			wpid = waitpid(pid, &status, WUNTRACED);
	}
	return (MINISHELL_CONTINUE);
}