cmake_minimum_required(VERSION 3.12)

project(ip_filter)

add_executable(_ip_filter_ main.cpp)

set_target_properties(_ip_filter_ PROPERTIES
        CXX_STANDARD 14
        CXX_STANDARD_REQUIRED ON
)

install(TARGETS _ip_filter_ RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)
set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")
set(CPACK_PACKAGE_CONTACT example@example.com)
include(CPack)
