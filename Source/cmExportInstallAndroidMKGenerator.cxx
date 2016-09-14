/*============================================================================
  CMake - Cross Platform Makefile Generator
  Copyright 2000-2009 Kitware, Inc., Insight Software Consortium

  Distributed under the OSI-approved BSD License (the "License");
  see accompanying file Copyright.txt for details.

  This software is distributed WITHOUT ANY WARRANTY; without even the
  implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
  See the License for more information.
============================================================================*/
#include "cmExportInstallAndroidMKGenerator.h"

#include "cmAlgorithms.h"
#include "cmExportBuildAndroidMKGenerator.h"
#include "cmExportSet.h"
#include "cmExportSetMap.h"
#include "cmGeneratedFileStream.h"
#include "cmGeneratorTarget.h"
#include "cmGlobalGenerator.h"
#include "cmInstallExportGenerator.h"
#include "cmInstallTargetGenerator.h"
#include "cmLocalGenerator.h"
#include "cmTargetExport.h"

cmExportInstallAndroidMKGenerator::cmExportInstallAndroidMKGenerator(
  cmInstallExportGenerator* iegen)
  : cmExportInstallFileGenerator(iegen)
{
}

void cmExportInstallAndroidMKGenerator::GenerateImportHeaderCode(
  std::ostream& os, const std::string&)
{
  std::string installDir = this->IEGen->GetDestination();
  os << "LOCAL_PATH := $(call my-dir)\n";
  size_t numDotDot = cmSystemTools::CountChar(installDir.c_str(), '/');
  numDotDot += (installDir.size() > 0) ? 1 : 0;
  std::string path;
  for (size_t n = 0; n < numDotDot; n++) {
    path += "/..";
  }
  os << "_IMPORT_PREFIX := "
     << "$(LOCAL_PATH)" << path << "\n\n";
  for (std::vector<cmTargetExport*>::const_iterator tei =
         this->IEGen->GetExportSet()->GetTargetExports()->begin();
       tei != this->IEGen->GetExportSet()->GetTargetExports()->end(); ++tei) {
    // Collect import properties for this target.
    cmTargetExport const* te = *tei;
    if (te->Target->GetType() == cmState::INTERFACE_LIBRARY) {
      continue;
    }
    std::string dest;
    if (te->LibraryGenerator) {
      dest = te->LibraryGenerator->GetDestination("");
    }
    if (te->ArchiveGenerator) {
      dest = te->ArchiveGenerator->GetDestination("");
    }
    te->Target->Target->SetProperty("__dest", dest.c_str());
  }
}

void cmExportInstallAndroidMKGenerator::GenerateImportFooterCode(std::ostream&)
{
}

void cmExportInstallAndroidMKGenerator::GenerateImportTargetCode(
  std::ostream& os, const cmGeneratorTarget* target)
{
  std::string targetName = this->Namespace;
  targetName += target->GetExportName();
  os << "include $(CLEAR_VARS)\n";
  os << "LOCAL_MODULE := ";
  os << targetName << "\n";
  os << "LOCAL_SRC_FILES := $(_IMPORT_PREFIX)/";
  os << target->Target->GetProperty("__dest") << "/";
  std::string config = "";
  if (this->Configurations.size()) {
    config = this->Configurations[0];
  }
  os << target->GetFullName(config) << "\n";
}

void cmExportInstallAndroidMKGenerator::GenerateExpectedTargetsCode(
  std::ostream&, const std::string&)
{
}

void cmExportInstallAndroidMKGenerator::GenerateImportPropertyCode(
  std::ostream&, const std::string&, cmGeneratorTarget const*,
  ImportPropertyMap const&)
{
}

void cmExportInstallAndroidMKGenerator::GenerateMissingTargetsCheckCode(
  std::ostream&, const std::vector<std::string>&)
{
}

void cmExportInstallAndroidMKGenerator::GenerateInterfaceProperties(
  cmGeneratorTarget const* target, std::ostream& os,
  const ImportPropertyMap& properties)
{
  std::string config = "";
  if (this->Configurations.size()) {
    config = this->Configurations[0];
  }
  cmExportBuildAndroidMKGenerator::GenerateInterfaceProperties(
    target, os, properties, cmExportBuildAndroidMKGenerator::INSTALL, config);
}

void cmExportInstallAndroidMKGenerator::LoadConfigFiles(std::ostream&)
{
}

void cmExportInstallAndroidMKGenerator::GenerateImportPrefix(std::ostream&)
{
}

void cmExportInstallAndroidMKGenerator::GenerateRequiredCMakeVersion(
  std::ostream&, const char*)
{
}

void cmExportInstallAndroidMKGenerator::CleanupTemporaryVariables(
  std::ostream&)
{
}

void cmExportInstallAndroidMKGenerator::GenerateImportedFileCheckLoop(
  std::ostream&)
{
}

void cmExportInstallAndroidMKGenerator::GenerateImportedFileChecksCode(
  std::ostream&, cmGeneratorTarget*, ImportPropertyMap const&,
  const std::set<std::string>&)
{
}

bool cmExportInstallAndroidMKGenerator::GenerateImportFileConfig(
  const std::string&, std::vector<std::string>&)
{
  return true;
}