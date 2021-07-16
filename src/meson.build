src_prefix = 'src/'

sub_sources = []

subdir('args_interpret')
subdir('user_input')
subdir('printers')

subsrc_list = []

foreach subsrc : sub_sources
	subsrc_list += [src_prefix + subsrc]
endforeach

sources += [
	src_prefix + 'concentrate.c'
] + subsrc_list
