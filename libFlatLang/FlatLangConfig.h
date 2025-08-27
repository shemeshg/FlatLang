#include <iostream>
#include <format>

// using json = nlohmann::json;

class ExternalHwBinding
{
public:
    std::string tag = ".";
    std::string datatype = "int";
    bool isConst = true;
    int dataLen = 1;
    const std::string getDataTypeStr() const
    {
        std::string isConstStr;
        if (isConst)
        {
            isConstStr = "const";
        }
        if (dataLen == 1)
        {
            return isConstStr + " " + datatype + "&";
        }
        else
        {

            return std::format("std::span<{} {},{}>", isConstStr, datatype, dataLen);
        }
    }
};

class FlatLangConfig
{
public:
    std::vector<ExternalHwBinding> externalHwBindings;

    std::string getConfig();
};