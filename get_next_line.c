#include "get_next_line.h"

char    *read_from_fd(int fd, char *stored)
{
    char    *buffer;
    char    *temp;
    ssize_t bytes_read;

    buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
    if (!buffer)
    {
        free(stored);
        return (NULL);
    }
    bytes_read = 1;
    while (!stored || (!ft_strchr(stored, '\n')) && (bytes_read > 0))
    {
        bytes_read = read(fd, buffer, BUFFER_SIZE);
        if (bytes_read < 0)
        {
            free(buffer);
            free(stored);
            return (NULL);
        }
        if (bytes_read == 0)
            break;
        buffer[bytes_read] = '\0';
        temp = ft_strjoin(stored, buffer);
        free(stored);
        stored = temp;
    }
    free(buffer);
    return (stored);
}

char    *extract_line(char *stored)
{
    int     i;
    char    *line;

    if (!stored || !stored[0])
        return (NULL);
    i = 0;
    while (stored[i] && stored[i] != '\n')
        i++;
    if (stored[i] == '\n')
        line = ft_substr(stored, 0, i + 1);
    else
        line = ft_substr(stored, 0, i);
    return (line);
}

char    *update_stored(char *stored)
{
    char    *new_stored;
    int     i;

    i = 0;
    while (stored[i] && stored[i] != '\n')
        i++;
    if (!stored[i])
    {
        free(stored);
        return (NULL);
    }
    new_stored = ft_substr(stored, i + 1, ft_strlen(stored) - i - 1);
    free(stored);
    return (new_stored);
}

char    *get_next_line(int fd)
{
    static char *stored;
    char        *line;

    if (fd < 0 || BUFFER_SIZE <= 0)
        return (NULL);
    stored = read_from_fd(fd, stored);
    if (!stored)
        return (NULL);
    line = extract_line(stored);
    stored = update_stored(stored);
    return (line);
}
