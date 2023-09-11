project('ECS', 'cpp', default_options : ['c_std=c17']) 

raylib_dep = dependency('raylib')

sources = files('main.cpp')

incdir = include_directories('.')

ecs_dep = declare_dependency(
    include_directories: include_directories('.')
)

executable(
  'main', 
  sources, 
  dependencies : [raylib_dep],
  override_options : ['c_std=c17'],
  include_directories : incdir
  )
