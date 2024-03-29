//
// Created by aurailus on 07/02/19.
//

#ifndef ZEUS_SERVERPLAYERLIST_H
#define ZEUS_SERVERPLAYERLIST_H

#include <vector>
#include <string>
#include "ServerClient.h"
#include "../../util/net/Packet.h"
#include "../../util/net/PacketChannel.h"
#include "../../util/Log.h"

class ServerClients {
public:
    void handleConnect(ENetEvent e);
    void handleDisconnect(ENetEvent e);

    std::vector<ServerClient> clients;
};

#endif //ZEUS_SERVERPLAYERLIST_H
