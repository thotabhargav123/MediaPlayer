cmake_minimum_required(VERSION 3.0)
project(GloApp)

# Find wxWidgets
find_package(wxWidgets REQUIRED COMPONENTS core base media)
include(${wxWidgets_USE_FILE})

# Find GStreamer
find_package(PkgConfig REQUIRED)
pkg_check_modules(GST REQUIRED gstreamer-1.0)

# Include directories and link libraries for GStreamer
include_directories(${GST_INCLUDE_DIRS})
link_directories(${GST_LIBRARY_DIRS})

# Add the executable with both VideoPlayer and ImageSlideshow
add_executable(GloApp main.cpp VideoPlayer.cpp ImageSlideshow.cpp)

# Link wxWidgets and GStreamer libraries
target_link_libraries(GloApp ${wxWidgets_LIBRARIES} ${GST_LIBRARIES})
