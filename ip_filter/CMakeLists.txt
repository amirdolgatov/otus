cmake_minimum_required(VERSION 3.12)

set(PATCH_VERSION "1" CACHE INTERNAL "Patch version")  # для сборки пакета необходимо указать номер версии
set(PROJECT_VESRION 0.0.${PATCH_VERSION})

project(ip_filter)

configure_file(version.h.in version.h)

add_executable(_ip_filter_ main.cpp)

set_target_properties(_ip_filter_ PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
)

install(TARGETS _ip_filter_ RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")  # здесь указаны настройки сборки пакета
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT example@example.com)
include(CPack)
