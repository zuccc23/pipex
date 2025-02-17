/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dahmane <dahmane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 14:14:11 by dahmane           #+#    #+#             */
/*   Updated: 2025/02/16 14:25:41 by dahmane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int     return_error_input(t_pipeto *pipeto)
{
    free_all(pipeto);
    errno = ENOMEM;
    perror("Malloc failed");
    return (1);
}

void	free_all(t_pipeto *pipeto)
{
    if (pipeto->commands_in != NULL)
	    free_strs(pipeto->commands_in);
    if (pipeto->commands_out != NULL)
	    free_strs(pipeto->commands_out);
    if (pipeto->paths != NULL)
	    free_strs(pipeto->paths);
    if (pipeto->final_paths != NULL)
	    free_strs(pipeto->final_paths);

	if (pipeto != NULL)
	    free(pipeto);
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
