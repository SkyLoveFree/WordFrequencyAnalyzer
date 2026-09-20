cmake_minimum_required(VERSION 3.30)

project(SkyReader)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

set(CMAKE_INSTALL_PREFIX ${CMAKE_SOURCE_DIR}/install/)


qt_standard_project_setup()#使用qt提供的标准CMake项目设置，qt_standard_project_setup()

####################################################################
#							core//业务层target
####################################################################

add_library(
	SkyReader_core
	STATIC
	core/src/FileReader.cpp
	core/include/FileReader.h
	core/src/TextAnalyzer.cpp
	core/include/TextAnalyzer.h
	core/src/UTF8Codec.cpp
	core/include/UTF8Codec.h
	core/include/utf8.h
	core/src/TextSearcher.cpp
	core/include/TextSearcher.h
	core/src/CharacterAnalyzer.cpp
	core/include/CharacterAnalyzer.h
)

target_include_directories(
	SkyReader_core
	PUBLIC
	core/include
	PRIVATE 
	third_party/utf8
)

#####################################################################
#							tests 测试target
#####################################################################

add_executable(
	SkyReader_tests
	tests/main.cpp
)

target_link_libraries(
	SkyReader_tests
	PRIVATE
	SkyReader_core
)
#####################################################################
#							GUI 页面于交互target
#####################################################################

qt_add_executable(
	SkyReader_gui
	WIN32
	GUI/src/main.cpp
	GUI/src/SkyReader_gui_Widget.cpp
	GUI/include/SkyReader_gui_Widget.h
	GUI/src/SkyReaderWidget.ui
)
target_link_libraries(
	SkyReader_gui
	PRIVATE
	SkyReader_core
	Qt6::Widgets
)
target_include_directories(
	SkyReader_gui
	PUBLIC
	GUI/include
)

qt_generate_deploy_app_script(
	TARGET SkyReader_gui
	OUTPUT_SCRIPT deploy_script
	NO_UNSUPPORTED_PLATFORM_ERROR
)

install(
	TARGETS SkyReader_gui
	RUNTIME DESTINATION bin
)

install(
	SCRIPT ${deploy_script}
)
