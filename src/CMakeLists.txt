include_directories(${CUBA_INCLUDE_DIRS})
add_executable (numcal numcal.c)
target_link_libraries (numcal ${CUBA_LIBRARIES} -lm)

install(TARGETS numcal
RUNTIME DESTINATION bin COMPONENT RUNTIME
LIBRARY DESTINATION lib COMPONENT RUNTIME
ARCHIVE DESTINATION lib COMPONENT DEVELOPMENT)

