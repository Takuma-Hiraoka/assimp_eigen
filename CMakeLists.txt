cmake_minimum_required(VERSION 3.16)
project(assimp_eigen)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Release)

find_package(ament_cmake REQUIRED)
find_package(Eigen3 3.3 REQUIRED)
set(dependencies
  Eigen3
  assimp
)

foreach(dep ${dependencies})
  find_package(${dep} REQUIRED)
endforeach()

add_library(${PROJECT_NAME}
  src/assimp_eigen.cpp
  )

target_include_directories(${PROJECT_NAME}
  PUBLIC
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
  )

target_link_libraries(${PROJECT_NAME}
  PUBLIC
  Eigen3::Eigen
  assimp
  )

ament_target_dependencies(${PROJECT_NAME}
  ${dependencies}
  )

install(TARGETS ${PROJECT_NAME}
  EXPORT export_${PROJECT_NAME}
  ARCHIVE DESTINATION lib
  LIBRARY DESTINATION lib
  RUNTIME DESTINATION bin
  )

install(DIRECTORY include/
  DESTINATION include
  )

ament_export_targets(export_${PROJECT_NAME} HAS_LIBRARY_TARGET)
ament_export_dependencies(${dependencies})

ament_package()
