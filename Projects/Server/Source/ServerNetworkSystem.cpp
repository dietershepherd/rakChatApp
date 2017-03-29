#include "ServerNetworkSystem.h"
#include "RakPeerInterface.h"
#include "MessageIdentifiers.h"
#include "ClientList.h"
#include "BitStream.h"
#include "PacketTypes.h"
#include <string>

ServerNetworkSystem::ServerNetworkSystem(int a_socket)
	: m_clientList(std::make_unique<ClientList>())
{
	m_rakNet = RakNet::RakPeerInterface::GetInstance();

	RakNet::SocketDescriptor desc(a_socket, INADDR_ANY);


	m_rakNet->Startup(16, &desc, 1);
	m_rakNet->SetMaximumIncomingConnections(16);


}


ServerNetworkSystem::~ServerNetworkSystem() = default;

void ServerNetworkSystem::Update() {
	RakNet::Packet *packet = m_rakNet->Receive();

	while (packet != nullptr) {

		switch (packet->data[0])
		{
		case ID_NEW_INCOMING_CONNECTION:
		{
			ClientList::ClientID id = m_clientList->AddClient(packet->guid);
			printf("New incoming connection. with ID %d\n", id);
			break;
		}
		case ID_DISCONNECTION_NOTIFICATION:
		{
			printf("We have been disconnected.\n");
			break;
		}
		case ID_CONNECTION_LOST:
		{
			printf("Connection lost.\n");
			break;
		}
		case EPacketType::CLIENT_MSG: 
		{
			RakNet::BitStream input(packet->data, packet->length, false);
			input.IgnoreBytes(1);

			RakNet::RakString chatMsg;
			input.Read(chatMsg);

			//// prepend client ID and broadcast to all
			//ClientList::ClientID id = m_clientList->GetClientID(packet->guid);
			////std::string outMsg(std::to_string(id) + chatMsg);
			//RakNet::RakString outMsg(std::to_string(id).c_str());
			//outMsg += RakNet::RakString(": ");
			//outMsg += chatMsg;

			ClientList::ClientID id = m_clientList->GetClientID(packet->guid);

			RakNet::BitStream output;
			output.Write((unsigned char)EPacketType::SERVER_MSG);
			output.Write(id);
			output.Write(chatMsg);

			m_rakNet->Send(&output, PacketPriority::HIGH_PRIORITY, PacketReliability::RELIABLE, 0, RakNet::UNASSIGNED_SYSTEM_ADDRESS, true);

			break;
		}

		default:
		{
			printf("Message with identifier %i has arrived.\n", packet->data[0]);
			break;
		}
		}

		m_rakNet->DeallocatePacket(packet);
		packet = m_rakNet->Receive();
	}
}
void ServerNetworkSystem::HandlePackets(const std::vector<RakNet::Packet*> a_packets) {

}