/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpadasia <ryanpadasian@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 15:26:47 by rpadasia          #+#    #+#             */
/*   Updated: 2025/04/13 16:58:16 by rpadasia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "../libft/libft.h"
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <errno.h>
# include <stdio.h>

typedef struct s_file
{
	int	pid[2];
	int	fd[2];
}	t_file;

void	cp(char *argv[], int *fd, char **envp, int infile);
void	pp(char	*argv[], int *fd, char **envp, int outfile);
void	execute(char	*arg, char **envp);
char	*cmd_dir(char	*cmd, char **envp);
void	free_path(char **pa/ths);


#endif