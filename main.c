#include "so_long.h"


typedef struct data{
	void 	*mlx;
	void 	*mlx_win;
	char 	**map;
	char	**visited;
	int 	n;
	int		m;
	int		start_x;
	int		start_y;
	int		collect;
	int		collect_rem;
	void	*images[8];
	int		step;
} data;

int	ft_test_name(char *s)
{
	int	len;
	int	i;
	int	k;
	char *p;

	len = ft_strlen(s);
	i = 0;
	k = 0;
	p = ".ber";
	while(s[i])
	{
		if(s[i] == '.')
			k++;
		i++;	
	}
	if(k != 1 || len < 5)
		return (1);
	i = len - 4;
	while(s[i] == p[4 - (len-i)])
		i++;
	if (i != len)
		return (1);
	return (0);
}

int ft_fill_map(data *all, int fd)
{
	char	*line;
	char    *ans;
	char 	*tmp;
	int		i;

	i = 0;
	ans = ft_strdup("");
	if(fd == -1)
		return (1);
	all->m = 0;
	all->n = 0;
	line = get_next_line(fd);
	while(line)
	{
		all->n++;
		tmp = ans;
		ans = ft_strjoin(ans,line);
		free(tmp);
		free(line);
		if(ans ==NULL)
			return (1);
		line = get_next_line(fd);
	}
	all->map = ft_split(ans,'\n');
	all->visited = ft_split(ans,'\n');
	all->m = ft_strlen(all->map[0]);
	while(i < all->n)
	{
		if(ft_strlen(all->map[i]) != all->m)
			return (1);
		i++;
	}
	printf("%s",ans);
	if(all->map == NULL)
		return (1);
	return (0);
}
void	ft_fill_elem(data *all, int i, int j, int *o)
{
	int p;

	p = *o;
	if(all->map[i][j] == 'E'){
		if((p&1))
			p = (p|8); 
		p = (p|1);
	}
	else if(all->map[i][j] == 'C'){
		p = (p|2);
		all->collect++;
	}
	else if(all->map[i][j] == 'P'){
		if((p&4))
			p = (p|8);
		p = (p|4);
		all->start_x = i;
		all->start_y = j;
		all->map[i][j] = '0';
	}
	else if(all->map[i][j] != '0' && all->map[i][j] != '1')
		p = (p|8);
	*o = p;
}
int ft_elem_check(data *all)
{
	int	i;
	int	j;
	int p;

	i = 0;
	p = 0; 
	while(i < all->n)
	{
		j = 0;
		while (j < all->m)
		{
			if(i == 0 || j == 0 || i == all->n - 1 || j == all->m -1)
			{
				if(all->map[i][j] != '1')
					return (1);
			}
			ft_fill_elem(all, i, j, &p);
			j++;
		}
		i++;
	}
	if(p != 7)
		return (1);
	return (0);
}

int ft_dfs(data* all, int i, int j)
{
	char c = all->visited[i][j];
	int S = 0;
	if(c == 'C' || c == 'E')
		S++;
	all->visited[i][j] = '1';
	if(all->visited[i + 1][j] != '1')
		S += ft_dfs(all, i + 1, j);
	if(all->visited[i - 1][j] != '1')
		S += ft_dfs(all, i - 1, j);
	if(all->visited[i][j + 1] != '1')
		S += ft_dfs(all, i, j + 1);
	if(all->visited[i][j - 1] != '1')
		S += ft_dfs(all, i, j - 1);
	return (S);
}
int	ft_check_map(data *all, char *str)
{
	int	fd;
	if (!ft_test_name(str))
		return (1);
	fd = open(str, O_RDONLY);
	if(fd == -1)
		return (1);
	if (ft_fill_map(all, fd) || ft_elem_check(all))
		return (1);
	if (ft_dfs(all, all->start_x, all->start_y) != all->collect + 1)
		return (1);
	return (0);
}

