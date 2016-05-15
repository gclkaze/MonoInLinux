#include "Kazelib.h"
#include <mono/jit/jit.h>
#include <mono/metadata/assembly.h>
#include <assert.h>
#include <mono/metadata/debug-helpers.h>

static void processThroughMono(std::string& dll)
{    
    //Initialize mono runtime
    MonoDomain* domain = mono_jit_init (dll.c_str());
    MonoAssembly *assembly;

    assembly = mono_domain_assembly_open (domain, dll.c_str());
    assert(assembly);

    MonoImage *image =  mono_assembly_get_image  (assembly);
    assert(image);
    MonoMethodDesc* desc = mono_method_desc_new ("TestDLL.Program:process", true);
    assert(desc);

    MonoMethod* method = mono_method_desc_search_in_image (desc, image);
    assert(method);

    //Create our container
    Container* c = new Container();

    //Cast to uint64
    uint64_t ptr = reinterpret_cast<uint64_t>(c);

    //Fill it as an argument before the mono method invokation
    void* args[1];
    args[0] = &ptr;

    //Invoke C# code
    mono_runtime_invoke (method, nullptr, args, nullptr);

    //Clean mono runtime
    mono_jit_cleanup (domain);

    //We did it!
    c->dump();

}

void process()
{
    std::cout << "process()!!" << std::endl;
    std::string dll("test.dll");
    processThroughMono(dll);
}

void storeResults(uint64_t container,int value)
{
	Container* c = reinterpret_cast<Container*>(container);
	c->storeValue(value);
}