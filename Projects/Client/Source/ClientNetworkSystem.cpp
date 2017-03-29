#include "ClientNetworkSystem.h"
#include "RakPeerInterface.h"
#include <BitStream.h>
#include "MessageIdentifiers.h"
#include "..\..\Server\Include\PacketTypes.h"

ClientNetworkSystem::ClientNetworkSystem(const std::string& a_serverIP, int a_serverPort) {
	m_rakNet = RakNet::RakPeerInterface::GetInstance();


	RakNet::SocketDescriptor desc; //leave blank to auto assign socket

	m_rakNet->Startup(1, &desc, 1);
	
	RakNet::ConnectionAttemptResult result = m_rakNet->Connect(a_serverIP.c_str(), a_serverPort, nullptr, 0);

}

void ClientNetworkSystem::Update() {
	RakNet::Packet *packet = m_rakNet->Receive();

	while (packet != nullptr) {

		switch (packet->data[0])
		{
		case ID_CONNECTION_REQUEST_ACCEPTED:
			printf("Our connection request has been accepted.\n");
			break;
		case ID_DISCONNECTION_NOTIFICATION:
			printf("We have been disconnected.\n");
			break;
		case ID_CONNECTION_LOST:
			printf("Connection lost.\n");
			break;
		case EPacketType::SERVER_MSG: 
		{
			RakNet::BitStream input(packet->data, packet->length, false);
			input.IgnoreBytes(1);

			int ID;
			RakNet::RakString chatMsg;
			input.Read(ID);
			input.Read(chatMsg);

			printf("%d: %s\n", ID, chatMsg.C_String());
			break;
		}
		default:
			printf("Message with identifier %i has arrived.\n", packet->data[0]);
			break;
		}

		m_rakNet->DeallocatePacket(packet);
		packet = m_rakNet->Receive();
	}
}

void ClientNetworkSystem::TransmitMessage(const std::string &a_str)
{
	RakNet::BitStream output;
	output.Write((unsigned char)EPacketType::CLIENT_MSG);
	//RakNet::RakString testMsg("TEST FROM CLIENT");
	//output.Write(testMsg);

	RakNet::RakString outMsg(a_str.c_str());
	output.Write(outMsg);

	m_rakNet->Send(&output, PacketPriority::HIGH_PRIORITY, PacketReliability::RELIABLE, 0, RakNet::UNASSIGNED_SYSTEM_ADDRESS, true);
}

void ClientNetworkSystem::HandlePackets(const std::vector<RakNet::Packet*> a_packets) {

}