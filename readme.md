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
\ signal does nothing
ctrl c in the here doc
multiple nested minishells bug
cd goes to home directory
buildins should not create env var
2 times unset same env var
unset non existing env var
OLDPWD should have the old value of pwd, not the name of the old working directory
export lists env var in alphabetical order
commands stored in enviroment variables do not work
