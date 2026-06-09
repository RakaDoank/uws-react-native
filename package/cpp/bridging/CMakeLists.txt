project("react_native_uws__bridging")

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
	"react_native_uws::bridging"
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
	android
	log
)
