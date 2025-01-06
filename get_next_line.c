#include "get_next_line.h"

char	*ft_strdup(char *src)
{
	char	*dest;
	int		i = 0;

	while (src[i])
		i++;
	dest = (char *)malloc(sizeof(char) * (i + 1)); // allocate memory for a new string (strlen + 1)
	i = 0;
	while (src[i])
	{
		dest[i] = src[i]; // copy the source string into the new string
		i++;
	}
	dest[i] = '\0'; // terminate the new string with /0
	return (dest); // return the new string
}

char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE];
	char		line[70000];
	static int	buffer_read;
	static int 	buffer_pos;
	int		i = 0;

	if (fd < 0 || BUFFER_SIZE <= 0) // check if the file descriptor and BUFFER_SIZE are valid
		return (NULL);
	while (1) // enter an infinite loop to read the file
	{
		if (buffer_pos >= buffer_read) // read from the file into the buffer
		{
			buffer_read = read(fd, buffer, BUFFER_SIZE);
			buffer_pos = 0; // reset the buffer position to 0
			if (buffer_read <= 0) // // breaks loop if no characters were read
				break ;
		}
		line[i++] = buffer[buffer_pos++]; // copy characters and increment buffer_pos and line index
		if (buffer[buffer_pos] == '\n') //if a newline character is found, break the loop
			break ;
	}
	line[i] = '\0'; // terminate the line with a null character
	if (i == 0)
		return (NULL);
	return (ft_strdup(line)); // return a copy of the line or NULL if no characters were read
}

/*
int main()
{
	int fd = open("./file.txt", O_RDONLY);;
	char *line;

	while ((line = get_next_line(fd)))
		printf("%s", line);
	return (0);
}*/
