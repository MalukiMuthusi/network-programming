#include "../library/common_headers.h"
#include "../library/function_headers.h"

/* show account balance */
void show_balance(size_t socket_fd)
{
    printf("Enter your PIN\n");
    char *pin = read_pin();
    /* write the show balance command to the server. */

    char *buff = "{service:'show_balance',data:{account_name:'name_of_account',pin: 123}}";
    char sizeofmessage[8];
    snprintf(sizeofmessage, sizeof(sizeofmessage), "%ld", sizeof(buff));

    printf("send message size to the server:%s\n", sizeofmessage);
    writen(socket_fd, sizeofmessage, sizeof(sizeofmessage));

    printf("sending message to server\n message\t%s\n", buff);
    writen(socket_fd, buff, sizeof(buff));

    /* read the server's response */
    int n;
    char receiveline[MAX_BUFF_SIZE];
    n = recv(socket_fd, receiveline, MAX_BUFF_SIZE, 0);

    if (n == -1)
    {
        throw_error_exit("error: reading show balance reply from the server");
    }
    /* write the balance amount to user output */
    printf("Your balance is: %s\n", receiveline);
    return;
}