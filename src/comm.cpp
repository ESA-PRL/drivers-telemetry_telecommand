
#include "comm.h"
#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>

#include <time.h> 
#include "linuxOrcc.h"

using std::string;
using std::ostringstream;
using std::istringstream;

extern "C" int orcExecAct(const char* rtname, const char *rtparams, int req_id); 

//extern void orcGetTmMsg(std::string &tmmsg);

//extern CommTcReplyServer* tcReplyServer;

int handleTcMsg(CommTcServer *, char *msg);

void choppy( char *s )
{
    s[strcspn ( s, "\n" )] = '\0';
}


CommServer::CommServer(int port)
{
  Running = 1;
  Connected = 0;
  Port = port;
  theStatus = 0;

}
CommServer::~CommServer() {
  Running = 0;
  Close();
  //  sleep(1);
}


int CommServer::GetStatus() {
  return theStatus;
}
void CommServer::StopRunning() {
  Running = 0;
}
void  CommServer::Close() {
  if (Client != NULL) 
    SDLNet_TCP_Close(Client);
  if (Server != NULL)
    SDLNet_TCP_Close(Server);
}

CommandInfo::CommandInfo(std::string activity_name, std::string activity_param) {
  activityName.append(activity_name);
  activityParams.append(activity_param);
}
CommTcServer::CommTcServer(int port): CommServer(port) {

  fprintf (stdout, "=== CommTcServer::CommTcServer \n");
  if ( createThread() == ERROR ) {
    fprintf (stdout, "=== CommTcServer::createThread failed \n");
    return;
  }
  theStatus = 1;
  fprintf (stdout, "=== CommTcServer::CommTcServer OK \n");
}
void CommTcServer::addCommandInfo(CommandInfo *cmd_info) {
  cmdList.push_back( cmd_info ); 
}
CommandInfo* CommTcServer::extractCommandInfo() {
  std::list<CommandInfo*>::iterator pr; 
  if (cmdList.size() == 0) {
    return NULL;
  }
  pr = cmdList.begin();
  cmdList.clear();
  return (*pr);
}

void* CommTcServer::thread() {
  IPaddress ip;

  if (SDLNet_ResolveHost(&ip, NULL, Port) == -1) {
    //    fprintf (stdout, "SDLNet_ResolveHost %s\n", SDLNet_GetError());
    theStatus = 0;
  }
  Server = SDLNet_TCP_Open(&ip); 
  if (!Server) { 
    //    fprintf (stdout, "SDLNet_TCP_Open %s\n", SDLNet_GetError());
    theStatus = 0;
  } 

  while (Running == 1) {

    if (Connected == 0) {
      Client = SDLNet_TCP_Accept(Server); 
      if (!Client) { 
	//fprintf (stdout, "SDLNet_TCP_Accept %s\n", SDLNet_GetError()); 
	sleep(1);
      }	
      else {
	fprintf (stdout, "CommTcServer accepted connection\n", SDLNet_GetError());
	Connected = 1; 
      }
    }				
    else {
      char msg[1024];
      char dummych[80];
      char ackidch[80];
      
      memset((char *)msg, 0, sizeof(msg)); 
      
      int result = SDLNet_TCP_Recv(Client, msg, 1024); 
      if (result <= 0) { 
	fprintf (stdout, "SDLNet_TCP_Recv %s\n", SDLNet_GetError()); 
	Connected = 0;
      }
      else {
	choppy(msg);
	
	std::cerr << "TC Received Message: ->" << msg << "<--" << std::endl;
	int token = sscanf(msg, "%s %s %s %s %s", // %s %s\n", 
			   ackidch, dummych, dummych, dummych, dummych); 
	// , dummych, dummych, dummych); 
	string ackid(ackidch);
	if (token < 5) {
	  std::cerr << "Less than five tokens received: " << token << std::endl;
	  string send_msg(ackid + " -1 RspError\n");
	  result = SDLNet_TCP_Send(Client, 
				   (void *)(send_msg.c_str()), 
				   send_msg.length()); 
	  if (result <= 0) { 
	    fprintf (stdout, "SDLNet_TCP_Send %s\n", SDLNet_GetError()); 
	    Connected = 0;
	  }
	  std::cerr << "The message is disgarded" << std::endl;
	}
	else {
	  
	  string send_msg(ackid + " 0 RspAck\n");
	  //result = tcReplyServer->sendData((char *)send_msg.c_str());
	  
	  int rc = handleTcMsg(this, msg);
	}
      }
    }
  }
  
}

