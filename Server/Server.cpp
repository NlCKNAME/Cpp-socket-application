#include <iostream>
#include <string>
#define  _WINSOCK_DEPRECATED_NO_WARNINGS
#include <winsock2.h>
typedef int socklen_t;
#pragma comment(lib, "ws2_32.lib")

using namespace std;

int main()
{
	#if defined (WIN32)
		WSADATA WSAData;
		int erreur = WSAStartup(MAKEWORD(2, 2), &WSAData);
	#else
		int erreur = 0;
	#endif

	/* Socket et contexte d'adressage du serveur */
	SOCKADDR_IN sin;
	SOCKET sock;
	socklen_t recsize = sizeof(sin);

	/* Socket et contexte d'adressage du client */
	SOCKADDR_IN csin;
	SOCKET csock;
	socklen_t crecsize = sizeof(csin);

	int sock_err;


	if (!erreur)
	{
		/* Création d'une socket */
		sock = socket(AF_INET, SOCK_STREAM, 0);

		/* Si la socket est valide */
		if (sock != INVALID_SOCKET)
		{
			printf("La socket %d est maintenant ouverte en mode TCP/IP\n", sock);

			/* Configuration */
			sin.sin_addr.s_addr = htonl(INADDR_ANY);  /* Adresse IP automatique */
			sin.sin_family = AF_INET;                 /* Protocole familial (IP) */
			sin.sin_port = htons(9999);               /* Listage du port */
			sock_err = bind(sock, (SOCKADDR*)&sin, recsize);

			/* Si la socket fonctionne */
			if (sock_err != SOCKET_ERROR)
			{
				/* Démarrage du listage (mode server) */
				sock_err = listen(sock, 5);
				printf("Listage du port %d...\n", 9999);

				/* Si la socket fonctionne */	
				if (sock_err != SOCKET_ERROR)
				{
					/* Attente pendant laquelle le client se connecte */
					printf("Patientez pendant que le client se connecte sur le port %d...\n", 9999);
					csock = accept(sock, (SOCKADDR*)&csin, &crecsize);
					printf("Un client se connecte avec la socket %d de %s:%d\n", csock, inet_ntoa(csin.sin_addr), htons(csin.sin_port));
					char text2[250];
					recv(sock, text2, sizeof(text2), 0);
					cout << text2 << endl;
					send(sock, text2, sizeof(text2), 0);
				}
				else
					perror("listen");
			}
			else
				perror("bind");

			/* Fermeture de la socket client et de la socket serveur */
			printf("Fermeture de la socket client\n");
			closesocket(csock);
			printf("Fermeture de la socket serveur\n");
			closesocket(sock);
			printf("Fermeture du serveur terminée\n");
		}
		else
			perror("socket");

	#if defined (WIN32)
			WSACleanup();
	#endif
		}

		return EXIT_SUCCESS;
}