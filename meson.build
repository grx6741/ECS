project('ECS', 'cpp', default_options : ['c_std=c17']) 

raylib_dep = dependency('raylib')

sources = files('main.cpp')

executable(
  'main', 
  sources, 
  dependencies : [raylib_dep],
  override_options : ['c_std=c17']
  )
