/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpadasia <ryanpadasian@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 16:21:25 by rpadasia          #+#    #+#             */
/*   Updated: 2025/04/13 16:44:23 by rpadasia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headerfile/pipex.h"

void	free_path(char **paths)
{
	int	i;

	i = 0;
	while (paths[i])
	{
		free(paths[i]);
		i++;
	}
	free(paths);
}

char	*cmd_dir(char	*cmd, char **envp)
{
	int		i;
	char	*path_env;
	char	**paths;
	char	*full_path;

	i = 0;
	while (envp[i] && ft_strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	paths = ft_split(envp[i] + 5, ':');
	i = 0;
	while (paths[i]) {
		path_env = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(path_env, cmd);
		free(path_env);
		if (access(full_path, X_OK) == 0)
		{
			free_path(paths);
			return (full_path);
		}
		free(full_path);
		i++;
	}
	free_path(paths);
	return (NULL);
}

void	execute(char	*arg, char **envp)
{
	char	**cmd;
	char	*path;

	cmd = ft_split(arg, ' ');
	path = cmd_dir(cmd[0], envp);
	if (!path)
	{
		free_path(cmd);
		write(2, "Invalid Path\n", 14);
		exit(1);
	}
	execve(path, cmd, envp);
	perror("execve");
	free(path);
	free_path(cmd);
	exit(0);
}
