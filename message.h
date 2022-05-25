//message.cpp

//sys info
#include <ctime> // double check this
#include <chrono>
#include <thread>
//data types
#include <json.hpp> // check out jsonCPP and the nlohmann json 
#include <typeinfo>
#include <iostream>
#include <string>
//crypto
#include <openssl/sha.h>
#include <openssl/evp.h>


//TODO: check if everything should be public because i think it is in python but

class Message{
    /*Unsigned transactions with information regarding a message's type, flag, data, and timestamp.*/
    public: 
        std::string type;
        bool debug;
        int flag;
        std::string data; 
        std::string timestamp;
        Message (){
                     //Initializes a message object, does *not* check if information is None

            this->debug = 0;

            this->type = "";
            this->flag = 0;
            this->data = "";
            //figure out a way to use clock online or something, uses local time 
            std::time_t t = std::chrono::_V2::system_clock::to_time_t(std::chrono::system_clock::now());
            this->timestamp = ctime(&t);
        }


        // ------------------------------------------------------------------------------
        Message (std::string type, int flag, std::string data) {
            // --------------------------------------------------------------------------
            //Initializes a message object, does *not* check if information is None

            this->debug = 1;

            this->type = type;
            this->flag = flag;
            this->data = data;
            //figure out a way to use clock online or something, uses local time 
            std::time_t t = std::chrono::_V2::system_clock::to_time_t(std::chrono::system_clock::now());
            this->timestamp = ctime(&t);
        }  

        // ------------------------------------------------------------------------------
        void __debug(std::string message){
            // --------------------------------------------------------------------------
            //Prints a message to the screen with the id of the current thread
            if (this->debug) {
                printf("[%s], %s",  std::this_thread::get_id(), message);
            }
        }

        // ------------------------------------------------------------------------------
        bool validate(){
            // --------------------------------------------------------------------------
            //Checks to see whether a message has a valid type, flag, data, and timestamp


            //probably doesn't matter if we check type if we default initialize tbh  
            bool is_valid_type = (typeid(this->type).name() == "string" && (this->type == 
                "response" || this->type == "request")) ? 1 : 0; 
            bool is_valid_flag = (typeid(this->flag).name() == "int" && (this->flag > 0 && this->flag < 100)) ? 1 : 0; 
            bool is_valid_data = typeid(this->data).name() == "string";
            bool is_valid_timestamp = typeid(this->timestamp).name() == "string";
                    
            if(!is_valid_type){
                __debug("Invalid message type, with type of: " + (std::string)typeid(this->type).name());
                return false;
            }

            if(!is_valid_flag){
                __debug("Invalid message type, with type of: " + (std::string)typeid(this->flag).name());
                return false;
            }

            if(!is_valid_data){
                __debug("Invalid message type, with type of: " + (std::string)typeid(this->data).name());
                return false;
            }
            
            if(!is_valid_flag){
                __debug("Invalid message timestamp, with type of: " + (std::string)typeid(this->timestamp).name());
                return false;
            }

            __debug("Message is valid!");
            return true;
        
        }

        // ------------------------------------------------------------------------------
        std::string to_JSON(){
            // --------------------------------------------------------------------------
            /*Returns a serialized version of a Message object. This can be used with
            any function/method in which an encoded message is to be sent.*/

            nlohmann::json j = nlohmann::json{{"type", this->type}, 
                                                {"debug", this->debug}, 
                                                {"flag", this->flag},
                                                {"data", this->data},
                                                {"timestamp", this->timestamp},
                                            };
            //TODO: ensure that this output matches the python output
            return j.nlohmann::json::dump(4);
            // json.dumps(self, default=lambda o: o.__dict__, sort_keys=True, indent=4)
        }

        //@classmethod
        //EQUIVILENT TO THE FROM_JSON FUNCTION
        // ------------------------------------------------------------------------------
        Message (std::string JSON){
            //# --------------------------------------------------------------------------
            /*Returns a Message object given a JSON input. If JSON is not formatted 
            correctly, this method will return None.*/
            auto data = nlohmann::json::parse(JSON);

            //this exists
            for (auto& it : data.items()){
                //todo: figure out a more efficient way of doing this
                if (it.key().compare("type")){
                    this->type = it.value();
                }//type

                //TODO: this shit is super wrong, have the else just in case
                else if (it.key().compare("debug")){
                    if (it.value() == "true"){
                        this->debug = 1;
                    }

                    else if (it.value() == "false"){
                        this->debug = 0;
                    }

                    else{
                        throw std::invalid_argument("programmer sucks at handling booleans in json");
                    }
                }//debug

                else if (it.key().compare("flag")){
                    this->flag = std::__cxx11::stoi(it.value());
                }//flag

                else if (it.key().compare("data")){
                    this->data = it.value();
                }//data
                
                else if (it.key().compare("timestamp")){
                    this->timestamp = it.value();
                }//timestamp
            }//for
        }
};


// **********************************************************

class SignedMessage{
    //TODO: check if the signature should be a string or what 

    //Manages any actions made with a signed message. Inherits attributes from the Message class.
    private:
        Message message; 
        std::string signature;
    public:
    
    //  ------------------------------------------------------------------------------
    SignedMessage(Message message, std::string signature){ 
        //  --------------------------------------------------------------------------
        // Initializes a the signature of a SignedMesage 

        this->message = message;
        this->signature = signature;
    }

    // ------------------------------------------------------------------------------
    void __debug(){
        // --------------------------------------------------------------------------
        if (this->message.debug){
            printf("[%s] %i",  std::this_thread::get_id(), message.debug);
        }
    }

    // ------------------------------------------------------------------------------
    bool is_signed(){
        // --------------------------------------------------------------------------
        //TODO: ask if we are doing actual signature verfication
        return this->signature != "";
    }

    // ------------------------------------------------------------------------------
    std::string to_JSON(){
        // --------------------------------------------------------------------------
        //Returns a serialized version of a SignedMessage object. This can be used
        //with any function/method in which an encoded message is to be sent.
        

            nlohmann::json j = nlohmann::json{{"type", this->message.type}, 
                                                {"debug", this->message.debug}, 
                                                {"flag", this->message.flag},
                                                {"data", this->message.data},
                                                {"timestamp", this->message.timestamp},
                                                {"signature", this->message.timestamp},
                                            }; //TODO: ensure that this output matches the python output, also we are
        return j.nlohmann::json::dump(4);
    }

    // ------------------------------------------------------------------------------
    SignedMessage(std::string JSON){
        //  --------------------------------------------------------------------------
        /*Returns a SignedMessage object given a JSON input. If JSON is not formatted 
        correctly, this method will return None.*/
        Message message(JSON);
        nlohmann::json j = nlohmann::json::parse(JSON);


        SignedMessage signed_message(message, j.at("signature"));        
    }
    
};