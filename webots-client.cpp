
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

using namespace std;
static easywsclient::WebSocket::pointer ws = NULL;

// "WALK 5.8 30.0"
// walk --> Walk(5,8 30.0);
// "STOPWALK"
// stopWalking();

void handle_message(const std::string & message)
{
  
  size_t curr = 0; // the cursor
  string c (""); // the current message
  printf(">>> %s\n", message.c_str());

  while (curr < message.length()){
      if (message[curr] != ' '){
          c.append(message[curr]);
          curr++;
      } else{
          if (c == "WALK"){
             string r = message.substr(curr + 1,message.length()); //remaining string
             handle_walk(r);
          }
          if (c == "STOPWALK"){
              stopWalking();
              ws->close();
              break;
              }
          }
  }
}


void handle_walk(const string & r){
    size_t curr2 = 0;
    string c2 = ""; // the current message in this loop
    double speed = 0.0;
    double angle = 0.0;
    string r2; 
    while (curr2 < r.length()){
        if (r[curr2] != ' '){
            c2.append(m[curr2]);
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
 

int main()
{
using easywsclient::WebSocket;
#ifdef _WIN32
  INT rc; 
  WSADATA wsaData;

  rc = WSAStartup(MAKEWORD(2, 2), &wsaData);
  if (rc) {
    printf("WSAStartup Failed.\n");
    return 1;
  }   
#endif

  ws = WebSocket::from_url("ws://localhost:8126/foo");
  assert(ws);
  ws->send("command STOPWALK recieved");
  ws->send("command WALK recieved");
  ws->send("hello");
  while (ws->getReadyState() != WebSocket::CLOSED) {
    ws->poll();
    ws->dispatch(handle_message);
  }   
  delete ws; 
#ifdef _WIN32
  WSACleanup();
#endif
  return 0;
}
