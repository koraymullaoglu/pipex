/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipexct.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: femullao <femullao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/27 15:55:37 by femullao          #+#    #+#             */
/*   Updated: 2024/12/27 17:14:22 by femullao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	ft_puterror(char *str, int f)
{
	if (f == 0)
	{
		ft_putstr_fd("no such file or directory: ", 2);
		ft_putendl_fd(str, 2);
		free(str);
	}
	else if (f == 1)
	{
		ft_putstr_fd("permission denied: ", 2);
		ft_putendl_fd(str, 2);
		free(str);
	}
	else if (f == 2)
	{
		ft_putstr_fd("command not found: ", 2);
		ft_putendl_fd(str, 2);
	}
}

static char	**get_path(char **env)
{
	char	**r;
	int		i;

	i = 0;
	r = NULL;
	while (env && env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			r = ft_split(ft_strchr(env[i], '/'), ':');
			return (r);
		}
		i++;
	}
	return (r);
}

static char	*check_path(char *cmd, char **env)
{
	char	**paths;
	char	*tmp;
	char	*test;

	paths = get_path(env);
	while (paths && *paths)
	{
		tmp = ft_strjoin(*paths, "/");
		test = ft_strjoin(tmp, cmd);
		free(tmp);
		if (!access(test, X_OK) && !access(test, F_OK))
			return (test);
		else if (access(test, X_OK) != 0 && access(test, F_OK) == 0)
			ft_puterror(test, 1);
		else
			free(test);
		paths++;
	}
	ft_puterror(cmd, 2);
	exit(127);
}

void	run_command(char *cmd, char **env)
{
	char	**command;
	char	*path;

	command = ft_split(cmd, ' ');
	if (ft_strchr(command[0], '/'))
	{
		path = command[0];
		if (access(path, X_OK) == -1)
		{
			if (access(path, F_OK) == -1)
			{
				ft_puterror(path, 0);
				free(command);
				exit (127);
			}
			ft_puterror(path, 1);
			free (command);
			exit (126);
		}
	}
	else
		path = check_path(command[0], env);
	execve(path, command, env);
	free(command);
}
