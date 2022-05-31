//request.h
#include <message.h>
//from __future__ import annotations
//from utilities import Utilities
//from typing import TYPE_CHECKING
//if TYPE_CHECKING:
    //from node import Node, PeerConnection
//TODO: node and peer connectio
class Request{
    public: 
    std::string type;
    bool debug;
    int flag;
    Node node;
    std::string data; 
    std::string timestamp;
    SignedMessage message;
    PeerConnection peer_connection;
    
    //------------------------------------------------------------------------------
    Request(Node node, SignedMessage message, PeerConnection peer_connection): 
        node(node), message(message), peer_connection(peer_connection)  {
        // --------------------------------------------------------------------------

        this->debug = 1;
        this->__request_selector();
        
    }


    // ------------------------------------------------------------------------------
    void __request_selector(){
        // --------------------------------------------------------------------------

        if (this->message.message.flag == 1){
            this->handle_known_peers_request();
        }
        if(this->message.message.flag == 2){
            this->handle_transaction_count_request();
        }
    }

    //# ------------------------------------------------------------------------------
    void handle_known_peers_request(){
        //# --------------------------------------------------------------------------
        
        //known_peers = Utilities.get_known_peers()
        //print('!{}'.format(self.peer_connection.s.getpeername()))
        //print(self.message.message.type)
        //print(self.message.message.flag)
        //self.peer_connection.send_data(
            //message_type='response', message_flag=self.message.message.flag, message_data=known_peers)
        //print('Known Peers Sent!')
        std::cout << "known peers not yet implemented";
    }

    // ------------------------------------------------------------------------------
    void handle_transaction_count_request(){
        // --------------------------------------------------------------------------

        //transaction_count = Utilities.get_transaction_count()

        //self.peer_connection.send_data(
            //message_type='response', message_flag=self.message.message.flag, message_data=transaction_count)
        //print('Transaction Count Sent!')
        std::cout << "transaction count not yet implemented";
    }
};


