#include <iostream>
#include <assert.h>
#include <dlfcn.h>

bool process(std::string &lib, std::string &function)
{
    void *handle;
    void (*process)(void);
    char *error;

    handle = dlopen (lib.c_str(), RTLD_LAZY);

    if (!handle) {
        fputs (dlerror(), stderr);
        return false;
    }

    process = (void (*)(void)) dlsym(handle, function.c_str());
    if ((error = dlerror()) != nullptr)  {
        fputs(error, stderr);
        return false;
    }
    process();
    
    dlclose(handle);
    return true;
}

int main(int argc, char** argv)
{
	std::string lib("./Kazelib.so");
    std::string function("process");
	assert ( process(lib, function) );
}