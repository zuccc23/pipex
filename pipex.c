/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dahmane <dahmane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 00:54:28 by dahmane           #+#    #+#             */
/*   Updated: 2025/02/21 15:10:26 by dahmane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	child1(t_pipeto **pipeto, int *fd, char **env)
{
	if (close(fd[0]) == -1)
		return (1);
	fd[0] = -1;
	(*pipeto)->fd_in = open((*pipeto)->infile, O_RDONLY);
	if ((*pipeto)->fd_in == -1)
		return (1);
	if (dup2((*pipeto)->fd_in, STDIN_FILENO) == -1)
		return (1);
	if (dup2(fd[1], STDOUT_FILENO) == -1)
		return (1);
	if (close(fd[1]) == -1)
		return (1);
	if (close((*pipeto)->fd_in) == -1)
		return (1);
	if (execve((*pipeto)->ok_path, (*pipeto)->commands_in, env) == -1)
		return (1);
	return (0);
}

int	child2(t_pipeto **pipeto, int *fd, char **env)
{
	if (close(fd[1]) == -1)
		return (return_error(&(*pipeto), fd), -1);
	fd[1] = -1;
	(*pipeto)->fd_out = open((*pipeto)->outfile, O_WRONLY | O_CREAT | O_TRUNC);
	if ((*pipeto)->fd_out == -1)
		return (return_error(&(*pipeto), fd), -1);
	if (dup2(fd[0], STDIN_FILENO) == -1)
		return (return_error(&(*pipeto), fd), -1);
	if (dup2((*pipeto)->fd_out, STDOUT_FILENO) == -1)
		return (return_error(&(*pipeto), fd), -1);
	if (close(fd[0]) == -1)
		return (return_error(&(*pipeto), fd), -1);
	if (close((*pipeto)->fd_out) == -1)
		return (return_error(&(*pipeto), fd), -1);
	if (execve((*pipeto)->ok_path_out, (*pipeto)->commands_o, env) == -1)
		return (return_error(&(*pipeto), fd), -1);
	return (0);
}

int	parent(t_pipeto **pipeto, int *fd)
{
	if (close(fd[0]) == -1)
		return (1);
	fd[0] = -1;
	if (close(fd[1]) == -1)
		return (1);
	fd[1] = -1;
	if (waitpid((*pipeto)->id, &(*pipeto)->ex_cd1, 0) == -1)
		return (1);
	if (waitpid((*pipeto)->id2, &(*pipeto)->ex_cd2, 0) == -1)
		return (1);
	(*pipeto)->ex_cd1 = ((*pipeto)->ex_cd1 >> 8) & 0xFF;
	(*pipeto)->ex_cd2 = ((*pipeto)->ex_cd2 >> 8) & 0xFF;
	if ((*pipeto)->ex_cd1 != 0 || (*pipeto)->ex_cd2 != 0)
	{
		free_all(&(*pipeto), fd);
		exit(-1);
	}
	free_all(&(*pipeto), fd);
	return (0);
}

int	main(int argc, char **argv, char **env)
{
	int			fd[2];
	t_pipeto	*pipeto;

	if (argc != 5 || init(&pipeto, argv, env, fd) == 1)
		return (return_error_input(&pipeto, fd, argc));
	if (fork_and_pipe(&pipeto, fd) == 1)
		return_error(&pipeto, fd);
	if (pipeto->id == 0)
	{
		if (child1(&pipeto, fd, env) == 1)
			return_error(&pipeto, fd);
	}
	else
	{
		if (pipeto->id2 == 0)
		{
			if (child2(&pipeto, fd, env) == 1)
				return_error(&pipeto, fd);
		}
		else
		{
			if (parent(&pipeto, fd) == 1)
				return_error(&pipeto, fd);
		}
	}
}
