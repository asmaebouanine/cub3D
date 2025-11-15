/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parssing.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: wnid-hsa <wnid-hsa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/02 17:28:40 by wnid-hsa          #+#    #+#             */
/*   Updated: 2025/11/15 21:35:43 by wnid-hsa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3D.h"

int	valid_extension(char *argv)
{
	int	len;

	if (!argv)
		return (0);
	len = ft_strlen(argv);
	if ((argv + len - 4) && !ft_strcmp(argv + len - 4, ".cub"))
		return (1);
	else
		return (0);
}

t_config	*parsser_core(int argc, char **argv, t_config **config)
{
	int	fd;

	if (argc == 2 && valid_extension(argv[1]))
	{
		fd = open(argv[1], O_RDONLY);
		if (fd >= 0)
		{
			gc_fds(fd);
			if (!parssing(fd))
			{
				printf("enter a valid map/config file\n");
				return (NULL);
			}
			else
			{
				*config = config_struct();
				if (*config)
					fill_config_struct(argv[1], config);
			}
		}
		else
			printf("enter a valid map/config file\n");
	}
	else
		printf("enter a valid map/config file\n");
	return (*config);
}

t_config	*parsser(int argc, char **argv)
{
	t_config	*config;

	config = NULL;
	return (parsser_core(argc, argv, &config));
}

int	parssing(int fd)
{
	t_identifiers	*identifiers;

	identifiers = gcmalloc(sizeof(t_identifiers), 0);
	if (!identifiers)
		return (0);
	identifiers->no = 0;
	identifiers->so = 0;
	identifiers->we = 0;
	identifiers->ea = 0;
	identifiers->f = 0;
	identifiers->c = 0;
	return (parssing_core(fd, identifiers));
}
