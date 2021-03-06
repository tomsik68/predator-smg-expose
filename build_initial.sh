#!/bin/bash
set -e

# this build script relies on availability of llvm-config binary in $PATH
llvm_config="$(which llvm-config)"

predator_git="https://github.com/versokova/predator"
predator_git_branch="master"

function clone_predator(){
  [ -d extern/ ] || mkdir extern/
  pushd extern/
  git clone "$predator_git"
  pushd predator/
  git checkout "$predator_git_branch"
  [ -d sl_build ] || ./switch-host-llvm.sh $($llvm_config --cmakedir)
  popd
  popd
}

function perform_build() {
  rm -rf build
  mkdir build
  pushd build
  cmake -DLLVM_DIR="$($llvm_config --cmakedir)" -DCMAKE_EXPORT_COMPILE_COMMANDS=ON ..
  make
  popd
}

################################################################################
##################### end of helper functions, start script   #####################
################################################################################

clone_predator
perform_build
echo -e "Initial build seems to be done. \nIf everything went ok, changing sources should now only require running 'make' from the build directory."
