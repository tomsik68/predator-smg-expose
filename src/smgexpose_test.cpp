#include "PredatorInterface.hpp"

#include <clplug.hh>
#include <iostream>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IRReader/IRReader.h>
#include <llvm/Support/SourceMgr.h>

int main(int argc, char *argv[]) {
    using namespace std;
    using namespace smgexpose;
    using namespace llvm;

    if (argc != 2) {
        errs() << "Usage: " << argv[0] << " program.(bc|ll)" << '\n';
        return 1;
    }

    LLVMContext context;
    SMDiagnostic err;

    auto module = parseIRFile(argv[1], err, context);

    if (!module) {
        errs() << "Failed to load module\n";
        err.print(argv[1], errs());
        return 1;
    }

    PredatorInterface::analyze(*module);
    // TODO use the results somehow

    return 0;
}
