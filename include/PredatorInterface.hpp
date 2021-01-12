#pragma once

#include <llvm/IR/Module.h>

namespace smgexpose {
namespace PredatorInterface {

struct AnalysisProperties { /* TODO */
};

struct AnalysisResults {
    AnalysisProperties props;
    /* TODO */
};

/**
 */
AnalysisResults analyze(llvm::Module &module);

} // namespace PredatorInterface
} // namespace smgexpose

