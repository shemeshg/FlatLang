#include "FlatLangConfig.h"
#include <nlohmann/json.hpp>
#include <inja.hpp>

const std::string ExternalHwBinding::getDataTypeStr() const
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

std::string FlatLangConfig::getConfig()
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
    {% for var in params %}   
     {{ var.datatype }} {{ var.name }}{% if not loop.is_last %},{% endif %}    
    {% endfor %}
    ) {
        {% include "impl" %}
    }
    )";

    inja::Environment env;
    inja::Template implTemplate = env.parse("    // Implementation goes here \n" + semanticGroupsStr);
    env.include_template("impl", implTemplate);

    nlohmann::json data;
    data["params"] = externalParams;

    return env.render(t, data);
}