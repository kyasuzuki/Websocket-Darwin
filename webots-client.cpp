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

//webots
#include "walk-client.h"
#include <cstdlib>
#include <vector>
#include "webots-client.h"


//using namespace webots;

static easywsclient::WebSocket::pointer ws = NULL;

// if the server sends "WALK 5.8 30.0"
// the Walk function should be called with the parameters 5.8(speed) and 30.0(angle);
// if the server sends "STOPWALK"
// the function stopWalking() should be called and the connection should close;


void handle_motors(const std::string & r){
    size_t curr2 = 0;
    std::string c2 = ""; // the current message in this loop
    double motor_num = 0.0;
    double motor_pos = 0.0;
    std::string r2; 
    while (curr2 < r.length()){
        if (r[curr2] != ' '){
            c2 += r[curr2];
            curr2++;
        } else{
            motor_num = stod(c2);
            r2 = r.substr(curr2 + 1, r.length());
            motor_pos = stod(r2);
            move(motor_num, motor_pos);
           break;
        }
    }
}

void handle_walk(const std::string & r){
    size_t curr2 = 0;
    std::string c2 = ""; // the current message in this loop
    double speed = 0.0;
    double angle = 0.0;
    std::string r2; 
    while (curr2 < r.length()){
        if (r[curr2] != ' '){
            c2 += r[curr2];
            curr2++;
        } else{
            speed = stod(c2);
            r2 = r.substr(curr2 + 1, r.length());
            angle = stod(r2);
            walk(speed, angle);
           break;
        }
    }

}


void handle_message(const std::string & message)
{

    size_t curr = 0; // the cursor
    std::string c (""); // the current message
    printf(">>> %s\n", message.c_str()); 
    while (curr < message.length()){
        if (message[curr] != ' '){
            c += message[curr];
            curr++;
        }
        if (c == "WALK"){
                std::string r = message.substr(curr + 1, message.length()); //remaining string
                handle_walk(r);
                break;
            }
        if (c == "STOPWALK"){
            stopWalking();
            ws->close();
            break;
        }
        if (c == "MOVE_MOTORS"){
            std:: string r = message.substr(curr + 1, message.length()); //remaining string
            handle_motors(r);
            break;
        }
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
