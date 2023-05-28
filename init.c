/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsilva-c <bsilva-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 14:16:15 by bsilva-c          #+#    #+#             */
/*   Updated: 2023/05/28 21:43:56 by bsilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	init_envp(t_data *data, char **envp)
{
	int		len;
	char	**temp;

	len = 0;
	while (envp[len])
		len++;
	data->envp.exec_envp = NULL;
	data->envp.envp = ft_calloc(len + 1, sizeof(char **));
	if (!data->envp.envp)
		return ;
	while (len-- > 0)
	{
		temp = ft_split(envp[len], '=');
		data->envp.envp[len] = ft_calloc(2 + 1, sizeof(char *));
		if (!data->envp.envp[len])
			return ;
		data->envp.envp[len][0] = ft_strdup(temp[0]);
		data->envp.envp[len][1] = ft_strdup(temp[1]);
		free_darr((void **)temp);
	}
}

void	init_tmp(t_data *data)
{
	int		i;

	i = 1;
	if (!data->tmp_file)
		data->tmp_file = ft_strdup(".tmp1");
	while (access(data->tmp_file, F_OK) == 0)
	{
		if (data->tmp_file)
			free(data->tmp_file);
		data->tmp_file = ft_strjoin(".tmp", ft_itoa(++i));
	}
}

void	init_pipe_fd(t_data *data)
{
	int	i;

	i = len_darr((void **)data->argv.type);
	data->argv.pipe_fd = ft_calloc(i + 1, sizeof(int *));
	if (!data->argv.pipe_fd)
		return ;
	while (i--)
	{
		data->argv.pipe_fd[i] = ft_calloc(2 + 1, sizeof(int));
		if (!data->argv.pipe_fd[i])
			return ;
	}
}

void	*init_struct(char **envp)
{
	t_data	*data;

	data = malloc(sizeof(t_data));
	if (!data)
		return (0);
	data->interactive = TRUE;
	data->exit_status = 0;
	data->prompt = NULL;
	data->argv.args = NULL;
	data->argv.type = NULL;
	data->argv.pipe_fd = NULL;
	data->tmp_file = NULL;
	init_envp(data, envp);
	return (data);
}
