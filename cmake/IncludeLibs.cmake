cmake_minimum_required(VERSION 3.21)
add_library(third_party INTERFACE)

# Include libraries
CPMAddPackage("gh:matcool/gd-imgui-cocos#09a9555")
CPMAddPackage("gh:maxnut/GDReplayFormat#4950cc2")
CPMAddPackage("gh:SpaghettDev/subprocess#e12740b")
CPMAddPackage(
    NAME nlohmann_json
    GITHUB_REPOSITORY nlohmann/json
    VERSION 3.11.3
)

# Link them to the project
target_link_libraries(third_party INTERFACE
    libGDR
    subprocess
    imgui-cocos
    nlohmann_json::nlohmann_json
)