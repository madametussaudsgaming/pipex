/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpadasia <ryanpadasian@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/08 12:58:40 by rpadasia          #+#    #+#             */
/*   Updated: 2025/04/13 23:20:33 by rpadasia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "headerfile/pipex.h"

void	cp(char *argv[], int *fd, char **envp, int infile)
{
	if (dup2(infile, STDIN_FILENO) == -1)
		perror("dup2 infile failed");
	if (dup2(fd[1], STDOUT_FILENO) == -1)
		perror("dup2 fd[1] failed");
	close(fd[0]);
	close(fd[1]);
	close(infile);
	execute(argv[2], envp);
}

void	pp(char	*argv[], int *fd, char **envp, int outfile)
{
	if (dup2(fd[0], STDIN_FILENO) == -1)
		perror("dup2 fd[0] failed");
	if (dup2(outfile, STDOUT_FILENO) == -1)
		perror("dup2 outfile failed lol");
	close(fd[0]);
	close(fd[1]);
	close(outfile);
	execute(argv[3], envp);
}

void	pipexmain(char **argv, char **envp)
{
	t_file	pipex;
	int		infile;
	int		outfile;

	infile = open(argv[1], O_RDONLY);
	outfile = open(argv[4], O_CREAT | O_WRONLY | O_TRUNC, 0777);
	if (infile < 0 || outfile < 0)
	{
		perror("FILE MISSING");
		exit(1);
	}
	if (pipe(pipex.fd) < 0)
	{
		perror("PIPE ERROR");
		exit(1);
	}
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
		return (1);
	}
	pipexmain(argv, envp);
	return (0);
}
