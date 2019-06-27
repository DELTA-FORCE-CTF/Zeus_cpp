//
// Created by aurailus on 11/06/19.
//

#ifndef ZEUS_SMODULEUTILS_H
#define ZEUS_SMODULEUTILS_H

#include "../../def/ServerDefs.h"
#include "../../def/block/SelectionBox.h"
#include "../../def/block/server/ServerBlockDef.h"
#include "../../def/block/server/ServerBlockAtlas.h"
#include <sol.hpp>


class ModuleServerUtils {
public:
    ModuleServerUtils(sol::state& lua, sol::table& zeus, ServerDefs& defs) {
        //Dump function
        lua.script(R"(
            local function dump(tbl, indent)
                if not indent then indent = 0 end
                for k, v in pairs(tbl) do
                    if type(k) == "number" then
                        k = "[" .. k .. "]"
                    end
                    local indentString = string.rep("  ", indent)
                    local formatting = indentString .. k .. " = "
                    if type(v) == "table" then
                        print(formatting .. "{")
                        dump(v, indent+1)
                        print(indentString .. "}")
                    elseif type(v) == 'boolean' then
                        print(formatting .. tostring(v))
                    else
                        print(formatting .. v)
                    end
                end
            end

            zeus.dump = dump
        )");

        //Printe function
        lua.script(R"(
            function printe(str)
                print('\27[31m[!] ' .. str .. '\27[0m')
            end
        )");

        //Get path for mod
        zeus.set_function("get_path", [&](std::string modname) {
            try {
                if (modname.length() == 0) throw "No mod name specified!";
                return "/home/aurailus/CLion/Zeus/res/lua/" + modname + "/";
            }
            catch (const std::string& e) {
                std::cout << Log::err << "Exception on get_path: " << e << Log::endl;
            }
        });

        //Get if the interpreter is the server or the client
        zeus.set_function("is_server", []() {
            return true;
        });
    }
};

#endif //ZEUS_SMODULEUTILS_H
