#!/bin/sh

export DYLD_LIBRARY_PATH=.
export DYLD_FORCE_FLAT_NAMESPACE=1
export DYLD_INSERT_LIBRARIES="./libft_malloc.so"
$@