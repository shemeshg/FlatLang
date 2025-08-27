#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <FlatLangConfig.h>
namespace py = pybind11;
int add(int i, int j) {
    return i + j;
}

FlatLangConfig myTest(){
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

    return flatLangConfig;
}

PYBIND11_MODULE(flatLangPy, m, py::mod_gil_not_used()) {
    m.doc() = "pybind11 flatLangPy plugin"; // optional module docstring

    m.def("add", &add, "A function that adds two numbers");

    py::class_<FlatLangConfig>(m, "FlatLangConfig")
    .def(py::init<>())
    .def("getConfig", &FlatLangConfig::getConfig)
    .def_readwrite("externalHwBindings", &FlatLangConfig::externalHwBindings);


    py::class_<ExternalHwBinding>(m, "ExternalHwBinding")
    .def(py::init<>())
    .def_readwrite("tag", &ExternalHwBinding::tag)
    .def_readwrite("datatype", &ExternalHwBinding::datatype)
    .def_readwrite("dataLen", &ExternalHwBinding::dataLen)
    .def("__repr__",
        [](const ExternalHwBinding &ehb) {
            return "<ExternalHwBinding tag='" + ehb.tag +
                   "', datatype='" + ehb.datatype +
                   "', dataLen=" + std::to_string(ehb.dataLen) + ">";
        });


    m.def("myTest", &myTest, "Returns a FlatLangConfig object");

}