CommTcReplyServer::CommTcReplyServer(int port): CommServer(port) {

  fprintf (stdout, "=== CommTcReplyServer::CommTcReplyServer \n");
  if ( createThread() == ERROR ) {
    fprintf (stdout, "=== CommTcReplyServer::createThread failed \n");
    return;
  }
  theStatus = 1;
  fprintf (stdout, "=== CommTcReplyServer::CommTcReplyServer OK \n");
}
int CommTcReplyServer::sendData (char *buffer)
{
  fprintf (stderr, "CommTcReply::sendData %s\n", buffer);
  if (Connected == 1) {
    int result = SDLNet_TCP_Send(Client, (void *)buffer, (strlen(buffer)));
    if (result <= 0) { 
      fprintf (stdout, "CommTcReply SDLNet_TCP_Send %s\n", SDLNet_GetError()); 
      Connected = 0;
      fprintf (stderr, "CommTcReply::sendData not sent\n");
      return result;
    }
    else {
      //fprintf (stdout, "sent\n");
      return result;
    }
  }
  return 0;
}
void* CommTcReplyServer::thread() {
  IPaddress ip;

  if (SDLNet_ResolveHost(&ip, NULL, Port) == -1) {
    fprintf (stdout, "SDLNet_ResolveHost %s\n", SDLNet_GetError());
    theStatus = 0;
  }
  Server = SDLNet_TCP_Open(&ip); 
  if (!Server) { 
    fprintf (stdout, "SDLNet_TCP_Open %s\n", SDLNet_GetError());
    theStatus = 0;
  } 

  while (Running == 1) {
    
    if (Connected == 0) {
      Client = SDLNet_TCP_Accept(Server); 
      if (!Client) { 
	//fprintf (stdout, "SDLNet_TCP_Accept %s\n", SDLNet_GetError()); 
	sleep(1);
      }	
      else {
	fprintf (stdout, "CommTcReplyServer accepted connection %s\n", SDLNet_GetError());
	Connected = 1; 
      }
    }				
    else {
      char msg[1024];

      msg[0] = '\0'; 
      int result = SDLNet_TCP_Recv(Client, msg, 1024); 
      if (result <= 0) { 
	fprintf (stdout, "SDLNet_TCP_Recv %s\n", SDLNet_GetError()); 
	Connected = 0;
      }
    }
  }
}


CommTmServer::CommTmServer(int port, RobotProcedure* prr, ActiveMQTMSender* actmqtmsender, RoverName rn): CommServer(port) {

  this->prr = prr;
  this->activemqTMSender = actmqtmsender; 
  this->rover = rn;
  fprintf (stdout, "=== CommTmServer::CommTmServer \n");
  if ( createThread() == ERROR ) {
    fprintf (stdout, "=== CommTmServer::createThread failed \n");
    return;
  }
  theStatus = OK;
  Running = TRUE;
  fprintf (stdout, "=== CommTmServer::CommTmServer OK \n");
}
void* CommTmServer::thread() {
  IPaddress ip;
  string send_msg;
  
/*
  if (SDLNet_ResolveHost(&ip, NULL, Port) == -1) {
    fprintf (stdout, "SDLNet_ResolveHost %s\n", SDLNet_GetError());
    theStatus = ERROR;
  }
  Server = SDLNet_TCP_Open(&ip); 
  if (!Server) { 
    fprintf (stdout, "SDLNet_TCP_Open %s\n", SDLNet_GetError());
    theStatus = ERROR;
  } 
  */
  while (Running == TRUE) {
    
    if (Connected == FALSE) {
      
	Connected = TRUE;
/*
      Client = SDLNet_TCP_Accept(Server); 
      if (!Client) { 
	//fprintf (stdout, "SDLNet_TCP_Accept %s\n", SDLNet_GetError()); 
	sleep(1);
      }	
      else {
	Connected = TRUE;
      }
*/
    }				
    else {
      send_msg.clear();
      orcGetTmMsg(send_msg);
      if (send_msg.length()>0)
      {
        int result = 1;
/*
      	int result = SDLNet_TCP_Send(Client, 
				   (void *)(send_msg.c_str()), 
				   send_msg.length());
        if (result <= 0) { 
	  fprintf (stdout, "TmServer SDLNet_TCP_Send %s\n", SDLNet_GetError()); 
	  Connected = FALSE;
        }
        else {
	  sleep( 1 );
        }
*/sleep( 1 );
      }
      else {
	sleep (1);
      }
    }
  }
}



string& triml(string &s) {
  int pos(0);
  for ( ; s[pos] == ' ' || s[pos] == '\t'; ++pos);
  s.erase(0,pos);
  return s;
  
}

