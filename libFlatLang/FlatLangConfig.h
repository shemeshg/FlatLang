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
    const std::string getDataTypeStr() const;
};


class SemanticGroupItem{
    public:
    explicit SemanticGroupItem(ExternalHwBinding *ehb):ehb{ehb}{
        if (ehb->dataLen != 1){
            fromIdx = 0;
            toIdx = ehb->dataLen - 1;
        }
    }


    // Should only through setter and check bounds and all
    int fromIdx = 0;
    int toIdx = 0;

    private:
    ExternalHwBinding *ehb;
};

class SemanticGroup {
    public:
    std::vector<SemanticGroupItem> semanticGroups;
};

class FlatLangConfig
{
public:
    std::vector<ExternalHwBinding> externalHwBindings;


    std::string getConfig();
};