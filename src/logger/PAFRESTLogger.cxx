#include "PAFRESTLogger.h"
#include <TSocket.h>
#include "TObjArray.h"
#include "TObjString.h"
#include "TString.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include "TSystem.h"
#include "TObjArray.h"
#include <string>
#include "PAFLogger.h"



PAFRESTLogger *PAFRESTLogger::instance = 0;



bool PAFRESTLogger::isServerAvailable(){
  
    TString hostAddress = this->properties["logger.host"];
    TString protocol = this->properties["logger.protocol"];
    Int_t port = this->properties["logger.port"].Atoi();
  
   
      TSocket sock(hostAddress.Data(), port);
      TString message;

      
      bool availabe = sock.IsValid();
      
      
      sock.Close();
      
      std::cout << "The server is there? " << availabe << std::endl;
      return availabe;
      
}

void PAFRESTLogger::GetNewLogId()
{
  
    
    Bool_t isLoggerEnabled = this->properties["logger.enabled"].EqualTo("true");
    TString hostAddress = this->properties["logger.host"];
    TString protocol = this->properties["logger.protocol"];
    Int_t port = this->properties["logger.port"].Atoi();
  
    if(isLoggerEnabled && isServerAvailable()){
      TSocket sock(hostAddress.Data(), port);
      TString message;

      TString data = "";

      std::cout << data.Data() << std::endl;
      

	message.Append(TString::Format("POST %s://%s:%d/execution HTTP/1.1\r\n", protocol.Data(),hostAddress.Data(), port ));
	message.Append("Transfer-Encoding: chunked\r\n");
	message.Append("Accept: */*\r\n");
	message.Append("Content-Type: application/json; charset=UTF-8\r\n");
	message.Append(TString::Format("Content-Length: %d\r\n", data.Length()));
	message.Append("\n");

	message.Append(data.Data());

	sock.SendRaw(message.Data(), message.Length());

	char recvBuff;
	TString response = "";
	while (sock.RecvRaw(&recvBuff, 1)) {
	    response.Append(recvBuff);
	}
	
	TObjArray *tx = response.Tokenize("\r\n");

	sock.Close();
	    
	this->logId = ((TObjString *) tx->At(tx->GetEntries() - 1))->String();  
      
    }
}


PAFRESTLogger::PAFRESTLogger() {
    LoadConfiguration();
    GetNewLogId();
    this->isServerReachable = true;
}

PAFRESTLogger *PAFRESTLogger::GetInstance() {
    if (!instance) {
        instance = new PAFRESTLogger;
    }
    return instance;
}

void PAFRESTLogger::Log(const char *module, const char *msg) {
    Log(INFO, module, msg);
}

void PAFRESTLogger::Log(PAFLogLevel level, const char *type, const char *data) {
  
    
    Bool_t isLoggerEnabled = this->properties["logger.enabled"].EqualTo("true");
    TString hostAddress = this->properties["logger.host"];
    TString protocol = this->properties["logger.protocol"];
    Int_t port = this->properties["logger.port"].Atoi();
    
  
    if(isLoggerEnabled && isServerAvailable())
    {
      
      std::cout << this->isServerReachable << std::endl;
      TSocket sock(hostAddress.Data(), port);
      TString message;
      

      TString payload{TString::Format("{\"level\":\"%s\" , \"type\":\"%s\", \"data\" : \"%s\"}\r\n", PAFLogLevelStrings[level], type, data)};

      if (!sock.IsValid()){
	sock.Close();
	return;
      };

      message.Append(TString::Format("PUT %s://%s:%d/execution/%s HTTP/1.1\r\n",protocol.Data(),hostAddress.Data(), port ,this->logId.Data()));
      message.Append("Transfer-Encoding: chunked\r\n");
      message.Append("Accept: */*\r\n");
      message.Append("Content-Type: application/json; charset=UTF-8\r\n");
      message.Append(TString::Format("Content-Length: %d\r\n", payload.Length()));
      message.Append("\n");

      message.Append(payload.Data());

      sock.SendRaw(message.Data(), message.Length());

      // Socket close
      sock.Close();
    }
}

void PAFRESTLogger::Flush() {

}

void PAFRESTLogger::LoadConfiguration() {

    std::ifstream infile("../etc/logger.conf");
    std::string line;

    
    int numberOfLines = 0;
    
    while (std::getline(infile, line))
    {
        TString value = line;
	TObjArray* parsedValues = value.Tokenize("=");
	numberOfLines++;
	
	
	if(parsedValues->GetEntries() != 2)
	{
	    PAFLogger::GetInstance()->Log(WARN, "PAF REST LOGGER",TString::Format("Invalid configuration on line %d : %s", numberOfLines, value.Data()).Data());

	}else
	{
	  TString key =  ((TObjString*)parsedValues->At(0))->GetString();
	  TString val =  ((TObjString*)parsedValues->At(1))->GetString();
	  
	  properties[key] = val;

	}
    }
    
}

PAFRESTLogger::~PAFRESTLogger() {
    delete this->instance;
}




