/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_catcher.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbauer <bbauer@student.42.us.org>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/25 11:25:07 by bbauer            #+#    #+#             */
/*   Updated: 2017/04/30 21:23:23 by bbauer           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

extern char		*g_line;

/*
** Frees the g_line pointer. get_next_line() will see that the pointer is NULL
** and start over.
*/

void		reset_prompt(int sig)
{
	if (sig == SIGINT)
	{
		ft_strdel(&g_line);
		ft_putstr("\nMeh$H> ");
	}
}
