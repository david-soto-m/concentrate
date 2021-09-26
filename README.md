# Concentrate

It's a program that sends sigkills to the processes specified in files.
It could possibly be helpful in order to focus on a task via killing everything that isn't required with the task.
It is available in Spanish and English.

It is built and installed with the meson build system.
In order to install it use the script build_start, go to your build directory and then run ```meson install```.

## Initializing

In order to run the program for the first time you may need to run it twice.
The first time it will generate some files.
They will be in ```~/.config/concentrate```.
Please take a look at them before running the program.

## Settings

### Syntax

All settings should be written like ```KEYWORD : ARG```.The settings will look something like this.

~~~
NEXTJUMP : 30
DEFAULT_TIME : 15
INFO_TIME : 5
DEFAULTS_PATH : /home/$(USER)/.config/concentrate/defaultblock
EXIT_PATH : /home/$(USER)/.bashrc
EXIT : FALSE
~~~

### Arguments

```NEXTJUMP```
: should be followed by the time period in minutes that you will not allow yourself to interact at all with it.

```DEFAULT_TIME```
: should be followed by the amount of seconds between blocks

```INFO_TIME```
: should be followed by the time period in minutes you want feedback on.

```DEFAULT_PATH```
: should be followed by the path to a default blockfile.

```EXIT_PATH```
: should be followed by a path that points to .bashrc or .bash_aliases. It prevents from opening new terminals while concentrate is in execution. Already existing ones will not be killed unless specified in a blockfile.

```EXIT```
: is an optional argument that prevents the program from writing in the file pointed by EXIT_PATH if specified FALSE. Has the same effect as using argument -N

## Blockfiles

Blockfiles are text files that should only contain processes names separated by newlines or tabs.
The can be provided by argument with the syntax ```concentrate -f n file1 file2 ...```  where n is the number of files that will be provided.

## Interaction

You can interact with the program by typing ```C-c```. var represents a numerical input. The possible interactions are:

```q var?```
: Quits, var is optional

```t var```
: Provides var minutes off;

```n var```
: Sets next concentration period to var minutes
