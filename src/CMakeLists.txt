set(SRC
    main.cpp
)

add_executable(ldclient WIN32 ${SRC})
set_target_properties(ldclient PROPERTIES CXX_STANDARD 11)

target_link_libraries(ldclient Qt5::Network Qt5::WebSockets Qt5::Widgets)

install(TARGETS ldclient RUNTIME DESTINATION bin)
