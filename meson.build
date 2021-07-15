project(
	'concentrate',
	'c',
	version: '1.0.0',
	license: 'Unlicence'
)

sources = []

install_dir = join_paths(get_option('prefix'),'bin')
locale_dir = join_paths(get_option('prefix'),get_option('datadir'),'locale')

config_h = configuration_data()
config_h.set_quoted('GETTEXT_PACKAGE', meson.project_name())
config_h.set_quoted('LOCALEDIR', locale_dir)
configure_file(output: 'config.h', configuration: config_h)

config_include = include_directories('.')
inc = include_directories('include')

compiler = meson.get_compiler('c')
real_time_dep = compiler.find_library('rt')

subdir('src')
subdir('po')

exe = executable(
	'concentrate',
	sources,
	dependencies: [real_time_dep],
	include_directories: inc,
	install_dir: install_dir,
	install: true
)
