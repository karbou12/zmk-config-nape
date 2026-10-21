#!/bin/bash

if [[ "$1" == "nape_console" || "$1" == "nape_zephyr" ]]; then
    ln -nfs $1/nape.json nape.json
    ln -nfs $1/$1.keymap $1.keymap
    ln -nfs $1/west.yml west.yml
else
    echo "incorrect arguments"
    echo "$0 <nape_console or nape_zephyr>"
fi
