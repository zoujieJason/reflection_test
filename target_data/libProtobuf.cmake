include(FetchContent)
FetchContent_Declare(Protobuf
    GIT_REPOSITORY https://github.com/protocolbuffers/protobuf.git
    GIT_TAG v25.1)
FetchContent_MakeAvailable(Protobuf)

FetchContent_GetProperties(Protobuf SOURCE_DIR Protobuf_SOURCE_DIR)
include(${Protobuf_SOURCE_DIR}/cmake/protobuf-generate.cmake)
