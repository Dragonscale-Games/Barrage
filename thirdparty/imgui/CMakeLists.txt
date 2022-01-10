# =============================================================================
# File:             CMakeLists.txt
# Author:           David Wong Cascante
# Email:            david.wongcascante@gmail.com
# Project:          Barrage Engine
# Date:             1/1/2022
# =============================================================================

# Create the library.
add_subdirectory(src)
# Add the directory for the header files.
target_include_directories(imgui PUBLIC "includes")
