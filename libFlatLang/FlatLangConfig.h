#include <iostream>
#include <format>
#include <ranges>
#include <sstream>
#include <numeric>
// using json = nlohmann::json;

class ExternalHwBindingItem
{
public:
    std::vector<std::string> aliases{};
};

class ExternalHwBinding
{
public:
    explicit ExternalHwBinding(std::string tag, std::string datatype, int dataLen, bool isConst) : tag{tag}, datatype{datatype}, dataLen{dataLen}, isConst{isConst},
                                                                                                   signalPorts(populateSignalPorts(dataLen))
    {
    }
    std::string tag = ".";
    std::string datatype = "int";
    bool isConst = true;
    int dataLen = 1;
    const std::string getDataTypeStr() const;
    std::vector<ExternalHwBindingItem> signalPorts;
    void printAllAliases()
    {
        for (auto i : std::views::iota(0, dataLen))
        {
            if (signalPorts.at(i).aliases.size() > 0)
            {
                std::ostringstream oss;
                for (const auto &alias : signalPorts.at(i).aliases)
                {
                    oss << alias << " ";
                }
                std::string joinedAliases = oss.str();
                std::cout << tag << " " << i << " " << joinedAliases << std::endl;
            }
        }
    }

    bool isUnary()
    {
        return dataLen == 1;
    }

private:
    std::vector<ExternalHwBindingItem> populateSignalPorts(int _dataLen)
    {
        std::vector<ExternalHwBindingItem> v;
        for (auto i : std::views::iota(0, dataLen))
        {
            ExternalHwBindingItem a;
            v.emplace_back(a);
        }

        return v;
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

    void printAllAliases()
    {
        std::cout << "Itterate all semanticGroups for aliases" << std::endl;
        int semanticGroupIdx = 0;
        for (const auto &row : semanticGroups)
        {
            for (int i = row.fromIdx; i <= row.toIdx; i++)
            {
                semanticGroupIdx ++;
                if (row.ehb->signalPorts[i].aliases.size() > 0)
                {
                    std::ostringstream oss;
                    for (const auto &alias : row.ehb->signalPorts[i].aliases)
                    {
                        oss << alias << " ";
                    }
                    std::string joinedAliases = oss.str();
                    std::cout << "SemanticGroup portId " << semanticGroupIdx << " " << joinedAliases << std::endl;
                }
            }
        }
    }

    const int getDataLen() const
    {
        return std::accumulate(
            semanticGroups.begin(), semanticGroups.end(), 0,
            [](int sum, const SemanticGroupItem &row)
            {
                return sum + row.ehb->dataLen;
            });
    }

    const std::string getSemanticGroupsStr() const
    {
        std::string _ret;

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