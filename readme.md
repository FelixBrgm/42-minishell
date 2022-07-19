LET THE WORK BEGIN
https://docs.brew.sh/Installation
TODO:
$? handling
Signals
echo errors with the-n
chage global variable to g_

//11.07.2022
fix multiple pipes next to each other
change the forking (fork and exec everything if there are pipes, no pipes no fork)

-----
cd goes to home directory
2 times unset same env var
unset non existing env var
OLDPWD should have the old value of pwd, not the name of the old working directory
commands stored in enviroment variables do not work

	ctrl c in the here doc
	export lists env var in alphabetical order



POINTERS 
	set to NULL
	if allocated freed or in the description 
	if allocated protected
INPUT
	if (!env)

//17.07.2022
free file lists on each iteration - should be fixed now

//18.07.2022
ft_free_split segfaults - should be fixed
fix add_spaces - should be fizef

//19.07.2022
segfault on <out <<END
exiting on ulimit 4
change X_OK to F_OK
change printf to ft_printf in echo
check multiple pipes
trunc tabs and new lines
exit with args segfault
echo '$='
