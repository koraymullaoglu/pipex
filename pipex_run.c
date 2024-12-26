/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_run.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: femullao <femullao@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/20 14:50:26 by femullao          #+#    #+#             */
/*   Updated: 2024/12/23 16:34:15 by femullao         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char **get_paths(char **env)
{
	char **r;
	char *path;
	int i;

	i = 0;
	while (env && env[i])
	{
		if (ft_strncmp(env[i],"PATH=",5) == 0)
		{
			path = env[i];	
		}
		i++;
	}
	return (path);
}

char *check_path(char *cmd , char **env)
{
	char **path;

	path = get_paths(env);
	
}


void run_command(char *cmd, char **env)
{
	char **command;

	command = ft_split(cmd, ' ');
	if (ft_strchr(command,'/')==0)
	{
		 
	}
	else{
		
	}
	
	

}