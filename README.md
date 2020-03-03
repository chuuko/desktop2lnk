# desktop2lnk
An utility to convert .desktop files to iDesk .lnk files
# What is this?
desktop2lnk is an utility that converts existing .desktop files into .lnk files to be used with iDesk
# Requirements
Currently none except a compiler with C++. Dependencies will be added in the future as current limitations are resolved.
# Building
desktop2lnk is not set up to work with any build system (as I'm pretty unfamiliar with anything that isn't qmake). Compilation is as easy as g++ main.cpp -o desktop2lnk
# Limitations
desktop2lnk currently supports only ASCII characters. Also, it can't handle paths with spaces yet.
# Licensing
desktop2lnk is released under the BSD-3 license
