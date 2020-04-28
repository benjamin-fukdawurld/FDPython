#include <FDPython/Value.h>

FDPython::Value::Value() :
    FDScript::BaseValue(),
    m_obj(nullptr)
{}





FDPython::Value::~Value()
{
    if(m_obj)
        pybind11::handle(m_obj).dec_ref();
}

void FDPython::Value::setObject(pybind11::handle obj)
{
    if(m_obj)
        pybind11::handle(m_obj).dec_ref();

    m_obj = obj.ptr();
    obj.inc_ref();
}

FDPython::Value::operator bool() const
{
    return static_cast<bool>(m_obj);
}
