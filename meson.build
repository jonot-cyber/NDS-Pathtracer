project('mtest', 'c')

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

# create elf
elf = executable('mtest.elf', 'test.c', include_directories: '/opt/devkitpro/libnds/include', dependencies: libnds)

# create .nds file
ndstool = find_program('ndstool')

out = custom_target('mtest.nds', command: [ndstool, '-c', '@OUTPUT@', '-9', '@INPUT@', '-b', '/opt/devkitpro/libnds/icon.bmp', '"1;2;3"'], input: elf, output: 'mtest.nds', build_by_default: true)

# run with tool :)
flatpak = find_program('flatpak')
test('run', flatpak, args: ['run', 'net.kuribo64.melonDS', out])
