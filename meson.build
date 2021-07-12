project('Concenctrate', 'c',
	default_options: ['c_std=c17'])

inc = include_directories('include')

sources = []

subdir('src')

compiler = meson.get_compiler('c')
real_time_dep = compiler.find_library('rt')

exe = executable(
	'concentrate',
	sources,
	dependencies: real_time_dep,
	include_directories: inc
)

test('executable executes',exe, args: ['-h'])
