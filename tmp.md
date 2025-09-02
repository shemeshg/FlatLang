in main
```cpp
//flatLangConfig.semanticNodes.emplace_back(std::make_unique<LogicalGateAnd>("thisIsAnd", "true", "true"));
```

```cpp
//-only-file header
//-var {PRE} "LogicalGateAnd::"
class LogicalGateAnd : public SemanticNode
{
public:
    //- {function} 1 1
    explicit LogicalGateAnd(const std::string &tag,
                            const std::string &val1,
                            const std::string &val2
                            )
        //-only-file body
        : SemanticNode(tag, "bool" ), val1{val1}, val2{val2}
    {
    }

    //- {function} 1 3
    static const std::string getTemplateStr()
    //-only-file body
    {
        std::string str = R"(
        const {{var.datatype}} {{var.tag}} = {{var.val1}} == {{var.val2};
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
private:
    const std::string val1;
    const std::string val2;
};

//-only-file header
//-var {PRE} "LogicalGateOr::"
class LogicalGateOr : public SemanticNode
{
public:
    //- {function} 1 1
    explicit LogicalGateOr(const std::string &tag,
                           const std::string &val1,
                           const std::string &val2
                           )
        //-only-file body
        : SemanticNode(tag, "bool" ), val1{val1}, val2{val2}
    {
    }

    //- {function} 1 3
    static const std::string getTemplateStr()
    //-only-file body
    {
        std::string str = R"(
        const {{var.datatype}} {{var.tag}} = {{var.val1}} || {{var.val2};
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
private:
    const std::string val1;
    const std::string val2;
};

//-only-file header
//-var {PRE} "LogicalGateNand::"
class LogicalGateNand : public SemanticNode
{
public:
    //- {function} 1 1
    explicit LogicalGateNand(const std::string &tag,
                             const std::string &val1,
                             const std::string &val2
                             )
        //-only-file body
        : SemanticNode(tag, "bool" ), val1{val1}, val2{val2}
    {
    }

    //- {function} 1 3
    static const std::string getTemplateStr()
    //-only-file body
    {
        std::string str = R"(
        const {{var.datatype}} {{var.tag}} =   !({{var.val1}} && {{var.val2};
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
private:
    const std::string val1;
    const std::string val2;
};

//-only-file header
//-var {PRE} "LogicalGateXor::"
class LogicalGateXor : public SemanticNode
{
public:
    //- {function} 1 1
    explicit LogicalGateXor(const std::string &tag,
                            const std::string &val1,
                            const std::string &val2
                            )
        //-only-file body
        : SemanticNode(tag, "bool" ), val1{val1}, val2{val2}
    {
    }

    //- {function} 1 3
    static const std::string getTemplateStr()
    //-only-file body
    {
        std::string str = R"(
        const {{var.datatype}} {{var.tag}} =  ({{var.val1}} || {{var.val2}}) && !({{var.val1}} && {{var.val2}})  ;
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
private:
    const std::string val1;
    const std::string val2;
};

```