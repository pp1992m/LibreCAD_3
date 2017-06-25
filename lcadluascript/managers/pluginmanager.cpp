#include "pluginmanager.h"
#include "lclua.h"
#include <dirent.h>

lc::PluginManager::PluginManager(const char* interface) :
    _interface(interface) {

}

void lc::PluginManager::loadPlugins(FILE* (*f_openFileDialog)(bool, const char*, const char*)) {
    const char* path = "../lcUILua/plugins/"; //TODO: get path

    DIR* dir;
    struct dirent* ent;

    if((dir = opendir(path)) != NULL) {
        while((ent = readdir(dir)) != NULL) {
            if(strcmp(ent->d_name, ".") == 0 || strcmp(ent->d_name, "..") == 0) {
                continue;
            }

            loadPlugin((std::string(path) + ent->d_name + "/plugin.lua").c_str(), f_openFileDialog);
        }
        closedir(dir);
    }
    else {
        perror("Error opening dir");
    }
}

void lc::PluginManager::loadPlugin(const char* file, FILE* (*f_openFileDialog)(bool, const char*, const char*)) {
    auto state = LuaIntf::LuaState::newState();
    auto lcLua = LCLua(state);
    lcLua.setF_openFileDialog(f_openFileDialog);
    lcLua.addLuaLibs();
    lcLua.importLCKernel();

    LuaIntf::Lua::setGlobal(state, "LC_interface", _interface);

    int s = state.doFile(file);

    if (s != 0) {
        std::cout << lua_tostring(state, -1) << std::endl;
        lua_pop(state, 1);
    }
}