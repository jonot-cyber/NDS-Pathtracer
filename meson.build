project('pathtracer', 'c')

# C flags
add_project_arguments('-DARM9', language: 'c')
add_project_arguments('-MMD', language: 'c')
add_project_arguments('-MP', language: 'c')
add_project_arguments('-march=armv5te', language: 'c')
add_project_arguments('-mtune=arm946e-s', language: 'c')
add_project_arguments('-fomit-frame-pointer', language: 'c')

# Link flags
add_project_link_arguments('-specs=ds_arm9.specs', language: 'c')

# libnds
libnds = meson.get_compiler('c').find_library('nds9', dirs: '/opt/devkitpro/libnds/lib', static: true, required: true)
math = meson.get_compiler('c').find_library('m')

# create elf
elf = executable('pathtracer.elf', ['main.c', 'vector3.c', 'ray.c', 'sphere.c'], include_directories: '/opt/devkitpro/libnds/include', dependencies: [libnds, math])

# create .nds file
ndstool = find_program('ndstool')

game_title = 'Jonot\'s NDS Pathtracer'
out = custom_target(meson.project_name()+'.nds', command: [ndstool, '-c', '@OUTPUT@', '-9', '@INPUT@', '-b', '@SOURCE_ROOT@/icon.bmp', '"' + game_title + '"'], input: elf, output: meson.project_name()+'.nds', build_by_default: true, depend_files: './icon.bmp')

# run with tool :)
flatpak = find_program('flatpak')
test('run', flatpak, args: ['run', 'net.kuribo64.melonDS', out])
