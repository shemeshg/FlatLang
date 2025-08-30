//-define-file body GenHpp/FlatLangConfig.cpp
//-define-file header GenHpp/FlatLangConfig.h

//-only-file header //-
#pragma once
#include <vector>
#include <string>

#include <nlohmann/json.hpp>
//-only-file body //-
#include <inja.hpp>

//- #include "FlatLangConfig.h"

//-only-file header
//-var {PRE} "ExternalHwBindingItem::"
class ExternalHwBindingItem
{
public:
    std::vector<std::string> aliases{};
};

//-only-file header
//-var {PRE} "ExternalHwBinding::"
class ExternalHwBinding
{
public:
    //- {function} 1 1
    explicit ExternalHwBinding(std::string tag, std::string datatype, int dataLen, bool isConst)
        //-only-file body
        : tag{tag}, datatype{datatype}, dataLen{dataLen}, isConst{isConst}, signalPorts(populateSignalPorts(dataLen))
    {
    }
    //-only-file header
    std::string tag = ".";
    std::string datatype = "int";
    bool isConst = true;
    int dataLen = 1;
    std::vector<ExternalHwBindingItem> signalPorts;

    //- {function} 0 2
    const std::string getDataTypeStr() const
    //-only-file body
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

    //- {fn}
    void printAllAliases()
    //-only-file body
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

    //- {fn}
    bool isUnary()
    //-only-file body
    {
        return dataLen == 1;
    }

    //-only-file header
private:
    //- {fn}
    std::vector<ExternalHwBindingItem> populateSignalPorts(int _dataLen)
    //-only-file body
    {
        std::vector<ExternalHwBindingItem> v;
        for (auto i : std::views::iota(0, dataLen))
        {
            ExternalHwBindingItem a;
            v.emplace_back(a);
        }

        return v;
    }

    //-only-file header
};

//-only-file header
//-var {PRE} "SemanticGroupItem::"
class SemanticGroupItem
{
public:
    //- {function} 1 1
    explicit SemanticGroupItem(ExternalHwBinding *ehb)
        //-only-file body
        : ehb{ehb}
    {
        if (ehb->dataLen != 1)
        {
            fromIdx = 0;
            toIdx = ehb->dataLen - 1;
        }
    }

    //-only-file header
    // Should only through setter and check bounds and all
    int fromIdx = 0;
    int toIdx = 0;

    ExternalHwBinding *ehb;
};

//-only-file header
//-var {PRE} "SemanticGroup::"
class SemanticGroup
{
public:
    std::vector<SemanticGroupItem> semanticGroups;
    std::string tag = ".";
    std::string datatype = "int";
    bool isConst = true;

    //- {fn}
    void printAllAliases()
    //-only-file body
    {
        std::cout << "Itterate all semanticGroups for aliases" << std::endl;
        int semanticGroupIdx = 0;
        for (const auto &row : semanticGroups)
        {
            for (int i = row.fromIdx; i <= row.toIdx; i++)
            {
                semanticGroupIdx++;
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

    //- {function} 0 2
    const int getDataLen() const
    //-only-file body
    {
        return std::accumulate(
            semanticGroups.begin(), semanticGroups.end(), 0,
            [](int sum, const SemanticGroupItem &row)
            {
                return sum + row.ehb->dataLen;
            });
    }

    //- {function} 0 2
    const std::string getSemanticGroupsStr() const
    //-only-file body
    {
        std::string _ret;

        std::string t = R"(
std::vector<std::reference_wrapper<{% if isConst %}const {% endif %} {{datatype}}>> _{{tag}}{};
 {%- for item in items -%} 
_{{tag}}.push_back(std::ref( {% if item.isUnary %}  {{ item.tag}}  {% else %} {{ item.tag}} [ {{item.index}}] {% endif %}  ));
 {%- endfor -%}
 const std::vector<std::reference_wrapper<{% if isConst %}const {% endif %} {{datatype}}>> {{tag}} = std::move(_{{tag}});
)";
        nlohmann::json declarationJson = nlohmann::json::object({});
        
        declarationJson["datatype"] = datatype;
        declarationJson["tag"] = tag;
        declarationJson["isConst"]  = isConst;
        declarationJson["items"] = nlohmann::json::array({});
        inja::Environment env;
        

        for (const auto &row : semanticGroups)
        {

            for (int i = row.fromIdx; i <= row.toIdx; i++)
            {
                nlohmann::json item = nlohmann::json::object({});
                item["tag"] = row.ehb->tag;
                item["index"] = i;
                item["isUnary"] = row.ehb->isUnary();
                declarationJson["items"].push_back(item);
            }
        }



        return  env.render(t, declarationJson);
    }

    //-only-file header
};

//-only-file header
//-var {PRE} "FlatLangConfig::"
class FlatLangConfig
{
public:
    std::vector<ExternalHwBinding> externalHwBindings;
    std::vector<SemanticGroup> semanticGroups;

    //- {fn}
    std::string getConfig()
    //-only-file body
    {
        std::string semanticGroupsStr;
        for (auto const &row : semanticGroups)
        {
            semanticGroupsStr += row.getSemanticGroupsStr();
        }

        nlohmann::json externalParams = nlohmann::json::array({});

        for (auto const &row : externalHwBindings)
        {
            externalParams.push_back({{"name", row.tag},
                                      {"datatype", row.getDataTypeStr()}});
        }

        std::string t = R"(
    #include <span>

    void myRealTimeLoop(
    {%- for var in params -%}   
     {{ var.datatype }} {{ var.name }}{% if not loop.is_last %},{% endif %}    
    {%- endfor -%}
    ) {
        {%- include "impl" -%}
    }
    )";

        inja::Environment env;
        inja::Template implTemplate = env.parse("    // Implementation goes here \n" + semanticGroupsStr);
        env.include_template("impl", implTemplate);

        nlohmann::json data;
        data["params"] = externalParams;

        return env.render(t, data);
    }
    //-only-file header
};