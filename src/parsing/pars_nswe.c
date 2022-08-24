//
// Created by user on 23.08.22.
//

#include "cub3d.h"

char *addr_to_path(t_all *game, char *path)
{
	int i;
	int x;
	int y;
	void *img;
	char *adr;
	char *path2 = "../xpm/logo_cub.xpm";

	img = mlx_xpm_file_to_image(&game->mlx, path, &x, &y);
	if (img == NULL || x != 64 || y != 64)
		ft_error("Error: wrong xpm file\n");
	adr = mlx_get_data_addr(img, &x, &y, &i);
	return (adr);
}

void	set_pl_pos(t_all *game, int nswe, double i, double j)
{
	game->pl.pos.x = j;
	game->pl.pos.y = i;
	if (nswe == 'N')
	{
		game->pl.dir.y = -1;
		game->ray.plane.x = 0.66;
	}
	else if (nswe == 'S')
	{
		game->pl.dir.y = 1;
		game->ray.plane.x = -0.66;
	}
	else if (nswe == 'W')
	{
		game->pl.dir.x = -1;
		game->ray.plane.y = -0.66;
	}
	else if (nswe == 'E')
	{
		game->pl.dir.x = 1;
		game->ray.plane.y = 0.66;
	}
}

char *del_n(char *line)
{
	int i = 0;
	char *tmp;
	int len;

	len = ft_strlen(line);
	if (line[len] != '\n')
		line[len + 1] = '\n';
	tmp = malloc (sizeof(char) * len);
	if (!tmp)
		ft_error(RED"del_n malloc"NC);
	while (line[i] != '\n')
	{
		tmp[i] = line[i];
		i++;
	}
//	*tmp2 = &tmp;
//	free(tmp);
	return (tmp);
}

char	*get_text_addr(t_all *game, char *line)
{
	int		i;
	char *tmp;

	i = 0;
	while (ft_isspace(line[i]))
		i++;
	if (line[i] == '.' && line[i + 1] == '.' && line [i + 2] == '/')
	{
//			printf("%s\n", line); //
		tmp = del_n(line);
		printf("tmp = %s\n", tmp);
		return (addr_to_path(game,tmp));
	}
	ft_error(RED"Error: wrong texture file\n"NC);
	return (0);
}

void	pars_nswe(char *line, t_all *game)
{
	if (ft_strncmp(line, "NO ", 3) == 0 && game->map.north == NULL)
		game->map.north = get_text_addr(game,line + 3);
	else if (ft_strncmp(line, "SO ", 3) == 0 && game->map.south == NULL)
		game->map.south = get_text_addr(game,line + 3);
	else if (ft_strncmp(line, "WE ", 3) == 0 && game->map.west == NULL)
		game->map.west = get_text_addr(game,line + 3);
	else if (ft_strncmp(line, "EA ", 3) == 0 && game->map.east == NULL)
		game->map.east = get_text_addr(game,line + 3);
}