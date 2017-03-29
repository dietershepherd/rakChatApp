#pragma once

#include <memory>
#include <vector>

namespace RakNet {
	class RakPeerInterface;
	class RakString;
	struct SocketDescriptor;
	struct Packet;
}

class ClientNetworkSystem {
public:
	ClientNetworkSystem(const std::string& a_serverIP, int a_serverPort);

	void Update();
	void TransmitMessage(const std::string &a_str);
private:
	void HandlePackets(const std::vector<RakNet::Packet*> a_packets);
	RakNet::RakPeerInterface* m_rakNet;
};