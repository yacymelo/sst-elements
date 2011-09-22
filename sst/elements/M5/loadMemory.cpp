#include <loadMemory.h>

#include <mem/physical.hh>
#include <dummySystem.h>

#include <debug.h>
#include <process.h>

void loadMemory( string name, PhysicalMemory* memory, 
                                    const SST::Params& params )
{
    int num = 0;
    DBGC(1,"%s\n",name.c_str());
    while ( 1 ) {
        Addr start,end;
        std::stringstream numSS;
        std::string tmp;

        numSS << num; 

        tmp = numSS.str() + ".process.executable";

        std::string exe = params.find_string( tmp );
        if ( exe.size() == 0 ) {
            break;
        }
        DBGC(1,"%s%s %s\n",name.c_str(), tmp.c_str(), exe.c_str() );

        tmp = numSS.str() + ".physicalMemory.start";
        start = params.find_integer( tmp );
        DBGC(1,"%s%s %#lx\n", name.c_str(), tmp.c_str(), start);

        tmp = numSS.str() + ".physicalMemory.end";
        end = params.find_integer( tmp, 0 );
        DBGC(1,"%s%s %#lx\n", name.c_str(), tmp.c_str(), end);

        tmp = name + numSS.str() + ".dummySystem";
        DummySystem* system = create_DummySystem( tmp, memory,
                                    Enums::timing, start, end);

        SST::Params mergedParams = mergeParams(  
                params.find_prefix_params( numSS.str() + ".process."),
                params.find_prefix_params( "process." ) );

        tmp = name + numSS.str();

        Process* process = newProcess( tmp, mergedParams, system );
        process->assignThreadContext(num);

        // NOTE: system and process are not needed after
        // startup, how do we free them? 

        ++num;
    }
}
