#include <Shader.h>
namespace gem {
struct Blending {public:
static void setBlending() { if(manager.getFileByName("Blending").processFile() && "set" == "set" ){ throw; } ;}
static void addBlending_Layout(int loc,std::string name) { if(manager.getFileByName("Fundamental/Layout").processFile(loc,name) && "set" == "add" ){ throw; } ;}
static void setBlending_VS_OUT(std::string name) { if(manager.getFileByName("VS_OUT").processFile(name) && "set" == "set" ){ throw; } ;}
protected:
inline static _gem::FileManager manager;
static _gem::File& getEntry() { return manager.getFileByName("Blending");}
};
struct TestEntry {public:
static void setTestEntry(std::string any) { if(manager.getFileByName("TestEntry").processFile(any) && "set" == "set" ){ throw; } ;}
static void setTestEntry_Test() { if(manager.getFileByName("Test").processFile() && "set" == "set" ){ throw; } ;}
static void setTestEntry_Layout(int loc,std::string name) { if(manager.getFileByName("Fundamental/Layout").processFile(loc,name) && "set" == "set" ){ throw; } ;}
protected:
inline static _gem::FileManager manager;
static _gem::File& getEntry() { return manager.getFileByName("TestEntry");}
};
};