#include "../library/common_headers.h"
#include "../library/function_headers.h"

void read_message(size_t connect_fd)
{
    char message_size[8];
    memset(message_size, 0, sizeof(message_size));
    readn(connect_fd, message_size, 8);
    printf("the size of the message is: %s\n", message_size);

    char *endptr;
    errno = 0;
    long size = strtol(message_size, &endptr, 10);
    if (errno != 0)
    {
        printf("error converting message size to a number\n error code: %s\n", strerror(errno));
        return;
    }

    // no number found
    if (endptr == message_size)
    {
        printf("%s\n", "message size received is not a number");
        return;
    }

    char buff_f[size];
    memset(buff_f, 0, sizeof(buff_f));
    readn(connect_fd, buff_f, sizeof(buff_f));

    printf("server received message from client\n message: %s", buff_f);
}