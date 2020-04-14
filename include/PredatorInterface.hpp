#ifndef PREDATORINTERFACE_H
#define PREDATORINTERFACE_H

#include <llvm/IR/Module.h>

namespace PredatorInterface {

class AnalysisResults {};

AnalysisResults analyze(llvm::Module &module);

} // namespace PredatorInterface

#endif /* PREDATORINTERFACE_H */
