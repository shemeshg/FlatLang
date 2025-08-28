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
    bool isUnary()
    {
        return dataLen == 1;
    }
};

class SemanticGroupItem
{
public:
    explicit SemanticGroupItem(ExternalHwBinding *ehb) : ehb{ehb}
    {
        if (ehb->dataLen != 1)
        {
            fromIdx = 0;
            toIdx = ehb->dataLen - 1;
        }
    }

    // Should only through setter and check bounds and all
    int fromIdx = 0;
    int toIdx = 0;

    ExternalHwBinding *ehb;
};

class SemanticGroup
{
public:
    std::vector<SemanticGroupItem> semanticGroups;
    std::string tag = ".";
    std::string datatype = "int";
    bool isConst = true;

    const std::string getSemanticGroupsStr() const
    {
        std::string _ret;
        int dataLen = 0;
        std::string constStr = "";
        if (isConst)
        {
            constStr = "const ";
        }
        std::string declaration = std::format("std::vector<std::reference_wrapper<{}{}>> _{};", constStr, datatype, tag);
        _ret += declaration + "\n";
        for (const auto &row : semanticGroups)
        {

            for (int i = row.fromIdx; i <= row.toIdx; i++)
            {
                std::string itemRefString = std::format("{}[{}]", row.ehb->tag, i);
                if (row.ehb->isUnary())
                {
                    itemRefString = row.ehb->tag;
                }
                std::string rowPushback = std::format("_{}.push_back(std::ref({}));", tag, itemRefString);
                _ret += rowPushback + "\n";
            }
            dataLen = dataLen + row.ehb->dataLen;
        }

        std::string declarationEnd = std::format("const std::vector<std::reference_wrapper<{}{}>> {} = std::move(_{});",
                                                 constStr, datatype, tag, tag);
        _ret += declarationEnd + "\n";

        return _ret;
    }


};

class FlatLangConfig
{
public:
    std::vector<ExternalHwBinding> externalHwBindings;
    std::vector<SemanticGroup> semanticGroups;
    std::string getConfig();
};