#!/bin/bash

./optimize.py

#Update gvim - assumes results.txt is open
gvim --servername results --remote-send ':e<CR>'

