#include <utils/Exceptions.hpp>

class WrongCommandException : public std::exception {
    public:
const char * what () {
        std::string msg("Wrong command format!");
        return msg.c_str();
    }
};

class InvalidActionInCurrentStateException : public std::exception {
    public:
const char * what () {
        std::string msg("This action is not permitted in this state!");
        return msg.c_str();
    }
};

class WrongPlayerNumberException : public std::exception {
    public:
const char * what () {
        std::string msg("This action requires all 4 players to be connected!");
        return msg.c_str();
    }
};