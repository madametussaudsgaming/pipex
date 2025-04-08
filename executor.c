/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpadasia <rpadasia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 16:21:25 by rpadasia          #+#    #+#             */
/*   Updated: 2025/04/08 19:14:27 by rpadasia         ###   ########.fr       */
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

void	cmd_dir(char	*cmd, char **envp)
{
	int		i;
	char	*path_env;
	char	**paths;
	char	*full_path;

	while (envp[i] && strncmp(envp[i], "PATH=", 5) != 0)
		i++;
	paths = ft_split(envp[i] + 5, ":");
	i = 0;
	while (paths[i])
	{
		path_env = ft_strjoin(paths[i], "/");
		full_path = ft_strjoin(path_env, cmd);
		if (access(full_path, F_OK) == 0)
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
		exit();
	}
	execve(path, cmd, envp);
	free_path(cmd);
	free(path);
	exit();
}

void	errors(char *err, int type)
{
	write(2, err, ft_strlen(msg));
	write(2, "\n", 1);
	exit(type);
}
