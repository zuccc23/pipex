/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_paths.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dahmane <dahmane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/15 14:02:01 by dahmane           #+#    #+#             */
/*   Updated: 2025/02/19 13:50:57 by dahmane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	get_paths(t_pipeto **pipeto, char **env)
{
	find_path_line(&(*pipeto)->path_line, env);
	(*pipeto)->paths = ft_split((*pipeto)->path_line + 5, ':');
	if (!(*pipeto)->paths)
		return (1);
	join_paths((*pipeto)->paths, (*pipeto)->commands_in[0], &(*pipeto)->f_path);
	join_paths((*pipeto)->paths, (*pipeto)->commands_o[0], &(*pipeto)->f_patho);
	if (!(*pipeto)->f_path || !(*pipeto)->f_patho)
		return (1);
	(*pipeto)->ok_path = get_okpath((*pipeto)->f_path);
	(*pipeto)->ok_path_out = get_okpath((*pipeto)->f_patho);
	if (!(*pipeto)->ok_path || !(*pipeto)->ok_path_out)
		return (1);
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

void	find_path_line(char **path_line, char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strnstr(env[i], "PATH=", 5) != 0)
		{
			*path_line = ft_strnstr(env[i], "PATH=", 5);
			return ;
		}
		i++;
	}
}

int	join_paths(char **paths, char *command, char ***f_path)
{
	int	i;

	i = 0;
	while (paths[i])
		i++;
	*f_path = malloc(sizeof(char *) * (i + 1));
	i = 0;
	while (paths[i])
	{
		(*f_path)[i] = ft_strjoin(paths[i], command);
		if (!(*f_path)[i])
		{
			while (i > 0)
				free((*f_path)[--i]);
			free((*f_path));
			return (1);
		}
		i++;
	}
	(*f_path)[i] = NULL;
	return (0);
}
