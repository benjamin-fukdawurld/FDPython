#ifndef VALUE_H
#define VALUE_H

#include <FDScript/BaseValue.h>

#include<pybind11/embed.h>

namespace FDPython
{
    class Value : public FDScript::BaseValue
    {
        protected:
            PyObject *m_obj;

        public:
            Value();
            Value(pybind11::handle obj):
                m_obj(obj.ptr())
            {
                obj.inc_ref();
            }

            Value(const Value &other):
                m_obj(other.m_obj)
            {
                if(m_obj)
                    pybind11::handle(m_obj).inc_ref();
            }

            Value(Value &&other):
                m_obj(other.m_obj)
            {
                other.m_obj = nullptr;
            }

            ~Value() override;

            Value &operator=(const Value &other)
            {
                setObject(pybind11::handle(other.m_obj));
                return *this;
            }

            Value operator=(Value &&other)
            {
                m_obj = other.m_obj;
                other.m_obj = nullptr;
                return *this;
            }

            operator bool() const override;

            template<typename T = pybind11::object>
            T getObject() { return pybind11::reinterpret_borrow<T>(m_obj); }

            template<typename T = pybind11::object>
            const T getObject() const { return pybind11::reinterpret_borrow<T>(m_obj); }

            void setObject(pybind11::handle obj);
    };
}

#endif // VALUE_H
