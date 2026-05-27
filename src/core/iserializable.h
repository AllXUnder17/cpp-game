#ifndef _ISERIALIZABLE_
#define _ISERIALIZABLE_

#include <fstream>  // IWYU pragma: keep

class ISerializable {
public:
    ~ISerializable() = default;

    virtual void Serialize(std::ofstream& ofs) = 0;
    virtual void Deserialize(std::ifstream& ifs) = 0;
};

#endif