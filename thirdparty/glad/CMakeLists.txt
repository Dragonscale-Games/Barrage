# =============================================================================
# File:             CMakeLists.txt
# Author:           David Wong Cascante
# Email:            david.wongcascante@gmail.com
# Project:          Barrage Engine
# Date:             1/1/2022
# =============================================================================

# And create the directory for it.
add_subdirectory(src)
# Set the include directories.
target_include_directories(glad PUBLIC "includes")
