#include <Shader.h>
namespace gem {
struct Blending {public:
inline static _gem::FileManager manager;
static _gem::File& getEntry() { return manager.getFileByName("Blending");}
static void setBlending() { if(manager.getFileByName("Blending").processFile() && "set" == "set" ){ throw; } ;}
static void addBlending_Layout(int loc,std::string name) { if(manager.getFileByName("Fundamental/Layout").processFile(loc,name) && "set" == "add" ){ throw; } ;}
static void setBlending_VS_OUT(std::string name) { if(manager.getFileByName("VS_OUT").processFile(name) && "set" == "set" ){ throw; } ;}
};
};