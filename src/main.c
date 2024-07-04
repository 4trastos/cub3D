#include "../incl/cube3d.h"

char    **arg_check(int argc, char **argv, t_design *design, char **map)
{
    int fd;

    if (argc != 2)
        error_msg("Invalid number of arguments!", NULL);
    fd = open(argv[1], O_RDONLY);
    if (fd < 0)
    {
        perror("Error opening file!");
		exit(EXIT_FAILURE);
    }
    if (!ft_strmapcmp(argv[1], ".cub", 4))
        error_msg("The file is invalid, use a .cub file!", NULL);
    return (map_check(fd, design, map));
}

int main(int argc, char **argv)
{
    char        **map;
    t_design    *design;

    design = new_design();
    map = NULL;
    if (argc == 1)
        error_msg("You have to upload a file to play!", NULL);
    map = arg_check(argc, argv, design, map);
    init_game(map, design);
    free(design);
    free_map(map);
    return (0);
}
