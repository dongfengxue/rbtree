cmake_minimum_required(VERSION 3.9)
project(rbtree_master)

set(CMAKE_CXX_STANDARD 11)

add_executable(rbtree_master
        Makefile
        rb_test.c
        rbtree.c
        rbtree.h
        README.md)
