#pragma once

#include "SQLiteCpp/SQLiteCpp.h"

#ifdef _WIN32

#ifdef BROKER_EXPORT
#define BROKER_API extern "C" __declspec(dllexport)
#else
#define BROKER_API extern "C"  __declspec(dllimport)
#endif

#else
//NOT WINDOWS
#define BROKER_API 

#endif
class Broker
{
	SQLite::Database* db;

public:
	Broker(SQLite::Database* db) : db(db)
	{
	}

	SQLite::Database* get_db() const
	{
		return db;
	}

	~Broker()
	{
		delete db;
	}
};

typedef enum {
	OK,
	FAILED,
} BrokerResult;

struct MessageCollection
{
	MessageCollection() = default;
};

BROKER_API BrokerResult broker_initialize(Broker** broker);
BROKER_API BrokerResult broker_send(const Broker* broker, const char* queue, const char* payload);
BROKER_API BrokerResult broker_receive(const Broker* broker, MessageCollection** collection);
BROKER_API BrokerResult broker_ack(const Broker* broker, const char* id);
BROKER_API BrokerResult broker_nack(const Broker* broker, const char* id);
BROKER_API BrokerResult broker_destroy(const Broker* broker);

