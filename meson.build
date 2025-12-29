project('birthday-tracker', 'c')
jsondep = dependency('jansson')
sources =  ['src/main.c', 'src/types.c', 'src/sort.c', 'src/zodiac.c']
headers = include_directories('src')

# Include math library
cc = meson.get_compiler('c')
m_dep = cc.find_library('m', required: false)

dependencies = [m_dep, jsondep]
executable('birthday-tracker', sources, dependencies: dependencies, include_directories: headers)
