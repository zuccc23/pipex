/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dahmane <dahmane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/11 00:54:28 by dahmane           #+#    #+#             */
/*   Updated: 2025/02/15 16:16:59 by dahmane          ###   ########.fr       */
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

int main (int argc, char **argv, char **env)
{
	int     id = 0;
	int     id2 = 0;
	int     fd[2];
	int     fd2[2];
	t_pipeto   *pipeto;

	// INIT //////////////////////////////////////////////////////////////

	if (argc != 5)
		return (ft_printf("Error : Incorrect input"));
	if (init(&pipeto, argv, env) == 1)
		return (return_error(pipeto, id));

	// TEST INIT //////////////////////////////////////////////////////////////

	// ft_print(pipeto->commands_out);
	// ft_printf("%s\n", pipeto->ok_path);
	// free_all(pipeto);

	// USE EXECVE //////////////////////////////////////////////////////////////
	
	id = open(pipeto->infile, O_RDONLY);
	if (id == -1)
		return (return_error(pipeto, id));
	// id2 = open(pipeto->outfile, O_WRONLY);
	dup2(id, STDIN_FILENO);
	// dup2(id2, STDOUT_FILENO);
	execve(pipeto->ok_path, pipeto->commands_in, env);

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
	
	// TEST PROCESS ID //////////////////////////////////////////////////////
	// id = fork();
	// id2 = fork();
	// if (id == 0)
	// {
	//     if (id2 == 0)
	//     {
	//         printf("child2\n");
	//     }
	//     else
	//     {
	//         // wait(NULL);
	//         printf("parent\n");
	//     }
	// }
	// else 
	// {
	//     if (id2 == 0)
	//     {
	//         printf("child1\n");
	//     }
	//     else
	//     {
	//         printf("main\n");
	//     }
	// }
}

