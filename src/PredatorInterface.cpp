#include "PredatorInterface.hpp"

#include "llvm/Pass.h"

#include <cl/cl_msg.hh>
#include <cl/clutil.hh>
#include <cl/code_listener.h>
#include <cl/easy.hh>
#include <cl/memdebug.hh>
#include <cl/storage.hh>
#include <cl_private.hh>
#include <cl_storage.hh>
#include <clplug.hh>
#include <llvm/CodeGen/Passes.h>
#include <llvm/IR/LegacyPassManager.h>
#include <llvm/IR/Module.h>
#include <llvm/InitializePasses.h>
#include <llvm/PassSupport.h>
#include <llvm/Transforms/Instrumentation.h>
#include <llvm/Transforms/Scalar.h>
#include <llvm/Transforms/Utils.h>
#include <nestedgep.hh>
#include <passes.hh>
#include <symexec.hh>
#include <symstate.hh>
#include <symtrace.hh>

static SymStateWithJoin globResults;
static void execFnc(const CodeStorage::Fnc &fnc) {
    const CodeStorage::Storage &stor = *fnc.stor;
    const struct cl_loc *lw = locationOf(fnc);
    CL_DEBUG_MSG(lw,
                 "creating fresh initial state for " << nameOf(fnc) << "()...");

    // create the initial configuration
    Trace::RootNode *traceRoot = new Trace::RootNode(&fnc);
    SymHeap entry(stor, traceRoot);
#if SE_DISABLE_SYMCUT
    // we have to init gl variables now because they cannot be imported later on
    initGlVars(entry);
#endif

    // run the symbolic execution
    execute(globResults, entry, fnc);
}

static void launchSymExec(const CodeStorage::Storage &stor) {
    using namespace CodeStorage;

    // look for main() by name
    CL_DEBUG("looking for 'main()' at gl scope...");
    const NameDb::TNameMap &glNames = stor.fncNames.glNames;
    const NameDb::TNameMap::const_iterator iter = glNames.find("main");
    if (glNames.end() == iter) {
        CL_WARN("main() not found at global scope");
        // execVirtualRoots(stor);
        return;
    }

    // look for definition of main()
    const FncDb &fncs = stor.fncs;
    const Fnc *main = fncs[iter->second];
    if (!main || !isDefined(*main)) {
        CL_WARN("main() not defined");
        // execVirtualRoots(stor);
        return;
    }

    // just execute the main() function
    execFnc(*main);
    printMemUsage("execFnc");
}

// must be global, so CLPass can find it
void clEasyRun(const CodeStorage::Storage &storage, const char *config) {
    launchSymExec(storage);
}

namespace smgexpose {
namespace PredatorInterface {

using namespace llvm;

static void addRequirements(legacy::PassManager &pm) {
    pm.add(createGlobalVarsPass());
    pm.add(new NestedGepPass);
    pm.add(createAddressSanitizerFunctionPass(false, true, true));
    pm.add(createLowerSwitchPass());
    pm.add(createUnreachableBlockEliminationPass());
}

AnalysisResults analyze(Module &module) {
    legacy::PassManager pm;
    AnalysisResults results;

    addRequirements(pm);
    pm.add(new CLPass);
    errs() << "---- Predator output start ----\n";
    pm.run(module);
    errs() << "---- Predator output end ----\n";
    for (auto *state : globResults) {
    }

    return results;
}

} // namespace PredatorInterface
} // namespace smgexpose

