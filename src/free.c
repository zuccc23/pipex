/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dahmane <dahmane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 14:14:11 by dahmane           #+#    #+#             */
/*   Updated: 2025/02/26 17:18:12 by dahmane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	return_error_input(t_pipeto **pipeto, int *fd, int argc)
{
	if (argc != 5)
		return (1);
	if ((*pipeto) && !(*pipeto)->ok_path && (*pipeto)->f_path)
		return (return_cmd_not_found(&(*pipeto), fd));
	else if ((*pipeto) && !(*pipeto)->ok_path_out && (*pipeto)->f_patho)
		return (return_cmd_not_found(&(*pipeto), fd));
	else if ((*pipeto) && !(*pipeto)->path_line && (*pipeto)->commands_o)
		return (return_cmd_not_found(&(*pipeto), fd));
	else
	{
		errno = ENOMEM;
		perror("Error");
	}
	if (pipeto && *pipeto)
		free_all(&(*pipeto), fd);
	exit(1);
	return (1);
}

void	return_error(t_pipeto **pipeto, int *fd)
{
	free_all(&(*pipeto), fd);
	perror("Error");
	exit(1);
}

void	free_all(t_pipeto **pipeto, int *fd)
{
	if ((*pipeto)->commands_in != NULL)
		free_strs((*pipeto)->commands_in);
	if ((*pipeto)->commands_o != NULL)
		free_strs((*pipeto)->commands_o);
	if ((*pipeto)->paths != NULL)
		free_strs((*pipeto)->paths);
	if ((*pipeto)->f_path != NULL)
		free_strs((*pipeto)->f_path);
	if ((*pipeto)->f_patho != NULL)
		free_strs((*pipeto)->f_patho);
	close_fd(&(*pipeto), fd);
	if (*pipeto != NULL)
		free(*pipeto);
}

void	close_fd(t_pipeto **pipeto, int *fd)
{
	if (*pipeto)
	{
		if ((*pipeto)->fd_in != -1)
		{
			close((*pipeto)->fd_in);
			(*pipeto)->fd_in = -1;
		}
		if ((*pipeto)->fd_o != -1)
		{
			close((*pipeto)->fd_o);
			(*pipeto)->fd_o = -1;
		}
	}
	if (fd[0] != -1)
	{
		close(fd[0]);
		fd[0] = -1;
	}
	if (fd[1] != -1)
	{
		close(fd[1]);
		fd[1] = -1;
	}
}

void	free_strs(char **strs)
{
	int	i;

	i = 0;
	while (strs[i])
	{
		free(strs[i]);
		i++;
	}
	free(strs);
}
