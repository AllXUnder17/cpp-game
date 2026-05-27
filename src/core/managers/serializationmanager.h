#ifndef _SERIALIZATION_MANAGER_
#define _SERIALIZATION_MANAGER_

#include <vector>

#include "core/iserializable.h"

class SerializationManager {
public:
    //===CONSTANTS===
    
    //===STATIC MEMBERS===
    
    //===CONSTRUCTORS===
    
    //===DESTRUCTOR===
    
    //===OPERATORS===
    
    //===GETTERS===
    
    //===SETTERS===
    
    //===MEMBER FUNCTIONS===
    static void AddSerializable(ISerializable* serializable);
    static void RemoveSerializable(ISerializable* serializable);

    static void SaveGame();
    static void LoadGame();

    static void SerializeObject(ISerializable* serializable);
    static void DeserializeObject(ISerializable* serializable);
private:
    SerializationManager() = delete;

    static std::string saveFileDir;

    static std::vector<ISerializable*> serializables;
};

#endif