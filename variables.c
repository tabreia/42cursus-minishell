/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_status.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bsilva-c <bsilva-c@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 17:16:07 by bsilva-c          #+#    #+#             */
/*   Updated: 2023/05/21 14:08:19 by bsilva-c         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	check_var_within_quotes(t_data *data)
{
	int	i;
	int	quote;

	i = 0;
	quote = FALSE;
	while (data->prompt[i])
	{
		if (quote && (data->prompt[i] == quote))
			quote = FALSE;
		else if ((data->prompt[i] == 34 || data->prompt[i] == 39) && \
		ft_strchr(data->prompt + i + 1, data->prompt[i]))
			quote = (int)data->prompt[i];
		if (quote == 39 && data->prompt[i] == '$')
			if ((ft_isalnum(data->prompt[++i]) || data->prompt[i] == '_'))
				return (TRUE);
		i++;
	}
	return (FALSE);
}

static void	set_home_var(t_data *data)
{
	char	*temp;
	char	*env_var;

	env_var = get_env_var(data, "HOME");
	env_var = ft_strjoin(env_var, "/");
	if (!env_var)
		env_var = "";
	temp = ft_fndnrepl(data->prompt, "~/", env_var);
	free(data->prompt);
	data->prompt = temp;
	free(env_var);
}

static void	set_env_var(t_data *data)
{
	int		k;
	char	*temp;
	char	*env_var;
	char	*var_name;

	temp = ft_strnstr(data->prompt, "$", ft_strlen(data->prompt));
	k = 1;
	while (temp[++k])
	{
		if (!(ft_isalnum(temp[k]) || temp[k] == '_'))
			break ;
	}
	var_name = ft_calloc(k + 1, sizeof(char));
	ft_strlcpy(var_name, temp, k + 1);
	env_var = get_env_var(data, var_name + 1);
	if (!env_var)
		env_var = "";
	temp = ft_fndnrepl(data->prompt, var_name, env_var);
	free(data->prompt);
	data->prompt = temp;
	free(var_name);
}

static void	set_exit_status(t_data *data)
{
	char	*temp;

	temp = ft_fndnrepl(data->prompt, "$?", ft_itoa(data->exit_status));
	free(data->prompt);
	data->prompt = temp;
}

void	check_variables(t_data *data)
{
	if (data->prompt)
	{
		if (ft_strnstr(data->prompt, "~/", ft_strlen(data->prompt)))
		{
			set_home_var(data);
			check_variables(data);
		}
		else if (ft_strnstr(data->prompt, "$?", ft_strlen(data->prompt)))
		{
			set_exit_status(data);
			check_variables(data);
		}
		else if (ft_strnstr(data->prompt, "$", ft_strlen(data->prompt)) \
		&& (ft_isalnum(*(data->prompt + 1)) || *(data->prompt + 1) == '_') \
		&& !check_var_within_quotes(data))
		{
			set_env_var(data);
			check_variables(data);
		}
	}
}
