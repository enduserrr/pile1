#!/bin/bash

printf "$(echo {32..126} | xargs printf '\\x%x ')\n"
