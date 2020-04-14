#include "PredatorInterface.hpp"

#include <clplug.hh>
#include <llvm/IR/Module.h>
#include <llvm/IR/PassManager.h>

#if LLVM_VERSION_MAJOR > 3 ||                                                  \
    (LLVM_VERSION_MAJOR == 3 && LLVM_VERSION_MINOR >= 7)
#if LLVM_VERSION_MAJOR >= 7
#include "llvm/Transforms/Utils.h" // createLowerSwitchPass
#else
#include "llvm/Transforms/Scalar.h" // createLowerSwitchPass
#endif                              // LLVM >= 7
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"
#endif
#include "llvm/Transforms/Instrumentation.h" // createAddressSanitizerFunctionPass

namespace PredatorInterface {

AnalysisResults analyze(llvm::Module &module) {
    llvm::ModulePassManager mpm;
    mpm.addPass(std::move(CLPass{}));

    return {};
}

} // namespace PredatorInterface
