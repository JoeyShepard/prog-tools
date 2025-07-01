#!/bin/bash

grep -rn --color=always src/ -e "$@"
