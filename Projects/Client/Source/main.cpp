#include "ClientNetworkSystem.h"
#include <iostream>
#include <sstream>

using namespace std;

int main(void)
{
	ClientNetworkSystem client("127.0.0.1",12001);

	while (true) {
		client.Update();

		string inputString = "";
		getline(cin, inputString);
		client.TransmitMessage(inputString);
		
	}

	return 0;
}
