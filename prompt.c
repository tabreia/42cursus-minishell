/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tabreia- <tabreia-@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/20 19:03:13 by tabreia-          #+#    #+#             */
/*   Updated: 2023/04/25 14:23:12 by bsilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	char	*temp;
	t_data	*data;

	data = init_struct();
	while (1)
	{
		data->prompt = readline("\x1B[1;32m(Minishell)$ \x1B[0m");
		if (!ft_strncmp(data->prompt, "exit", ft_strlen("exit")))
			shell_exit(data->prompt);
		else if (!ft_strncmp(data->prompt, "cd", ft_strlen("cd")))
			change_dir(data->prompt);
		else if (!ft_strncmp(data->prompt, "pwd", ft_strlen("pwd")))
			pwd();
		else if (!ft_strncmp(data->prompt, "$", ft_strlen("$")))
		{
			temp = ft_strtrim(data->prompt, "$");
			getenv(temp);
			free(temp);
		}
		else
			run_executable(data->prompt);
		if (*data->prompt)
			add_history(data->prompt);
	}
}
