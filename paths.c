/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   paths.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dahmane <dahmane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 14:19:51 by dahmane           #+#    #+#             */
/*   Updated: 2025/02/14 14:22:50 by dahmane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void    find_path_line(char **path_line, char **env)
{
    int i;

    i = 0;
      while (env[i]) {
        if (ft_strnstr(env[i], "PATH=", 5) != 0)
        {
            *path_line = ft_strnstr(env[i], "PATH=", 5);
            return ;
        }
        i++;
    }
}

int    join_paths(char **paths, char *command, char ***final_paths)
{
    int i;
    int j;

    i = 0;
    while (paths[i])
        i++;
    *final_paths = malloc(sizeof(char *) * i + 1);
    i = 0;
    while (paths[i])
    {
        (*final_paths)[i] = ft_strjoin(paths[i], command);
        if (!(*final_paths)[i])
			{
				while (i > 0)
					free((*final_paths)[--i]);
				free((*final_paths));
				return (1);
			}
        i++;
    }
    (*final_paths)[i] = NULL;
    return (0);
}
