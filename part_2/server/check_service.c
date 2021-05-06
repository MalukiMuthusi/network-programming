#include "../library/common_headers.h"
#include "../library/function_headers.h"

int check_service(const char *message)
{
    char *s1 = "{service:";
    int n;
    if ((strstr(message, s1)) != message)
    {
        printf("no service requested\n");
        return 0;
    }
    char *data = ",data:{";
    char *start_of_d = strstr(message, data);

    char *start_number = message[data - (message + sizeof(s1))];
    size_t s_size = data - start_number - 1;
    char number[s_size];
    if (snprintf(number, s_size, "%s", start_number) == -1)
    {
        printf("error while reading service number from the message \n\t error: %s", strerror(errno));
        return 0;
    }

    char *endptr;
    errno = 0;
    long service_number = strtol(number, &endptr, 10);

    if (errno != 0)
    {
        printf("error when converting service message to number\n error code: %s\n", strerror(errno));
        return 0;
    }

    // no number found
    if (endptr == number)
    {
        printf("error when converting service message to number: no number was found\n");
        return 0;
    }

    printf("the service number interpreted is number: %ld\n", service_number);
    return service_number;
}