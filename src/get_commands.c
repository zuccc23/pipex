/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dahmane <dahmane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 14:19:51 by dahmane           #+#    #+#             */
/*   Updated: 2025/02/25 14:22:26 by dahmane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../pipex.h"

int	get_commands(t_pipeto **pipeto, char **argv)
{
	(*pipeto)->commands_in = ft_split1(argv[2], ' ');
	if (!(*pipeto)->commands_in)
		return (1);
	(*pipeto)->commands_o = ft_split1(argv[3], ' ');
	if (!(*pipeto)->commands_o)
		return (1);
	return (0);
}

int	set_paths(t_pipeto **pipeto)
{
	int i = 0;
	(*pipeto)->ok_path = (*pipeto)->commands_in[0];
	(*pipeto)->ok_path_out = (*pipeto)->commands_o[0];
	while ((*pipeto)->commands_in[0][i - 1] != '/')
	{
		i++;
	}
	(*pipeto)->commands_in[0] += i;
	ft_printf("TEST\n");
	(*pipeto)->f_path = NULL;
	(*pipeto)->paths = NULL;
	(*pipeto)->path_line = NULL;
	return (0);
}
