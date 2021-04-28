# Online Banking application

The application simulates a user using online banking using USSD.

## The services the application provides include

- Opening account
- Closing account
- Withdraw amount
- Deposit amount
- Check balance and provide account statement

## The Design Architecture

The server listens and waits for clients to make requests for services.
When a clients makes a connection to the server, the client authenticates by providing a PIN.
The server responses with a SUCCESS or FAILURE status.
On a SUCCESS status the client can proceed to ask for the other services.

When a client needs a particular service, eg Withdraw Account, it sends a request code for that service.
The server identifies the request code and offers the indicated in the request code.

### Application Protocol

How the server and clients exchange information is based on our custom application protocol.
The client indicates the service they want through a special CODE. The CODE is a digit for a particular service.
The CODE for each service is as follows:

1. Open Account
2. Close Online Account service
3. Withdraw amount
4. Deposit amount
5. Check balance/Bank statement

The server also sends all the necessary data back to the client. The data is sent as a string message.
The client application understands the message and it can process it.
For example when client asks for the withdraw amount service, the client can interpret the message returned from the server that has the amount for the account.

The server authenticates the client by responding with a status CODE.
0 -> SUCCESS
1 -> FAILURE
