/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dahmane <dahmane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 13:02:13 by dahmane           #+#    #+#             */
/*   Updated: 2025/02/25 14:22:34 by dahmane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	init(t_pipeto **pipeto, char **argv, char **env, int *fd)
{
	fd[0] = -1;
	fd[1] = -1;
	*pipeto = NULL;
	*pipeto = malloc(sizeof(t_pipeto));
	if (!(*pipeto))
		return (1);
	(*pipeto)->fd_in = -1;
	(*pipeto)->fd_o = -1;
	if (get_commands(&(*pipeto), argv) == 1)
		return (1);
	if (get_paths(&(*pipeto), env) == 1)
		return (1);
	(*pipeto)->infile = argv[1];
	(*pipeto)->outf = argv[4];
	return (0);
}

int	fork_and_pipe(t_pipeto **pipeto, int *fd)
{
	if (pipe(fd) == -1)
		return (1);
	(*pipeto)->id = fork();
	if ((*pipeto)->id == -1)
		return (1);
	if ((*pipeto)->id != 0)
	{
		(*pipeto)->id2 = fork();
		if ((*pipeto)->id2 == -1)
			return (1);
	}
	return (0);
}
