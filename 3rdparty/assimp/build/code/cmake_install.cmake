# Install script for directory: E:/Ralts/Amatsu/3rdparty/assimp/code

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Program Files (x86)/Assimp")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xlibassimp5.2.4-devx" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "E:/Ralts/Amatsu/3rdparty/assimp/build/lib/Debug/assimp-vc142-mtd.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "E:/Ralts/Amatsu/3rdparty/assimp/build/lib/Release/assimp-vc142-mt.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "E:/Ralts/Amatsu/3rdparty/assimp/build/lib/MinSizeRel/assimp-vc142-mt.lib")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY OPTIONAL FILES "E:/Ralts/Amatsu/3rdparty/assimp/build/lib/RelWithDebInfo/assimp-vc142-mt.lib")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xlibassimp5.2.4x" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "E:/Ralts/Amatsu/3rdparty/assimp/build/bin/Debug/assimp-vc142-mtd.dll")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ee][Aa][Ss][Ee])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "E:/Ralts/Amatsu/3rdparty/assimp/build/bin/Release/assimp-vc142-mt.dll")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Mm][Ii][Nn][Ss][Ii][Zz][Ee][Rr][Ee][Ll])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "E:/Ralts/Amatsu/3rdparty/assimp/build/bin/MinSizeRel/assimp-vc142-mt.dll")
  elseif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/bin" TYPE SHARED_LIBRARY FILES "E:/Ralts/Amatsu/3rdparty/assimp/build/bin/RelWithDebInfo/assimp-vc142-mt.dll")
  endif()
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xassimp-devx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/assimp" TYPE FILE FILES
    "E:/Ralts/Amatsu/3rdparty/assimp/code/../include/assimp/anim.h"
    "E:/Ralts/Amatsu/3rdparty/assimp/code/../include/assimp/aabb.h"
    "E:/Ralts/Amatsu/3rdparty/assimp/code/../include/assimp/ai_assert.h"
    "E:/Ralts/Amatsu/3rdparty/assimp/code/../include/assimp/camera.h"
    "E:/Ralts/Amatsu/3rdparty/assimp/code/../include/assimp/color4.h"
    "E:/Ralts/Amatsu/3rdparty/assimp/code/../include/assimp/color4.inl"
    "E:/Ralts/Amatsu/3rdparty/assimp/build/code/../include/assimp/config.h"
    "E:/Ralts/Amatsu/3rdparty/assimp/code/../include/assimp/ColladaMetaData.h"
    "E:/Ralts/Amatsu/3rdparty/assimp/code/../include/assimp/commonMetaData.h"
    "E:/Ralts/Amatsu/3rdparty/assimp/code/../include/assimp/defs.h"
    "E:/Ralts/Amatsu/3rdparty/assimp/code/../include/assimp/cfileio.h"
    "E:/Ralts/Amatsu/3rdparty/assimp/code/../include/assimp/light.h"
    "E:/Ralts/Amatsu/3rdparty/assimp/code/../include/assimp/material.h"
    "E:/Ralts/Amatsu/3rdparty/assimp/code/../include/assimp/material.inl"
    "E:/Ralts/Amatsu/3rdparty/assimp/code/../include/assimp/matrix3x3.h"
    "E:/Ralts/Amatsu/3rdparty/assimp/code/../include/assimp/matrix3x3.inl"
    "E:/Ralts/Amatsu/3rdparty/assimp/code/../include/assimp/matrix4x4.h"
    "E:/Ralts/Amatsu/3rdparty/assimp/code/../include/assimp/matrix4x4.inl"
    "E:/Ralts/Amatsu/3rdparty/assimp/code/../include/assimp/mesh.h"
    "E:/Ralts/Amatsu/3rdparty/assimp/code/../include/assimp/ObjMaterial.h"
    "E:/Ralts/Amatsu/3rdparty/assimp/code/../include/assimp/pbrmaterial.h"
    "E:/Ralts/Amatsu/3rdparty/assimp/code/../include/assimp/GltfMaterial.h"
    "E:/Ralts/Amatsu/3rdparty/assimp/code/../include/assimp/postprocess.h"
    "E:/Ralts/Amatsu/3rdparty/assimp/code/../include/assimp/quaternion.h"
    "E:/Ralts/Amatsu/3rdparty/assimp/code/../include/assimp/quaternion.inl"
    "E:/Ralts/Amatsu/3rdparty/assimp/code/../include/assimp/scene.h"
    "E:/Ralts/Amatsu/3rdparty/assimp/code/../include/assimp/metadata.h"
    "E:/Ralts/Amatsu/3rdparty/assimp/code/../include/assimp/texture.h"
    "E:/Ralts/Amatsu/3rdparty/assimp/code/../include/assimp/types.h"
    "E:/Ralts/Amatsu/3rdparty/assimp/code/../include/assimp/vector2.h"
    "E:/Ralts/Amatsu/3rdparty/assimp/code/../include/assimp/vector2.inl"
    "E:/Ralts/Amatsu/3rdparty/assimp/code/../include/assimp/vector3.h"
    "E:/Ralts/Amatsu/3rdparty/assimp/code/../include/assimp/vector3.inl"
    "E:/Ralts/Amatsu/3rdparty/assimp/code/../include/assimp/version.h"
    "E:/Ralts/Amatsu/3rdparty/assimp/code/../include/assimp/cimport.h"
    "E:/Ralts/Amatsu/3rdparty/assimp/code/../include/assimp/importerdesc.h"
    "E:/Ralts/Amatsu/3rdparty/assimp/code/../include/assimp/Importer.hpp"
    "E:/Ralts/Amatsu/3rdparty/assimp/code/../include/assimp/DefaultLogger.hpp"
    "E:/Ralts/Amatsu/3rdparty/assimp/code/../include/assimp/ProgressHandler.hpp"
    "E:/Ralts/Amatsu/3rdparty/assimp/code/../include/assimp/IOStream.hpp"
    "E:/Ralts/Amatsu/3rdparty/assimp/code/../include/assimp/IOSystem.hpp"
    "E:/Ralts/Amatsu/3rdparty/assimp/code/../include/assimp/Logger.hpp"
    "E:/Ralts/Amatsu/3rdparty/assimp/code/../include/assimp/LogStream.hpp"
    "E:/Ralts/Amatsu/3rdparty/assimp/code/../include/assimp/NullLogger.hpp"
    "E:/Ralts/Amatsu/3rdparty/assimp/code/../include/assimp/cexport.h"
    "E:/Ralts/Amatsu/3rdparty/assimp/code/../include/assimp/Exporter.hpp"
    "E:/Ralts/Amatsu/3rdparty/assimp/code/../include/assimp/DefaultIOStream.h"
    "E:/Ralts/Amatsu/3rdparty/assimp/code/../include/assimp/DefaultIOSystem.h"
    "E:/Ralts/Amatsu/3rdparty/assimp/code/../include/assimp/ZipArchiveIOSystem.h"
    "E:/Ralts/Amatsu/3rdparty/assimp/code/../include/assimp/SceneCombiner.h"
    "E:/Ralts/Amatsu/3rdparty/assimp/code/../include/assimp/fast_atof.h"
    "E:/Ralts/Amatsu/3rdparty/assimp/code/../include/assimp/qnan.h"
    "E:/Ralts/Amatsu/3rdparty/assimp/code/../include/assimp/BaseImporter.h"
    "E:/Ralts/Amatsu/3rdparty/assimp/code/../include/assimp/Hash.h"
    "E:/Ralts/Amatsu/3rdparty/assimp/code/../include/assimp/MemoryIOWrapper.h"
    "E:/Ralts/Amatsu/3rdparty/assimp/code/../include/assimp/ParsingUtils.h"
    "E:/Ralts/Amatsu/3rdparty/assimp/code/../include/assimp/StreamReader.h"
    "E:/Ralts/Amatsu/3rdparty/assimp/code/../include/assimp/StreamWriter.h"
    "E:/Ralts/Amatsu/3rdparty/assimp/code/../include/assimp/StringComparison.h"
    "E:/Ralts/Amatsu/3rdparty/assimp/code/../include/assimp/StringUtils.h"
    "E:/Ralts/Amatsu/3rdparty/assimp/code/../include/assimp/SGSpatialSort.h"
    "E:/Ralts/Amatsu/3rdparty/assimp/code/../include/assimp/GenericProperty.h"
    "E:/Ralts/Amatsu/3rdparty/assimp/code/../include/assimp/SpatialSort.h"
    "E:/Ralts/Amatsu/3rdparty/assimp/code/../include/assimp/SkeletonMeshBuilder.h"
    "E:/Ralts/Amatsu/3rdparty/assimp/code/../include/assimp/SmallVector.h"
    "E:/Ralts/Amatsu/3rdparty/assimp/code/../include/assimp/SmoothingGroups.h"
    "E:/Ralts/Amatsu/3rdparty/assimp/code/../include/assimp/SmoothingGroups.inl"
    "E:/Ralts/Amatsu/3rdparty/assimp/code/../include/assimp/StandardShapes.h"
    "E:/Ralts/Amatsu/3rdparty/assimp/code/../include/assimp/RemoveComments.h"
    "E:/Ralts/Amatsu/3rdparty/assimp/code/../include/assimp/Subdivision.h"
    "E:/Ralts/Amatsu/3rdparty/assimp/code/../include/assimp/Vertex.h"
    "E:/Ralts/Amatsu/3rdparty/assimp/code/../include/assimp/LineSplitter.h"
    "E:/Ralts/Amatsu/3rdparty/assimp/code/../include/assimp/TinyFormatter.h"
    "E:/Ralts/Amatsu/3rdparty/assimp/code/../include/assimp/Profiler.h"
    "E:/Ralts/Amatsu/3rdparty/assimp/code/../include/assimp/LogAux.h"
    "E:/Ralts/Amatsu/3rdparty/assimp/code/../include/assimp/Bitmap.h"
    "E:/Ralts/Amatsu/3rdparty/assimp/code/../include/assimp/XMLTools.h"
    "E:/Ralts/Amatsu/3rdparty/assimp/code/../include/assimp/IOStreamBuffer.h"
    "E:/Ralts/Amatsu/3rdparty/assimp/code/../include/assimp/CreateAnimMesh.h"
    "E:/Ralts/Amatsu/3rdparty/assimp/code/../include/assimp/XmlParser.h"
    "E:/Ralts/Amatsu/3rdparty/assimp/code/../include/assimp/BlobIOSystem.h"
    "E:/Ralts/Amatsu/3rdparty/assimp/code/../include/assimp/MathFunctions.h"
    "E:/Ralts/Amatsu/3rdparty/assimp/code/../include/assimp/Exceptional.h"
    "E:/Ralts/Amatsu/3rdparty/assimp/code/../include/assimp/ByteSwapper.h"
    "E:/Ralts/Amatsu/3rdparty/assimp/code/../include/assimp/Base64.hpp"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xassimp-devx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/assimp/Compiler" TYPE FILE FILES
    "E:/Ralts/Amatsu/3rdparty/assimp/code/../include/assimp/Compiler/pushpack1.h"
    "E:/Ralts/Amatsu/3rdparty/assimp/code/../include/assimp/Compiler/poppack1.h"
    "E:/Ralts/Amatsu/3rdparty/assimp/code/../include/assimp/Compiler/pstdint.h"
    )
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE FILE FILES "E:/Ralts/Amatsu/3rdparty/assimp/build/code/Debug/assimp-vc142-mtd.pdb")
  endif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xUnspecifiedx" OR NOT CMAKE_INSTALL_COMPONENT)
  if("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE FILE FILES "E:/Ralts/Amatsu/3rdparty/assimp/build/code/RelWithDebInfo/assimp-vc142-mt.pdb")
  endif("${CMAKE_INSTALL_CONFIG_NAME}" MATCHES "^([Rr][Ee][Ll][Ww][Ii][Tt][Hh][Dd][Ee][Bb][Ii][Nn][Ff][Oo])$")
endif()

