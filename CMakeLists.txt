cmake_minimum_required(VERSION 3.05)

# set the project name
project(EADIGS104)

# add the executable
add_executable(EADIGS104 main.c ssd1803a-spi.c spi-implement.c)