void	ft_load_images(data* all)
{
	int	x;
	int	y;
	all->images[0] = mlx_xpm_file_to_image(all->mlx,"./assests/front_side.xpm", &x, &y);
	all->images[1] = mlx_xpm_file_to_image(all->mlx,"./assests/back_side.xpm", &x, &y);
	all->images[2] = mlx_xpm_file_to_image(all->mlx,"./assests/right_side.xpm", &x, &y);
	all->images[3] = mlx_xpm_file_to_image(all->mlx,"./assests/left_side.xpm", &x, &y);
	all->images[4] = mlx_xpm_file_to_image(all->mlx,"./assests/floor.xpm", &x, &y);
	all->images[5] = mlx_xpm_file_to_image(all->mlx,"./assests/wall.xpm", &x, &y);
	all->images[6] = mlx_xpm_file_to_image(all->mlx,"./assests/exit.xpm", &x, &y);
	all->images[7] = mlx_xpm_file_to_image(all->mlx,"./assests/coins.xpm", &x, &y);
}

void	ft_show_image(data* all, char c, int x, int y)
{
	if(c == '1')
		mlx_put_image_to_window(all->mlx, all->mlx_win, all->images[5], x, y);
	else if(c == '0')
		mlx_put_image_to_window(all->mlx, all->mlx_win, all->images[4], x, y);
	else if(c == 'P')
	{
		mlx_put_image_to_window(all->mlx, all->mlx_win, all->images[4], x, y);
		mlx_put_image_to_window(all->mlx, all->mlx_win, all->images[0], x, y);
	}
	else if(c == 'C')
	{
		mlx_put_image_to_window(all->mlx, all->mlx_win, all->images[4], x, y);
		mlx_put_image_to_window(all->mlx, all->mlx_win, all->images[7], x, y);
	}
	else if(c == 'E')
		mlx_put_image_to_window(all->mlx, all->mlx_win, all->images[6], x, y);
}

void	ft_render(data* all)
{
	int	i;
	int	j;

	i = 0;
	while (i < all->n)
	{
		j = 0;
		while(j < all->m)
		{
			if (i == all->start_x && j == all->start_y)
				ft_show_image(all, 'P', i * 50, j * 50);
			else
				ft_show_image(all, all->map[i][j], i * 50, j * 50);
			j++;
		}
		i++;
	}

}

void	ft_movement_frame(data *all, int next_x, int next_y, int p)
{
	int x;
	int y;

	x = all->start_x;
	y = all->start_y;
	all->step++;
	if(all->map[next_x][next_y] == '0')
	{
		if (all->map[x][y] == '0' || all->map[x][y] == 'C' || all->map[x][y] == 'P'){
			all->map[x][y] = '0';
			mlx_put_image_to_window(all->mlx, all->mlx_win, all->images[4], x * 50, y * 50);
		}
		else if(all->map[x][y] == 'E')
		{
			mlx_put_image_to_window(all->mlx, all->mlx_win, all->images[6], x * 50, y * 50);
		}
		mlx_put_image_to_window(all->mlx, all->mlx_win, all->images[4], next_x * 50, next_y * 50);
		mlx_put_image_to_window(all->mlx, all->mlx_win, all->images[p], next_x * 50, next_y * 50);
		all->start_x = next_x;
		all->start_y = next_y;
	}
	else if(all->map[next_x][next_y] == 'C')
	{
		if (all->map[x][y] == '0' || all->map[x][y] == 'C' || all->map[x][y] == 'P'){
			all->map[x][y] = '0';
			mlx_put_image_to_window(all->mlx, all->mlx_win, all->images[4], x * 50, y * 50);
		}
		else if(all->map[x][y] == 'E')
		{
			mlx_put_image_to_window(all->mlx, all->mlx_win, all->images[6], x * 50, y * 50);
		}
		all->map[next_x][next_y] = '0';
		all->collect_rem++;
		mlx_put_image_to_window(all->mlx, all->mlx_win, all->images[4], next_x * 50, next_y * 50);
		mlx_put_image_to_window(all->mlx, all->mlx_win, all->images[p], next_x * 50, next_y * 50);
		all->start_x = next_x;
		all->start_y = next_y;
	}
	else if(all->map[next_x][next_y] == 'E')
	{
		if (all->map[x][y] == '0' || all->map[x][y] == 'C'){
			all->map[x][y] = '0';
			mlx_put_image_to_window(all->mlx, all->mlx_win, all->images[4], x * 50, y * 50);
		}
		mlx_put_image_to_window(all->mlx, all->mlx_win, all->images[6], next_x * 50, next_y * 50);
		mlx_put_image_to_window(all->mlx, all->mlx_win, all->images[p], next_x * 50, next_y * 50);
		all->start_x = next_x;
		all->start_y = next_y;
	}
}

