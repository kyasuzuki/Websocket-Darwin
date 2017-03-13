//websocket
#include "easywsclient.hpp" // <-- include only if you don't want compile separately
//#include "easywsclient.cpp"
#ifdef _WIN32
#pragma comment( lib, "ws2_32" )
#include <WinSock2.h>
#endif
#include <assert.h>
#include <stdio.h>
#include <string>
#include <sstream>

//webots
#include "walk-client.h"
#include <cstdlib>
#include <vector>
#include "webots-client.h"


//using namespace webots;

static easywsclient::WebSocket::pointer ws = NULL;


void handle_message(const std::string & message)
{
    std::istringstream str(message);
    std::string cmd; //command
    str >> cmd;

    if (cmd == "WALK"){
        double speed;
        double angle;
        str >> speed;
        str >> angle;
        walk(speed, angle);
        }
    if (cmd == "STOPWALK"){
    stopWalking();
    ws->close();
    }
    if (cmd == "MOVE_MOTORS"){
        double motor_num;
        double motor_pos;
        str >> motor_num;
        str >> motor_pos;
        move(motor_num, motor_pos);
    }
}



int main()
{

#ifdef _WIN32
    INT rc; 
    WSADATA wsaData;

    rc = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (rc) {
        printf("WSAStartup Failed.\n");
        return 1;
    }   
#endif

    ws = easywsclient::WebSocket::from_url("ws://localhost:8126/foo");
    assert(ws);

    ws->send("hello");

    while (ws->getReadyState() != easywsclient::WebSocket::CLOSED) {
        ws->poll();
        ws->dispatch(handle_message);
    }   
    delete ws; 
#ifdef _WIN32
    WSACleanup();
#endif
    return 0;
}
