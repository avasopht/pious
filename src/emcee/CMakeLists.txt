project(emcee VERSION 0.0.1)

include(CMakePackageConfigHelpers)
include(GenerateExportHeader)

include_directories(${INCLUDE_DIR}/emcee)

set(INCLUDE_FILES
        ${EMCEE_INCLUDE_FILES})

include(EmceeFiles)
set(SOURCE_FILES ${EMCEE_SOURCE_FILES})


add_library(emcee STATIC ${SOURCE_FILES} ${INCLUDE_FILES})


target_compile_definitions(emcee PUBLIC "EMCEE_DEBUG=$<CONFIG:Debug>")
generate_export_header(emcee)
target_include_directories(emcee PUBLIC
        "$<BUILD_INTERFACE:${EMCEE_INCLUDE_DIR}>")
target_link_libraries(emcee)
set(config_install_dir "lib/cmake/${PROJECT_NAME}")
set(include_install_dir "include")

set(generated_dir "${CMAKE_CURRENT_BINARY_DIR}/generated")

# configuration
set(version_config "${generated_dir}/${PROJECT_NAME}-config-version.cmake")
set(project_config "${generated_dir}/${PROJECT_NAME}-config.cmake")
set(targets_export_name "${PROJECT_NAME}-targets")
set(namespace "${PROJECT_NAME}::")

write_basic_package_version_file(
        "${version_config}" COMPATIBILITY SameMajorVersion)
configure_package_config_file(
        "config.cmake.in"
        "${project_config}"
        INSTALL_DESTINATION "${config_install_dir}")

install(TARGETS emcee
        EXPORT "${targets_export_name}"
        LIBRARY DESTINATION "lib"
        ARCHIVE DESTINATION "lib"
        RUNTIME DESTINATION "bin"
        INCLUDES DESTINATION "${include_install_dir}")

install(
        DIRECTORY ${EMCEE_INCLUDE_DIR}
        DESTINATION "${include_install_dir}"
        FILES_MATCHING PATTERN "*.hpp"
)

install(
        FILES "${project_config}" "${version_config}"
        DESTINATION "${config_install_dir}"
)

#install(
#        FILES ${INCLUDE_FILES}
#        DESTINATION "${include_install_dir}"
#)

install(
        FILES "${project_config}" "${version_config}"
        DESTINATION "${config_install_dir}"
)

install(
        EXPORT "${targets_export_name}"
        NAMESPACE "${namespace}"
        DESTINATION "${config_install_dir}"
)