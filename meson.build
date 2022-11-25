project('glXample', 'cpp',
  version: '0.0.1',
  default_options: ['buildtype=debug',
                    'cpp_std=c++2a',
                    'warning_level=3'])

include = include_directories('include')

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

sources = ['example1.cpp']

programs = [['GL_example', sources]]


foreach p: programs
  executable (p[0], p[1], include_directories: include, dependencies: GL_dep)
endforeach
