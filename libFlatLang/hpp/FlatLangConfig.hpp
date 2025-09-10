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
    std::string tag;
};





//-only-file header
//-var {PRE} "SemanticNode::"
class SemanticNode
{
public:

    explicit SemanticNode(const std::string &tag,
                          const std::string &datatype) : tag{tag}, datatype{datatype} {}

    const std::string tag;
    const std::string datatype;
    virtual ~SemanticNode() = default;

    //- {function} 0 2
    const std::string getRenderedStr()
    //-only-file body
    {
        inja::Environment env;
        return env.render(env.parse(getTemplateStr()), getTemplateObj());
    }

    //-only-file header
private:
    virtual const nlohmann::json getTemplateObj() const = 0;
    virtual const std::string getTemplateStr() const = 0;
};

//-only-file header

class Tag {
public:
    explicit Tag(const std::string &tag):tag{tag}{}
    const std::string tag;
};

class TagOut: public Tag {
public:
    explicit TagOut(const std::string &tag):Tag(tag){}
};

class TagIn: public Tag {
public:
    explicit TagIn(const std::string &tag):Tag(tag){}
};

//-only-file header
//-var {PRE} "LogicalGateAnd::"
class LogicalGateAnd : public SemanticNode
{
public:
    //- {function} 1 1
    explicit LogicalGateAnd(const TagOut &result,
                            const TagIn &val1,
                            const TagIn &val2)
        //-only-file body
        : SemanticNode(result.tag, "bool"), val1{val1.tag}, val2{val2.tag}
    {
    }

    //-only-file header
private:
    const std::string val1;
    const std::string val2;

    //- {function} 0 2
    const std::string getTemplateStr() const override
    //-only-file body
    {
        std::string str = R"(
        {{tag}} = {{val1}} == {{val2}};
         )";

        return str;
    }

    //- {function} 0 2
    const nlohmann::json getTemplateObj() const override
    //-only-file body
    {
        nlohmann::json json = nlohmann::json::object({});
        json["datatype"] = datatype;
        json["tag"] = tag;
        json["val1"] = val1;
        json["val2"] = val2;
        return json;
    }
    //-only-file header
};

//-only-file header
//-var {PRE} "FixedValue::"
class FixedValue : public SemanticNode
{
public:
    //- {function} 1 1
    explicit FixedValue(const std::string &tag,
                        const std::string &datatype,
                        const std::string &val)
        //-only-file body
        : SemanticNode(tag, datatype), val{val}
    {
    }

    //-only-file header
private:
    const std::string val;

    //- {function} 0 2
    const std::string getTemplateStr() const override
    //-only-file body
    {
        std::string str = R"( 
        const {{datatype}} {{tag}} = {{val}};
         )";

        return str;
    }

    //- {function} 0 2
    const nlohmann::json getTemplateObj() const override
    //-only-file body
    {
        nlohmann::json json = nlohmann::json::object({});
        json["datatype"] = datatype;
        json["tag"] = tag;
        json["val"] = val;
        return json;
    }
    //-only-file header
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
    const nlohmann::json getTemplateObj() const
    //-only-file body
    {
        nlohmann::json declarationJson = nlohmann::json::object({});
        declarationJson["isConst"] = isConst;
        declarationJson["datatype"] = datatype;
        declarationJson["dataLen"] = dataLen;
        declarationJson["tag"] = tag;

        return declarationJson;
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
        if (dataLen > 1)
        {
            for (auto i : std::views::iota(0, dataLen))
            {
                ExternalHwBindingItem a;
                a.tag = tag + "[" + std::to_string(i) + "]";
                v.emplace_back(a);
            }
        }
        else
        {
            ExternalHwBindingItem a;
            a.tag = tag;
            v.emplace_back(a);
        }

        return v;
    }

    //-only-file header
};

