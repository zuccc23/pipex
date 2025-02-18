/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dahmane <dahmane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 14:14:11 by dahmane           #+#    #+#             */
/*   Updated: 2025/02/18 16:55:28 by dahmane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int     return_error_input(t_pipeto **pipeto, int *fd)
{
    (*pipeto)->fd_in = -1;
	(*pipeto)->fd_out = -1;
    free_all(&(*pipeto), fd);
    errno = ENOMEM;
    perror("Malloc failed");
    return (1);
}

void	free_all(t_pipeto **pipeto, int *fd)
{
    if ((*pipeto)->commands_in != NULL)
	    free_strs((*pipeto)->commands_in);
    if ((*pipeto)->commands_out != NULL)
	    free_strs((*pipeto)->commands_out);
    if ((*pipeto)->paths != NULL)
	    free_strs((*pipeto)->paths);
    if ((*pipeto)->final_paths != NULL)
	    free_strs((*pipeto)->final_paths);
    if ((*pipeto)->final_paths_out != NULL)
	    free_strs((*pipeto)->final_paths_out);
    close_fd(&(*pipeto), fd);
    
	if (*pipeto != NULL)
	    free(*pipeto);
}

void    close_fd(t_pipeto **pipeto, int *fd)
{
    if (*pipeto)
    {
        if ((*pipeto)->fd_in != -1)
        {
            ft_printf("test1");
            close((*pipeto)->fd_in);
            (*pipeto)->fd_in = -1;
        }
        if ((*pipeto)->fd_out != -1)
        {
            ft_printf("test2");
            close((*pipeto)->fd_out);
            (*pipeto)->fd_out = -1;
        }
    }
    
    if (fd[0] != -1)
    {
        ft_printf("test3");
        close(fd[0]);
        fd[0] = -1;
    }
    if (fd[1] != -1)
    {
        ft_printf("test4");
        close(fd[1]);
        fd[1] = -1;
    }
}

void    free_strs(char **strs)
{
    int i;

    i = 0;
    while (strs[i])
    {
        free(strs[i]);
        i++;
        // ft_printf("test\n");
    }
    free(strs);
}
