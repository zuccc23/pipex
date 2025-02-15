/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_commands.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dahmane <dahmane@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/14 14:19:51 by dahmane           #+#    #+#             */
/*   Updated: 2025/02/15 14:51:04 by dahmane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	get_commands(t_pipeto **pipeto, char **argv)
{
	(*pipeto)->commands_in = ft_split1(argv[2], ' ');
	if (!(*pipeto)->commands_in)
		return (1);
	(*pipeto)->commands_out = ft_split1(argv[3], ' ');
	if (!(*pipeto)->commands_out)
		return (1);
	return (0);
}
