#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include "get_next_line.h"

// Без бонуса
int main(int ac, char **av) {
    int fd;
    char *line;
    int count = 0; // номера строк

    if (ac == 1) {
        fd = 0; // стандартный ввод (stdin)
        printf("Reading from stdin (press Ctrl+D to stop):\n");
    } else {
        fd = open(av[1], O_RDONLY);
        if (fd == -1) {
            write(1, "Cannot read file.\n", 18);
            return (1);
        }
    }

    // Цикл для чтения строк
    while (1) {
        line = get_next_line(fd);
        if (line == NULL) {
            break;
        }
        count++;
        printf("LINE [%d] =\n%s\n", count, line);
        printf("------------\n");
        free(line); // Освобождение памяти
    }

    // Закрытие файла, если ввод был не из stdin
    if (ac > 1) {
        close(fd);
    }
    
    return (0);
}
