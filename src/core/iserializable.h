#ifndef _ISERIALIZABLE_
#define _ISERIALIZABLE_

#include <fstream>  // IWYU pragma: keep

#include "managers/serializationmanager.h"

class ISerializable {
public:
    ISerializable() {
        SerializationManager::AddSerializable(this);
    }

    virtual ~ISerializable() {
        SerializationManager::RemoveSerializable(this);
    }

    virtual void Serialize(std::ofstream& ofs) = 0;
    virtual void Deserialize(std::ifstream& ifs) = 0;
};

#endif