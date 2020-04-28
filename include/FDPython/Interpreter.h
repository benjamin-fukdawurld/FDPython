#ifndef INTERPRETER_H
#define INTERPRETER_H

#include <FDScript/BaseInterpreter.h>
#include <FDPython/Value.h>

namespace FDPython
{
    class Interpreter : public FDScript::BaseInterpreter
    {
        protected:
            std::unordered_map<std::string, Value> m_variables;

        public:
            Interpreter();
            ~Interpreter() override;

            void importModule(std::string_view name);

            void exec(const std::string_view &code, FDScript::BaseValue &locals) override;
            void execFile(const std::string_view &filePath, FDScript::BaseValue &locals) override;

            Value *getVariable(std::string_view name) override;
            void setVariable(std::string_view name, const FDScript::BaseValue &value) override;
            void unsetVariable(std::string_view name) override;
    };
}

#endif // INTERPRETER_H
