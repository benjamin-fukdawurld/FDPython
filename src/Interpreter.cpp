#include <FDPython/Interpreter.h>

#include <pybind11/embed.h>

FDPython::Interpreter::Interpreter()
{
    pybind11::initialize_interpreter();
}

FDPython::Interpreter::~Interpreter()
{
    m_variables.clear();
    pybind11::finalize_interpreter();
}

void FDPython::Interpreter::importModule(std::string_view name)
{
    pybind11::module m = pybind11::module::import(name.data());
    m_variables[name.data()] = m;
    pybind11::globals()[name.data()] = m;
}

void FDPython::Interpreter::exec(const std::string_view &code, FDScript::BaseValue &locals)
{
    pybind11::exec(code.data(), pybind11::globals(), static_cast<FDPython::Value&>(locals).getObject());
}

void FDPython::Interpreter::execFile(const std::string_view &filePath, FDScript::BaseValue &locals)
{
    pybind11::eval_file(filePath.data(), pybind11::globals(), static_cast<FDPython::Value&>(locals).getObject());
}

FDPython::Value *FDPython::Interpreter::getVariable(std::string_view name)
{
    auto it = m_variables.find(name.data());
    if(it == m_variables.end())
        return nullptr;

    return &(it->second);
}

void FDPython::Interpreter::setVariable(std::string_view name, const FDScript::BaseValue &value)
{
    m_variables[name.data()] = static_cast<const Value&>(value).getObject();
}

void FDPython::Interpreter::unsetVariable(std::string_view name)
{
    m_variables.erase(name.data());
}
