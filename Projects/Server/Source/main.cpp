#include "ServerNetworkSystem.h"

int main(void)
{
	ServerNetworkSystem server(12001);

	while (true) {
		server.Update();
	}
	return 0;
}
