#include <iostream>
#include <string>
#define  _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")

using namespace std;

int main()
{
    WSADATA WSAData;
    SOCKET sock;
    SOCKADDR_IN sin;
    char buffer[255];
    WSAStartup(MAKEWORD(2,0), &WSAData);
    /* Tout est configuré pour se connecter sur IRC, haarlem, Undernet. */
    sock = socket(AF_INET, SOCK_STREAM, 0);
    sin.sin_addr.s_addr = inet_addr("127.0.0.1");
    sin.sin_family = AF_INET;
    sin.sin_port = htons(9999);
    connect(sock, (SOCKADDR *)&sin, sizeof(sin));

	if (connect(sock, (SOCKADDR*)&sin, sizeof(sin)))
	{
		cout << "Connecte. Texte a envoyer : ";
		string text;
		cin >> text;
		cout << endl;
		send(sock, "eee", 3, 0);
		recv(sock, buffer, sizeof(buffer), 0);
	}
    closesocket(sock);
    WSACleanup();
    return 0;
}