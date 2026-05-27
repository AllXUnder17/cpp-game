#include "core/managers/serializationmanager.h"

#include <algorithm>

//===CONSTANTS===

//===STATIC MEMBERS===
std::string SerializationManager::saveFileDir = "assets/savefile.bin";

std::vector<ISerializable*> SerializationManager::serializables = std::vector<ISerializable*>();

//===CONSTRUCTORS===

//===DESTRUCTOR===

//===OPERATORS===

//===GETTERS===

//===SETTERS===

//===MEMBER FUNCTIONS===
void SerializationManager::AddSerializable(ISerializable* serializable) {
    serializables.push_back(serializable);
}
void SerializationManager::RemoveSerializable(ISerializable* serializable) {
    auto it = std::find(serializables.begin(), serializables.end(), serializable);

    if (it != serializables.end())
        serializables.erase(it);
}

void SerializationManager::SaveGame() {
    std::ofstream ofs = std::ofstream("../assets/savefile.bin", std::ios::out | std::ios::binary | std::ios::trunc);

    for (auto s : serializables) {
        s->Serialize(ofs);
    }
}

void SerializationManager::LoadGame() {
    std::ifstream ifs = std::ifstream("../assets/savefile.bin", std::ios::in | std::ios::binary);

    for (auto s : serializables) {
        s->Deserialize(ifs);
    }
}


void SerializationManager::SerializeObject(ISerializable* serializable) {
    std::ofstream ofs = std::ofstream("../assets/savefile.bin", std::ios::out | std::ios::binary | std::ios::trunc);

    serializable->Serialize(ofs);

    ofs.close();
}

void SerializationManager::DeserializeObject(ISerializable* serializable) {
    std::ifstream ifs = std::ifstream("../assets/savefile.bin", std::ios::in | std::ios::binary);

    serializable->Deserialize(ifs);

    ifs.close();
}