string& trimr(string &s) {
  int pos(s.size());
  for ( ; s[pos-1] == ' ' || s[pos] == '\t'; --pos);
  s.erase(pos, s.size()-pos);
  return s;
}


CommClient::CommClient(int port) 
{
  Running = 1;
  Connected = 0;
  Port = port;
  theStatus = 0;  
  if ( createThread() == ERROR ) {
    fprintf (stdout, "=== CommClient::createThread failed \n");
    return;
  }
  theStatus = 1;
}
CommClient::~CommClient() {
  Close();
  Running = 0;
  sleep(1);
}

void* CommClient::thread() {
  IPaddress ip;
  
  
  if (SDLNet_ResolveHost(&ip, "pc-1", Port) == -1) {
    std::cerr << "SDLNet_ResolveHost: " <<  SDLNet_GetError() << std::endl;
    theStatus = 0;
  }

  while (Running == 1) {

    if (Connected == 0) {
      
      Client = SDLNet_TCP_Open(&ip); 
      if (!Client) { 
	//std::cerr << "SDLNet_TCP_Open failed: (pc-1," <<  Port << ")" << std::endl;
	theStatus = 0;
	sleep(1);
      } 
      else {
	Connected = 1;
	std::cerr << "CommClient connected: " << Port << std::endl; 
      }
    }				
    else {
      sleep(3);
    }
  }
}
int CommClient::sendData (char *buffer)
{
  // fprintf (stderr, "CommClient::sendData %s\n", buffer);
  if (Connected == 1) {
    int result = SDLNet_TCP_Send(Client, (void *)buffer, (strlen(buffer)));
    if (result <= 0) { 
      fprintf (stdout, "CommClient SDLNet_TCP_Send %s\n", SDLNet_GetError()); 
      Connected = 0;
      fprintf (stderr, "CommClient::sendData not sent\n");
      return result;
    }
    else {
      //fprintf (stdout, "sent\n");
      return result;
    }
  }
}
int CommClient::readData (char *msg)
{
  int result = -1;
  if (Connected == 1) {
    result = SDLNet_TCP_Recv(Client, msg, 1024); 
    if (result <= 0) { 
      fprintf (stderr, "CommClient SDLNet_TCP_Recv %s\n", SDLNet_GetError()); 
      Connected = 0;
    }
    return result;
  }
}
int CommClient::GetStatus() {
  return theStatus;
}
void CommClient::StopRunning() {
  Running = 0;
}
void  CommClient::Close() {
  if (Client)
    SDLNet_TCP_Close(Client);
  if (Server)
    SDLNet_TCP_Close(Server);
}


int handleTcMsg(CommTcServer *tc_server, char *msg) {
  
  char ackid[80], 
    actionname[80], 
    actioncmd[80], 
    actionparam[280];
  int rcv_rc, send_rc, cmd_id;
  
  std::cerr << " - handleTcMsg: ->" << msg << "<--" << std::endl;
  
  // 
  // Count the number off tokens
  // 
  char tmp_msg[1024];
  strcpy(tmp_msg, msg);
  int total_tokens_nbr = 0;
  char *tmp_token_str = strtok(tmp_msg, " ");
  while(tmp_token_str != NULL) {
    total_tokens_nbr++;
    tmp_token_str = strtok(NULL, " ");
  }

  strcpy(actionparam, "\0");
  int tokens_nbr = 0;
  char *token_str = strtok(msg, " ");
  while(token_str != NULL) {
    tokens_nbr++;
    if (tokens_nbr == 1) {
      strcpy(ackid, token_str);
      strcat(actionparam, ackid);
      strcat(actionparam, " ");
    }
    else if (tokens_nbr == 5) {
      strcpy(actionname, token_str);
      strcpy(actioncmd, "START");
    }
    else if (tokens_nbr > 6 && tokens_nbr <= total_tokens_nbr) {
      strcat(actionparam, token_str);
      if (tokens_nbr < (total_tokens_nbr)) strcat(actionparam, " ");
    }
    token_str = strtok(NULL, " ");
  }
  
  std::cerr << "Name of the Action ->" << actionname << "<--" << std::endl
	    << "Action Cmd = ->" << actioncmd << "<--" << std::endl
	    << "Action Params = ->" << actionparam << "<--" << std::endl;
  
  if (!strcmp(actioncmd, "START")) {
    CommandInfo *cmd_info = new CommandInfo(actionname, actionparam);
    tc_server->addCommandInfo(cmd_info);
  }
  else
    {
      std::cout << "action " << actionname << " to be executed by Rock" << std::endl;
    }
return OK;

}
