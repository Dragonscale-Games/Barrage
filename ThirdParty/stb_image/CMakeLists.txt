# =============================================================================
# File:             CMakeLists.txt
# Author:           David Wong Cascante
# Email:            david.wongcascante@gmail.com
# Project:          Barrage Engine
# Date:             1/1/2022
# =============================================================================

# And add the library.
add_subdirectory(src)
# Same thing here, add directories and create a library.
target_include_directories(stb_image PUBLIC "includes")