void	ft_move_left(data *all)
{
	int player_x;
	int player_y;

	player_x = all->start_x - 1;
	player_y = all->start_y;
	if(all->map[player_x][player_y] != '1')
		ft_movement_frame(all, player_x, player_y, 3);
}
void	ft_move_right(data *all)
{
	int player_x;
	int player_y;

	player_x = all->start_x + 1;
	player_y = all->start_y;
	if(all->map[player_x][player_y] != '1')
		ft_movement_frame(all, player_x, player_y, 2);
}
void	ft_move_back(data *all)
{
	int player_x;
	int player_y;

	player_x = all->start_x;
	player_y = all->start_y - 1;
	if(all->map[player_x][player_y] != '1')
		ft_movement_frame(all, player_x, player_y, 1);
}
void	ft_move_front(data *all)
{
	int player_x;
	int player_y;

	player_x = all->start_x;
	player_y = all->start_y + 1;
	if(all->map[player_x][player_y] != '1')
		ft_movement_frame(all, player_x, player_y, 0);
}

int keypress(int keycode, data *all)
{
	printf("%d \n",keycode);
	if (keycode == 2 || keycode == 124)
		ft_move_right(all);
	else if (keycode == 0 || keycode == 123)
		ft_move_left(all);
	else if (keycode == 1 || keycode == 125)
		ft_move_front(all);
	else if (keycode == 13 || keycode == 126)
		ft_move_back(all);
	else if (keycode == 53)
	{
		mlx_destroy_window(all->mlx, all->mlx_win);
		exit(1);
	}
	if(all->map[all->start_x][all->start_y] == 'E' && all->collect == all->collect_rem)
	{
		mlx_destroy_window(all->mlx, all->mlx_win);
		exit(1);
	}
	return (0);
}

void init_data(data *all)
{
	all->mlx = NULL;
	all->mlx_win = NULL;
	all->map = NULL;
	all->n = 0;
	all->m = 0;
	all->start_x = 0;
	all->start_y = 0;
	all->collect = 0;
	all->collect_rem = 0;
	all->images[0] = NULL;
	all->images[1] = NULL;
	all->images[2] = NULL;
	all->images[3] = NULL;
	all->images[4] = NULL;
	all->images[5] = NULL;
	all->images[6] = NULL;
	all->images[7] = NULL;
	all->step = 0;
}
int main(int arg, char **args)
{
	data *all;
	
	all = (data *)malloc(sizeof(data));
	init_data(all);
	if(arg != 2 || ft_check_map(all, args[1]))
	{
		printf("\033[1;31m🛑ERROR: \033[0mSomething went wrong!\n");
		exit(1);
	}
	all->mlx = mlx_init();
	all->mlx_win = mlx_new_window(all->mlx, all->n * 50, all->m * 50, "Hello world!");
	//Load images
	ft_load_images(all);
	ft_render(all);
	mlx_hook(all->mlx_win, 2, (1L << 0), keypress, all);
	//mlx_hook(all->mlx_win, 17, (1L << 0), ft_exit, all);
	mlx_loop(all->mlx);
}