#pragma once
#ifndef JSON_DESRIALIZE_H
#define JSON_DESRIALIZE_H
#include <nlohmann/json.hpp>
#include "mySqlConnector.h"

using namespace nlohmann;

struct Request {
	const char* buffer;
	int id;
};

class JsonDesrialize {
public:
	Request Desrialize(const char* buffer);
};
#endif