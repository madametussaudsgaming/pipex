/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpadasia <rpadasia@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 12:58:40 by rpadasia          #+#    #+#             */
/*   Updated: 2025/04/08 19:29:51 by rpadasia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headerfile/pipex.h"

void	cp(char *argv[], int *fd, char **envp, int infile)
{
	dup2(infile, 0);
	dup2(fd[1], 1);
	close(fd[0]);
	execute(argv[2], envp);
	close(infile);
}

void	pp(char	*argv[], int *fd, char **envp, int outfile)
{
	dup2(outfile, 1);
	dup2(fd[0], 0);
	close(fd[1]);
	execute(argv[3], envp);
	close(outfile);
}

void	pipexmain(char **argv, char **envp)
{
	t_file	pipex;
	int		infile;
	int		outfile;

	infile = open(argv[1], O_RDONLY);
	outfile = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC | 0777);
	pipex.pid[0] = fork();
	if (pipex.pid[0] == 0)
		cp(argv, pipex.fd, envp, infile);
	pipex.pid[1] = fork();
	if (pipex.pid[1] == 0)
		pp(argv, pipex.fd, envp, outfile);
	close(pipex.fd[0]);
	close(pipex.fd[1]);
	close(infile);
	close(outfile);
	waitpid(pipex.pid[0], NULL, 0);
	waitpid(pipex.pid[1], NULL, 0);
}

int	main(int argc, char *argv[], char **envp)
{
	if (argc != 5)
	{
		write(2, "ERROR, FIVE ARGUMENTS NEEDED\n", 30);
		return (0);
	}
	pipexmain(argv, envp);
	return (0);
}
