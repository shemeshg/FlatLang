#include "FlatLangConfig.h"
#include <nlohmann/json.hpp>
#include <inja.hpp>

std::string FlatLangConfig::getConfig()    {
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
        inja::Template implTemplate = env.parse("    // Implementation goes here");
        env.include_template("impl", implTemplate);

        nlohmann::json data;
        data["params"] = externalParams;

        return env.render(t, data);
    }