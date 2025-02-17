/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_paths.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dahmane <dahmane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 14:02:01 by dahmane           #+#    #+#             */
/*   Updated: 2025/02/17 11:09:54 by dahmane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	get_paths(t_pipeto **pipeto, char **argv, char **env)
{
	find_path_line(&(*pipeto)->path_line, env);
	(*pipeto)->paths = ft_split((*pipeto)->path_line + 5, ':');
    if (!(*pipeto)->paths)
		return (1);
	join_paths((*pipeto)->paths, (*pipeto)->commands_in[0], &(*pipeto)->final_paths);
    join_paths((*pipeto)->paths, (*pipeto)->commands_out[0], &(*pipeto)->final_paths_out);
    if (!(*pipeto)->final_paths || !(*pipeto)->final_paths_out)
		return (1);
	(*pipeto)->ok_path = get_okpath((*pipeto)->final_paths);
    (*pipeto)->ok_path_out = get_okpath((*pipeto)->final_paths_out);
	return (0);
}

int	get_paths_out(t_pipeto **pipeto, char **argv, char **env)
{
	// find_path_line(&(*pipeto)->path_line, env);
	// (*pipeto)->paths = ft_split((*pipeto)->path_line + 5, ':');
    // if (!(*pipeto)->paths)
	// 	return (1);
	// join_paths((*pipeto)->paths, (*pipeto)->commands_in[0], &(*pipeto)->final_paths);
    // if (!(*pipeto)->final_paths)
	// 	return (1);
	// (*pipeto)->ok_path = get_okpath((*pipeto)->final_paths);
	return (0);
}

char	*get_okpath(char **paths)
{
	int	i;
	
	i = 0;
	while (access(paths[i], F_OK) != 0 && paths[i])
		i++;
	return (paths[i]);
}

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
    *final_paths = malloc(sizeof(char *) * (i + 1));
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