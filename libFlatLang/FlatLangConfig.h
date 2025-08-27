#include <iostream>
#include <format>




// using json = nlohmann::json;

class ExternalHwBinding
{
public:
    std::string tag = ".";
    std::string datatype = "int";
    int dataLen = 1;
    const std::string getDataTypeStr() const
    {
        if (dataLen == 1)
        {
            return datatype + "&";
        }
        else
        {
            return std::format("std::span<{},{}>", datatype, dataLen);
        }
    }
};

class FlatLangConfig
{
public:
    std::vector<ExternalHwBinding> externalHwBindings;

    std::string getConfig();

};