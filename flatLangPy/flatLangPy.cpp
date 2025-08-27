#include <pybind11/pybind11.h>
#include <FlatLangConfig.h>
namespace py = pybind11;
int add(int i, int j) {
    return i + j;
}

std::string myTest(){
    FlatLangConfig flatLangConfig;
    ExternalHwBinding ehb;
    ehb.tag = "gpio_in";
    ehb.datatype = "int";
    ehb.dataLen = 4;
    flatLangConfig.externalHwBindings.push_back(ehb);
    ehb.tag = "gpio_out";
    flatLangConfig.externalHwBindings.push_back(ehb);
    ehb.tag = "tick_counter";
    ehb.dataLen = 1;
    flatLangConfig.externalHwBindings.push_back(ehb);

    return flatLangConfig.getConfig();
}

PYBIND11_MODULE(flatLangPy, m, py::mod_gil_not_used()) {
    m.doc() = "pybind11 flatLangPy plugin"; // optional module docstring

    m.def("add", &add, "A function that adds two numbers");
    m.def("myTest", &myTest, "Test if it works");

}



