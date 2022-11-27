project('glXample', 'cpp',
  version: '0.0.1',
  default_options: ['buildtype=debug',
                    'cpp_std=c++2a',
                    'warning_level=3'])

include = include_directories('../include')

opengl_dep = dependency('OpenGL', required: true)
glfw_dep = dependency('glfw3', required: false)
glew_dep = dependency('glew', required: false)
thread_dep = dependency('threads')

compiler = meson.get_compiler('cpp')
base_path = meson.current_source_dir()
libs_path = join_paths(base_path, '../lib')

if not glfw_dep.found()
  glfw_dep = compiler.find_library('glfw3_mt', dirs: libs_path)
endif
if not glew_dep.found()
  glew_dep = compiler.find_library('glew32', dirs: libs_path)
endif


GL_dep = [opengl_dep, glfw_dep, glew_dep, thread_dep]

sources_ex1 = ['ex1/example1.cpp']
sources_ex2 = ['ex2/example2.cpp', 'shader.cpp']
sources_ex3 = ['ex3/example3.cpp', 'shader.cpp']
sources_ex4 = ['ex4/example4.cpp', 'shader.cpp']
sources_ex5 = ['ex5/example5.cpp', 'shader.cpp', 'texture.cpp']

programs = [['example1', sources_ex1],
            ['example2', sources_ex2],
            ['example3', sources_ex3],
            ['example4', sources_ex4],
            ['example5', sources_ex5]
           ]


foreach p: programs
  executable (p[0], p[1], include_directories: include, dependencies: GL_dep)
endforeach
