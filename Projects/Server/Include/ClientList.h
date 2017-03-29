#pragma once

#include "RakNetTypes.h"
#include <unordered_map>

class ClientList {
public:
	using ClientID = int;

	int AddClient(RakNet::RakNetGUID a_GUID);

	RakNet::RakNetGUID GetClient(int a_ID);
	ClientID GetClientID(RakNet::RakNetGUID a_GUID);

	void RemoveClient(ClientID a_ID);
	void RemoveClient(RakNet::RakNetGUID);

private:
	std::unordered_map<int, RakNet::RakNetGUID> m_IDMap;

private:
	ClientID m_nextID = 0;

};