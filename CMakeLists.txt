cmake_minimum_required(VERSION 3.25)
project(argentum)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets Network)
qt_standard_project_setup()

qt_add_executable(argentum
        source/main.cpp
        source/ui/window.cpp
        source/ui/window.h
        source/data/transaction.h
        source/data/transaction.cpp
        source/util/error.cpp
        source/util/error.h
        source/ui/transaction_list_window.cpp
        source/ui/transaction_list_window.h
        source/ui/timeline_window.cpp
        source/ui/timeline_window.h
        source/data/transactions_model.cpp
        source/data/transactions_model.h
        source/api/sumup.cpp
        source/api/sumup.h
)

target_link_libraries(argentum
        PRIVATE Qt6::Core Qt6::Widgets Qt6::Network
)

target_compile_options(argentum PRIVATE -Wall -Werror -Wextra -Wpedantic)