/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dahmane <dahmane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 00:54:28 by dahmane           #+#    #+#             */
/*   Updated: 2025/02/19 12:51:40 by dahmane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int init(t_pipeto **pipeto, char **argv, char **env)
{
	*pipeto = NULL;
	*pipeto = malloc(sizeof(t_pipeto));
	if (!(*pipeto))
		return (1);
	(*pipeto)->fd_in = -1;
	(*pipeto)->fd_out = -1;
	if (get_commands(&(*pipeto), argv) == 1)
		return (1);
	if (get_paths(&(*pipeto), argv, env) == 1)
		return (1);
	(*pipeto)->infile = argv[1];
	(*pipeto)->outfile = argv[4];
	return (0);
}

int	child1(t_pipeto **pipeto, int *fd, char **env)
{
	// CLOSE READ END PIPE
	if (close(fd[0]) == -1)
		return (1);
	fd[0] = -1;
	// OPEN INFILE
	(*pipeto)->fd_in = open((*pipeto)->infile, O_RDONLY);
	if ((*pipeto)->fd_in == -1)
		return (1);

	// USE INFILE AS INPUT, AND PIPE WRITE END AS OUTPUT
	if (dup2((*pipeto)->fd_in, STDIN_FILENO) == -1)
		return (1);
	if (dup2(fd[1], STDOUT_FILENO) == -1)
		return (1);

	// CLOSE WRITE END PIPE AND INFILE FD
	if (close(fd[1]) == -1)
		return (1);
	if (close((*pipeto)->fd_in) == -1)
		return (1);
		
	// THING I WANT TO EXECUTE
	// printf("test");
	if (execve((*pipeto)->ok_path, (*pipeto)->commands_in, env) == -1)
		return (1);

	return (0);
}

int	child2(t_pipeto **pipeto, int *fd, char **env)
{
	// CLOSE WRITE END PIPE
	if (close(fd[1]) == -1)
		return (1);
	fd[1] = -1;
	// OPEN OUTFILE
	(*pipeto)->fd_out = open((*pipeto)->outfile, O_WRONLY | O_CREAT | O_TRUNC);
	if ((*pipeto)->fd_out == -1)
		return (1);
	
	// USE READ END AS INPUT, AND OUTFILE AS OUTPUT
	if (dup2(fd[0], STDIN_FILENO) == -1)
		return (1);
	if (dup2((*pipeto)->fd_out, STDOUT_FILENO) == -1)
		return (1);

	// CLOSE READ END PIPE AND OUTFILE FD
	if (close(fd[0]) == -1)
		return (1);
	if (close((*pipeto)->fd_out) == -1)
		return (1);

	// THING I WANT TO EXECUTE
	// ft_printf("read from child 2 :%s\n", buff);
	if (execve((*pipeto)->ok_path_out, (*pipeto)->commands_o, env) == -1)
		return (1);
	
	return (0);
}

int	parent(t_pipeto **pipeto, int *id, int *id2, int *fd)
{
	// CLOSE FILE DESCRIPTORS OF PIPE
	if (close(fd[0]) == -1)
		return (1);
	fd[0] = -1;
	if (close(fd[1]) == -1)
		return (-1);
	fd[1] = -1;
		
	// WAIT FOR CHILDREN
	if (waitpid(*id, NULL, 0) == -1)
		return (1);
	if (waitpid(*id2, NULL, 0) == -1)
		return (1);
			
	// FREE PIPETO
	free_all(&(*pipeto), fd);
	
	return (0);
}

int	fork_and_pipe(int *fd, int *id, int *id2)
{
	if (pipe(fd) == -1)
		return (1);
	*id = fork();
	if (*id == -1)
		return (1);
	if (*id != 0)
	{
		*id2 = fork();
		if (*id2 == -1)
			return (1);
	}
	return (0);
}

int main (int argc, char **argv, char **env)
{
	int     id;
	int     id2;
	int     fd[2];
	t_pipeto   *pipeto;

	// INIT //////////////////////////////////////////////////////////////

	if (argc != 5)
		return (ft_printf("Error : Incorrect input\n"));
	if (init(&pipeto, argv, env) == 1)
		return (return_error_input(&pipeto, fd));
	// init func sets perror to ENOENT idk why
	
	// maybe init fd to -1
	fd[0] = -1;
	fd[1] = -1;
	
	// FORK AND PIPE //////////////////////////////////////////////////////
	if (fork_and_pipe(fd, &id, &id2) == 1)
	{
		free_all(&pipeto, fd);
		perror("Error");
		exit(-1);
	}
	// test if this works correctly
	
	// CHILD 1 ////////////////////////////////////////////////////////////
	if (id == 0)
	{
		// ft_printf("%d %d\n", fd[0], fd[1]);
		// ft_printf("test : is it entering child 1");
		if (child1(&pipeto, fd, env) == 1)
		{
			perror("Error");
			free_all(&pipeto, fd);
			exit(-1);
			// ft_printf("where is error\n");
		}
	}
	
	// CHILD 2 ////////////////////////////////////////////////////////////
	else 
	{
	    if (id2 == 0)
	    {
			// ft_printf("test : is it entering child 2");
			if (child2(&pipeto, fd, env) == 1)
			{
				free_all(&pipeto, fd);
				perror("Error");
				exit(-1);
			}
	    }
		// MAIN ////////////////////////////////////////////////////////////
	    else
	    {
			// ft_printf("test : is it entering parent");
			if (parent(&pipeto, &id, &id2, fd) == 1)
			{
				free_all(&pipeto, fd);
				perror("Error");
				exit(-1);
			}
	    }
	}
	
}

