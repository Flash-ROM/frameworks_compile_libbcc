/*
 * Copyright 2012, The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef BCC_EXECUTION_ENGINE_COMPILER_CONFIG_H
#define BCC_EXECUTION_ENGINE_COMPILER_CONFIG_H

#include <string>
#include <vector>

#include <llvm/ADT/Triple.h>
#include <llvm/Support/CodeGen.h>
#include <llvm/Target/TargetOptions.h>

namespace llvm {

class Target;

} // end namespace llvm

namespace bcc {

class CompilerConfig {
private:
  //===--------------------------------------------------------------------===//
  // Available Configurations
  //===--------------------------------------------------------------------===//
  std::string mTriple;

  // Optional. If given, the name of the target CPU to generate code for.
  std::string mCPU;

  llvm::TargetOptions mTargetOpts;

  llvm::CodeModel::Model mCodeModel;

  llvm::CodeGenOpt::Level mOptLevel;

  llvm::Reloc::Model mRelocModel;

  // The list of target specific features to enable or disable -- this should
  // be a list of strings starting with '+' (enable) or '-' (disable).
  std::string mFeatureString;

private:
  //===--------------------------------------------------------------------===//
  // These are generated by CompilerConfig during initialize().
  //===--------------------------------------------------------------------===//
  const llvm::Target *mTarget;
  bool initializeTarget();

  llvm::Triple::ArchType mArchType;
  void initializeArch();

public:
  //===--------------------------------------------------------------------===//
  // Getters
  //===--------------------------------------------------------------------===//
  inline const std::string &getTriple() const
  { return mTriple; }

  inline const std::string &getCPU() const
  { return mCPU; }
  inline void setCPU(const std::string &pCPU)
  { mCPU = pCPU; }

  inline const llvm::TargetOptions &getTargetOptions() const
  { return mTargetOpts; }
  inline llvm::TargetOptions &getTargetOptions()
  { return mTargetOpts; }

  inline llvm::CodeModel::Model getCodeModel() const
  { return mCodeModel; }
  inline void setCodeModel(llvm::CodeModel::Model pCodeMode)
  { mCodeModel = pCodeMode; }

  inline llvm::CodeGenOpt::Level getOptimizationLevel() const
  { return mOptLevel; }
  inline void setOptimizationLevel(llvm::CodeGenOpt::Level pOptLvl)
  { mOptLevel = pOptLvl; }

  inline llvm::Reloc::Model getRelocationModel() const
  { return mRelocModel; }
  inline void setRelocationModel(llvm::Reloc::Model pRelocModel)
  { mRelocModel = pRelocModel; }

  inline const llvm::Target *getTarget() const
  { return mTarget; }

  inline llvm::Triple::ArchType getArchType() const
  { return mArchType; }

  inline const std::string &getFeatureString() const
  { return mFeatureString; }
  void setFeatureString(const std::vector<std::string> &pAttrs);

public:
  CompilerConfig(const std::string &pTriple);

  virtual ~CompilerConfig() { }
};

} // end namespace bcc

#endif  // BCC_EXECUTION_ENGINE_COMPILER_CONFIG_H
