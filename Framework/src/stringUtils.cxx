// Copyright 2019-2020 CERN and copyright holders of ALICE O2.
// See https://alice-o2.web.cern.ch/copyright for details of the copyright holders.
// All rights not expressly granted are reserved.
//
// This software is distributed under the terms of the GNU General Public
// License v3 (GPL Version 3), copied verbatim in the file "COPYING".
//
// In applying this license CERN does not waive the privileges and immunities
// granted to it by virtue of its status as an Intergovernmental Organization
// or submit itself to any jurisdiction.

///
/// \file   stringUtils.cxx
/// \author Barthelemy von Haller
///

#include "QualityControl/stringUtils.h"

#include "QualityControl/CustomParameters.h"
#include <Common/Exceptions.h>
#include <bitset>
#include <iomanip>
#include <sstream>
#include <fmt/core.h>

namespace o2::quality_control::core
{

std::vector<std::string> getBinRepresentation(unsigned char* data, size_t size)
{
  std::stringstream ss;
  std::vector<std::string> result;
  result.reserve(size);

  for (size_t i = 0; i < size; i++) {
    std::bitset<16> x(data[i]);
    ss << x << " ";
    result.push_back(ss.str());
    ss.str(std::string());
  }
  return result;
}

std::vector<std::string> getHexRepresentation(unsigned char* data, size_t size)
{
  std::stringstream ss;
  std::vector<std::string> result;
  result.reserve(size);
  ss << std::hex << std::setfill('0');

  for (size_t i = 0; i < size; i++) {
    ss << std::setw(2) << static_cast<unsigned>(data[i]) << " ";
    result.push_back(ss.str());
    ss.str(std::string());
  }
  return result;
}

/// \brief Decode key of a configurable parameter as boolean
/// \param value Value to be decoded (true or false, case-insensitive)
/// \return Boolean representation of the value
/// \throw std::runtime_error in case value is not a boolean value
bool decodeBool(const std::string& value)
{
  if (value == "true" || value == "True" || value == "TRUE" || value == "1") {
    return true;
  }
  if (value == "false" || value == "False" || value == "FALSE" || value == "0") {
    return false;
  }
  throw std::runtime_error(fmt::format("Value {} not a boolean", value.data()));
}

bool parseBoolParam(const CustomParameters& customParameters, const std::string& name, const std::string& runType, const std::string& beamType)
{
  try {
    return decodeBool(customParameters.at(name, runType, beamType));
  } catch (std::out_of_range& exception) {
    BOOST_THROW_EXCEPTION(AliceO2::Common::ObjectNotFoundError() << AliceO2::Common::errinfo_object_name(runType + "/" + beamType + "/" + name));
  }
}

bool isUnsignedInteger(const std::string& s)
{
  return !s.empty() && std::find_if(s.begin(),
                                    s.end(), [](unsigned char c) { return !std::isdigit(c); }) == s.end();
}

} // namespace o2::quality_control::core