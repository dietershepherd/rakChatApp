#include "..\Include\ClientList.h"

ClientList::ClientID ClientList::AddClient(RakNet::RakNetGUID a_GUID)
{
	ClientID id = m_nextID++;
	m_IDMap.emplace(id, a_GUID);
	return id;
}

RakNet::RakNetGUID ClientList::GetClient(int a_ID)
{
	return RakNet::RakNetGUID();
}

ClientList::ClientID ClientList::GetClientID(RakNet::RakNetGUID a_GUID)
{
	for (auto it = m_IDMap.begin(); it != m_IDMap.end(); ++it) {
		if (it->second == a_GUID) {
			return it->first;
		}
	}
	return -1;
}

void ClientList::RemoveClient(ClientID a_ID)
{
	m_IDMap.erase(a_ID);
}

void ClientList::RemoveClient(RakNet::RakNetGUID a_GUID)
{
	ClientID id = GetClientID(a_GUID);
	if (id != -1) {
		m_IDMap.erase(id);
	}
}
