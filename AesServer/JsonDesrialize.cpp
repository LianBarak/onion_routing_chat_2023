#include "JsonDesrialize.h"

Request JsonDesrialize::Desrialize(const char* buffer)
{
    try {
        json j = json::parse(buffer);
        Request req;
    
        req.buffer = j["buffer"].get<std::string>().c_str();
        req.id = j["id"];
        return req;
    }
    catch (json::parse_error& ex)
    {
        std::cerr << "parse error at byte " << ex.byte << std::endl;
    }
}
