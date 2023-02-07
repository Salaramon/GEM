#include <Shader.h>
namespace _gem {
};
namespace gem {
struct Blending {public:
static void addBlending_Layout(int loc,std::string name) { if(manager.getFileByName("Fundamental/Layout").processFile(loc,name) && "set" == "add" ){ throw; } ;}
static void setBlending_VS_OUT(std::string name) { if(manager.getFileByName("Other/VS_OUT").processFile(name) && "set" == "set" ){ throw; } ;}
protected:
static _gem::File& getEntry() { return manager.getFileByName("Blending");}
inline static constexpr const char source[] = "C:/Users/Salaramon/source/repos/GEM/x64/Debug/src/";
inline static constexpr const char entry[] = "C:/Users/Salaramon/source/repos/GEM/x64/Debug/src/";
inline static constexpr const char build[] = "C:/Users/Salaramon/source/repos/GEM/x64/Debug/build/";
inline static _gem::FileManager manager{source, entry};
};
struct TestEntry {public:
static void setTestEntry(std::string any) { if(manager.getFileByName("TestEntry").processFile(any) && "set" == "set" ){ throw; } ;}
static void setTestEntry_Layout(int loc,std::string name) { if(manager.getFileByName("Fundamental/Layout").processFile(loc,name) && "set" == "set" ){ throw; } ;}
protected:
static _gem::File& getEntry() { return manager.getFileByName("TestEntry");}
inline static constexpr const char source[] = "C:/Users/Salaramon/source/repos/GEM/x64/Debug/src/";
inline static constexpr const char entry[] = "C:/Users/Salaramon/source/repos/GEM/x64/Debug/src/";
inline static constexpr const char build[] = "C:/Users/Salaramon/source/repos/GEM/x64/Debug/build/";
inline static _gem::FileManager manager{source, entry};
};
};