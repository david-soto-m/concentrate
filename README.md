# concentrate
<h1>Initializing</h1>
<p>
	In order to run the program for the first time you may need to run it twice. The first time it will generate some files. They will be in ~/.concentrate. Please take a look at them before running the program.
</p>
<h1>Settings</h1>
<h2>Syntax</h2>
<p>
	The settings will look something like this.
	<p>
		NEXTJUMP : 30
		DEFAULT_TIME : 15
		INFO_TIME : 5
		DEFAULTS_PATH : /home/david/.concentrate/defaultblock
		EXIT_PATH : /home/david/.bashrc
		EXIT : FALSE
	</p>
	All settings should be written like KEYWORD : ARG.
</p>
<h2>Arguments</h2>
<p>
	NEXTJUMP should be followed by the time period in minutes that you will not allow yourself to interact at all with it. 
</p>
<p>
	DEFAULT_TIME should be followed by the amount of seconds between blocks
</p>
<p>
	INFO_TIME should be followed by the time period in minutes you want feedback on.
</p>
<p>
	DEFAULT_PATH should be followed by the path to a default blockfile. 
</p>
<p>
	EXIT_PATH should be followed by a path that points to .bashrc or .bash_aliases. It prevents from opening new terminals while concentrate is in execution. Already existing ones will not be killed unless specified in a blockfile.
</p>
<p>
	EXIT is an optional argument that prevents the program from writing in the file pointed by EXIT_PATH if specified FALSE. Has the same effect as using argument -N
</p>
<h1>Blockfiles</h1>
<p>
	Blockfiles are text files that should only contain processes names separated by newlines or tabs. The can be provided by argument with the syntax <i> concentrate -f n file1 file2 ...</i>  where n is the number of files that will be provided
</p>
<h1>Interaction</h1>
<p>
	You can interact with the program by typing C-c.var represents a numerical input. The possible interactions are:
</p>
<p>
q var?: Quits, var is optional
</p>
<p>
t var: Provides var minutes off;
</p>
<p>
n var: Sets next concentration period to var minutes
</p>