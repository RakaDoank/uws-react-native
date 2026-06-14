project("react_native_uws__app")

file(
	GLOB_RECURSE
	LIB_HEADER_SRCS
	RELATIVE
	${CMAKE_CURRENT_SOURCE_DIR}
	"./*.h"
)

add_library(
	${PROJECT_NAME}
	INTERFACE
	${LIB_HEADER_SRCS}
)

add_library(
	"react_native_uws::app"
	ALIAS
	${PROJECT_NAME}
)

target_include_directories(
	${PROJECT_NAME}
	INTERFACE
	"."
)

target_link_libraries(
	${PROJECT_NAME}
	INTERFACE
	reactnative
	jsi
	uWebSockets
	android
	log
	react_native_uws::bridging
	react_native_uws::jsi
)
