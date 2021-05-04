#include "../library/common_headers.h"
#include "../library/function_headers.h"

void provide_service(long action)
{
    switch (action)
    {
    case 1:
        // show balance
        printf("show_balance(socket_fd);");
        break;
    case 2:
        printf("close_account(socket_fd);");
        break;
    case 3:
        printf("withdraw(socket_fd);");
        // close account
        break;
    case 4:
        printf("open_account(socket_fd);");
        break;
    case 5:
        printf("Balance");
    default:
        break;
    }
}