//-only-file header
class ExternalHwBindingIn: public ExternalHwBinding {
public:
    explicit ExternalHwBindingIn(std::string tag, std::string datatype, int dataLen, bool isConst):
    ExternalHwBinding(tag, datatype,  dataLen,  isConst){
    }

    TagIn getTagAt(int idx){
        return TagIn( signalPorts.at(0).tag );
    }

};

class ExternalHwBindingOut: public ExternalHwBinding {
public:
    explicit ExternalHwBindingOut(std::string tag, std::string datatype, int dataLen, bool isConst):
        ExternalHwBinding(tag, datatype,  dataLen,  isConst){
    }

    TagOut getTagAt(int idx){
        return TagOut( signalPorts.at(0).tag );
    }
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
    std::string tagAt(int position)
    //-only-file body
    {
        int semanticGroupIdx = 0;
        for (const auto &row : semanticGroups)
        {
            for (int i = row.fromIdx; i <= row.toIdx; i++)
            {
                if (position == semanticGroupIdx)
                {
                    return row.ehb->signalPorts.at(i).tag;
                }
                semanticGroupIdx++;
            }
        }
        std::runtime_error("Not found in semanticGroupIdx");
        return "";
    }

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
    const nlohmann::json getTemplateObj() const
    //-only-file body
    {
        nlohmann::json declarationJson = nlohmann::json::object({});

        declarationJson["datatype"] = datatype;
        declarationJson["tag"] = tag;
        declarationJson["isConst"] = isConst;
        declarationJson["items"] = nlohmann::json::array({});

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
        return declarationJson;
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
    std::vector<SemanticNode *> semanticNodes;

    //- {fn}
    std::string getConfig()
    //-only-file body
    {
        nlohmann::json data;

        data["semanticNodes"] = nlohmann::json::array({});
        for (auto const &row : semanticNodes)
        {
            data["semanticNodes"].push_back(row->getRenderedStr());
        }

        data["semanticGroups"] = nlohmann::json::array({});
        for (auto const &row : semanticGroups)
        {
            data["semanticGroups"].push_back(row.getTemplateObj());
        }

        data["externalParams"] = nlohmann::json::array({});
        for (auto const &row : externalHwBindings)
        {
            data["externalParams"].push_back(row.getTemplateObj());
        }

        std::string configTemplate = R"(
    #include <span>

    void myRealTimeLoop({%- for var in externalParams -%} 
      {%- if var.dataLen == 1 -%}
      {%- if var.isConst -%}const {%- endif -%} {{ var.datatype }} &{%- else -%}
      std::span<{%- if var.isConst %}const {% endif -%} {{ var.datatype }},{{ var.dataLen }}> 
      {%- endif -%}      
      {{ var.tag }}{%- if not loop.is_last -%},{%-endif %}    
    {%- endfor -%}
    ) {
        {%- for var in semanticGroups -%}  
        {%- include "semanticGroupsTemplate" -%}
        {%- endfor -%}
        {%- for var in semanticNodes -%}
        {{var}}
        {%- endfor -%}

    }   
    )";

        std::string semanticGroupTemplate = R"(
std::vector<std::reference_wrapper<{% if var.isConst %}const {% endif %} {{var.datatype}}>> _{{var.tag}}{};
 {%- for item in var.items -%} 
_{{var.tag}}.push_back(std::ref( {% if item.isUnary %}  {{ item.tag}}  {% else %} {{ item.tag}} [ {{item.index}}] {% endif %}  ));
 {%- endfor -%}
 const std::vector<std::reference_wrapper<{% if var.isConst %}const {% endif %} {{var.datatype}}>> {{var.tag}} = std::move(_{{var.tag}});
)";

        inja::Environment env;

        inja::Template semanticGroupsTemplate = env.parse(semanticGroupTemplate);
        env.include_template("semanticGroupsTemplate", semanticGroupsTemplate);

        return env.render(configTemplate, data);
    }
    //-only-file header
};
