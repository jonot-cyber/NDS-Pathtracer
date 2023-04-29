# NDS Pathtracer
This program is a Pathtracer that runs on the Nintendo DS

## Building
You must install devkitpro for this build to work

`meson setup --cross-file devkitpro.ini build`

To compile with optimizations, do this:

`meson setup --cross-file devkitpro.ini --buildtype minsize -Db_lto=true build`

Then, run:

`ninja -C build`

To compile it
