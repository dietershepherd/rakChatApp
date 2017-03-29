#pragma once

#include <memory>
#include <vector>

class ClientList;

namespace RakNet {
	class RakPeerInterface;
	struct SocketDescriptor;
	struct Packet;
}

class ServerNetworkSystem {
public:
	ServerNetworkSystem(int a_socket);
	~ServerNetworkSystem();
	void Update();
private:
	void HandlePackets(const std::vector<RakNet::Packet*> a_packets);

	std::unique_ptr<ClientList> m_clientList;
	RakNet::RakPeerInterface* m_rakNet;
};