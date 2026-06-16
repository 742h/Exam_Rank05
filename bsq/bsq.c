#include <stdio.h>
#include <stdlib.h>

int get_min(int a, int b, int c)
{
    int min = a;
    if (b < min) min = b;
    if (c < min) min = c;
    return min;
}

void solve_bsq(FILE *f)
{
    char *line = NULL;
    size_t cap = 0;
    int len;

    if ((len = getline(&line, &cap, f)) < 4)
    {
        printf("Error: invalid map\n");
        free(line);
        return;
    }

    char full = line[len - 2];
    char obs = line[len - 3];
    char empty = line[len - 4];

    int rows = 0;
    for (int i = 0; i < len - 4; i++)
        rows = rows * 10 + (line[i] - '0');

    if (rows <= 0 || full == obs || full == empty || obs == empty)
    {
        printf("Error: invalid map\n");
        free(line);
        return;
    }
    free(line);

    char **grid = calloc(rows, sizeof(char *));
    int **dp = calloc(rows, sizeof(int *));
    int cols = 0, max = 0, best_y = 0, best_x = 0;
    int valid = 1;

    for (int i = 0; i < rows; i++)
    {
        line = NULL;
        cap = 0;

        if ((len = getline(&line, &cap, f)) <= 0)
        {
            valid = 0;
            break;
        }

        if (line[len - 1] == '\n')
            line[--len] = '\0';

        if (i == 0)
            cols = len;

        if (len != cols)
            valid = 0;

        grid[i] = line;
        dp[i] = calloc(cols, sizeof(int));

        for (int j = 0; j < cols; j++)
        {
            if (grid[i][j] != empty && grid[i][j] != obs)
                valid = 0;

            if (grid[i][j] == empty)
            {
                if (i == 0 || j == 0)
                    dp[i][j] = 1;
                else
                    dp[i][j] = get_min(dp[i-1][j], dp[i][j-1], dp[i-1][j-1]) + 1;

                if (dp[i][j] > max)
                {
                    max = dp[i][j];
                    best_y = i;
                    best_x = j;
                }
            }
        }
    }

    if (valid)
    {
        for (int i = best_y - max + 1; i <= best_y; i++)
            for (int j = best_x - max + 1; j <= best_x; j++)
                grid[i][j] = full;

        for (int i = 0; i < rows; i++)
            printf("%s\n", grid[i]);
    }
    else
        printf("Error: invalid map\n");

    for (int i = 0; i < rows; i++)
    {
        if (grid[i]) free(grid[i]);
        if (dp[i]) free(dp[i]);
    }
    free(grid);
    free(dp);
}

int main(int ac, char **av)
{
    if (ac == 1)
        solve_bsq(stdin);
    else
    {
        for (int i = 1; i < ac; i++)
        {
            FILE *f = fopen(av[i], "r");
            if (f)
            {
                solve_bsq(f);
                fclose(f);
            }
            else
                printf("Error: Cannot open file %s\n", av[i]);

            if (i < ac - 1)
                printf("\n");
        }
    }
    return 0;
}