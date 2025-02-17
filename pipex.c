/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dahmane <dahmane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 00:54:28 by dahmane           #+#    #+#             */
/*   Updated: 2025/02/17 14:47:41 by dahmane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int init(t_pipeto **pipeto, char **argv, char **env)
{
	*pipeto = malloc(sizeof(t_pipeto));
	if (!(*pipeto))
		return (1);
	if (get_commands(&(*pipeto), argv) == 1)
		return (1);
	if (get_paths(&(*pipeto), argv, env) == 1)
		return (1);
	(*pipeto)->infile = argv[1];
	(*pipeto)->outfile = argv[4];
	return (0);
}

void	child1(t_pipeto **pipeto, int *id, int *id2, int *fd, char **env)
{
	// CLOSE READ END PIPE
		close(fd[0]);
		
		// OPEN INFILE
		(*pipeto)->fd_in = open((*pipeto)->infile, O_RDONLY);
		// if (pipeto->fd_in == -1)
		// 	return (return_error(pipeto, id));
		
		// USE INFILE AS INPUT, AND PIPE WRITE END AS OUTPUT
		dup2((*pipeto)->fd_in, STDIN_FILENO);
		dup2(fd[1], STDOUT_FILENO);

		// CLOSE WRITE END PIPE AND INFILE FD
		close(fd[1]);
		close((*pipeto)->fd_in);
		
		// THING I WANT TO EXECUTE
		// printf("test");
		execve((*pipeto)->ok_path, (*pipeto)->commands_in, env);
}

void	child2(t_pipeto **pipeto, int *id, int *id2, int *fd, char **env)
{
	// CLOSE WRITE END PIPE
			close(fd[1]);
			
			// OPEN OUTFILE
			(*pipeto)->fd_out = open((*pipeto)->outfile, O_WRONLY);
			// READ FROM READ END PIPE
			// read(fd[0], buff, sizeof(buff));
			
			// USE READ END AS INPUT, AND OUTFILE AS OUTPUT
			dup2(fd[0], STDIN_FILENO);
			dup2((*pipeto)->fd_out, STDOUT_FILENO);

			// CLOSE READ END PIPE AND OUTFILE FD
			close(fd[0]);
			close((*pipeto)->fd_out);

			// THING I WANT TO EXECUTE
			// ft_printf("read from child 2 :%s\n", buff);
			execve((*pipeto)->ok_path_out, (*pipeto)->commands_out, env);
}

void	parent(t_pipeto **pipeto, int *id, int *id2, int *fd, char **env)
{
	// CLOSE FILE DESCRIPTORS OF PIPE
			close(fd[0]);
			close(fd[1]);
			
			// WAIT FOR CHILDREN
			waitpid(*id, NULL, 0);
			waitpid(*id2, NULL, 0);
			
			// FREE PIPETO
			free_all(*pipeto);
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
		return (return_error_input(pipeto));
	
	// FORK AND PIPE //////////////////////////////////////////////////////
	// pipe(fd);
	// id = fork();
	// if (id != 0)
	// 	id2 = fork();
	if (fork_and_pipe(fd, &id, &id2) == 1)
		
	
	// CHILD 1 ////////////////////////////////////////////////////////////
	if (id == 0)
	{
		// // CLOSE READ END PIPE
		// close(fd[0]);
		
		// // OPEN INFILE
		// pipeto->fd_in = open(pipeto->infile, O_RDONLY);
		// // if (pipeto->fd_in == -1)
		// // 	return (return_error(pipeto, id));
		
		// // USE INFILE AS INPUT, AND PIPE WRITE END AS OUTPUT
		// dup2(pipeto->fd_in, STDIN_FILENO);
		// dup2(fd[1], STDOUT_FILENO);

		// // CLOSE WRITE END PIPE AND INFILE FD
		// close(fd[1]);
		// close(pipeto->fd_in);
		
		// // THING I WANT TO EXECUTE
		// // printf("test");
		// execve(pipeto->ok_path, pipeto->commands_in, env);
		child1(&pipeto, &id, &id2, fd, env);
	}
	
	// CHILD 2 ////////////////////////////////////////////////////////////
	else 
	{
	    if (id2 == 0)
	    {
			// // CLOSE WRITE END PIPE
			// close(fd[1]);
			
			// // OPEN OUTFILE
			// pipeto->fd_out = open(pipeto->outfile, O_WRONLY);
			// // READ FROM READ END PIPE
			// // read(fd[0], buff, sizeof(buff));
			
			// // USE READ END AS INPUT, AND OUTFILE AS OUTPUT
			// dup2(fd[0], STDIN_FILENO);
			// dup2(pipeto->fd_out, STDOUT_FILENO);

			// // CLOSE READ END PIPE AND OUTFILE FD
			// close(fd[0]);
			// close(pipeto->fd_out);

			// // THING I WANT TO EXECUTE
			// // ft_printf("read from child 2 :%s\n", buff);
			// execve(pipeto->ok_path_out, pipeto->commands_out, env);
			child2(&pipeto, &id, &id2, fd, env);
	    }
		// MAIN ////////////////////////////////////////////////////////////
	    else
	    {
			// // CLOSE FILE DESCRIPTORS OF PIPE
			// close(fd[0]);
			// close(fd[1]);
			
			// // WAIT FOR CHILDREN
			// waitpid(id, NULL, 0);
			// waitpid(id2, NULL, 0);

			
			// // FREE FD OF INFILE AND OUTFILE
			// // if (pipeto->fd_in > 0)
			// // 	close(pipeto->fd_in);
			// // if (pipeto->fd_out > 0)
			// // 	close(pipeto->fd_out);
			
			// // FREE PIPETO
			// free_all(pipeto);
			parent(&pipeto, &id, &id2, fd, env);
	    }
	}
	
	// TEST INIT //////////////////////////////////////////////////////////////

	// ft_print(pipeto->final_paths_out);
	// ft_printf("%s\n", pipeto->ok_path_out);
	// free_all(pipeto);

	// FORK //////////////////////////////////////////////////////////////

	// pid[0] = fork();
	// if (pid[0] != 0)
	// {
	// 	wait(NULL);
	// 	pid[1] = fork();
	// }
	
	// EXECVE //////////////////////////////////////////////////////////////
	
	
	// id = open(pipeto->infile, O_RDONLY);
	// if (id == -1)
	// 	return (return_error(pipeto, id));
	// // id2 = open(pipeto->outfile, O_WRONLY);
	// dup2(id, STDIN_FILENO);
	// // dup2(id2, STDOUT_FILENO);
	// execve(pipeto->ok_path, pipeto->commands_in, env);

	// DOUBLE PIPE ////////////////////////////////////////////////////////////
	
	// pipe(fd);
	// pipe(fd2);
	// id = fork();
	// if (id == 0)
	// {
	//     int nb = 5;
	//     close(fd[0]);
	//     write(fd[1], &nb, sizeof(int));
	//     close(fd[1]);

	//     close(fd2[1]);
	//     read(fd2[0], &nb, sizeof(int));
	//     close(fd2[0]);
	//     printf("%d\n", nb);
	// }
	// if (id != 0)
	// {
	//     int nb2;
	//     close(fd[1]);
	//     read(fd[0], &nb2, sizeof(int));
	//     close(fd[0]);
	//     // printf("%d\n", nb2);
	//     nb2 *= 2;

	//     close(fd2[0]);
	//     write(fd2[1], &nb2, sizeof(int));
	//     close(fd2[1]);
	// }
}

