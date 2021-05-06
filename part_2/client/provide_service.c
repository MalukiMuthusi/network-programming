#include "../library/common_headers.h"
#include "../library/function_headers.h"

int provide_service(long action, size_t socket_fd)
{
    char *service_name;
    int ask_command = 0;
    switch (action)
    {
    case 1:
        // show balance
        printf("show_balance(socket_fd);");
        show_balance(socket_fd);
        service_name = "show_balance";
        break;
    case 2:
        printf("close_account(socket_fd);");
        service_name = "close_account";
        break;
    case 3:
        printf("withdraw(socket_fd);");
        service_name = "withdraw_money";
        // close account
        break;
    case 4:
        printf("open_account(socket_fd);");
        service_name = "open_account";
        break;
    case 5:
        service_name = "deposit_money";
        printf("deposit_money");
    default:
        ask_command = 1;
        printf("Please select a service.\n");
        break;
    }

    return ask_command;
}