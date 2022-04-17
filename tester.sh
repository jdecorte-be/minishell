#!/bin/bash
#!/bin/ls
#!/bin/echo

clear

for value in 'ls' "cat test.c && ls" "cat test.c || ls" "export && ls" "cat test.c || ls"
do
    ((i=i+1))
    echo TEST $i ================ ---\> $value

    eval $value > shell.op
    echo RETURN ERROR SHELL : ${LINENO}
    eval ./minishell -c '"' $value '"' > me.op
    echo RETURN ERROR ME : ${LINENO}

    if diff shell.op me.op
    then
        echo -e $(printf "\e[32mOK\e[0m")
    else
        echo -e $(printf "\e[31mKO\e[0m")
    fi

    echo
    echo
done


# clear
# declare -a arr=("ls -la && echo test" "ls -la || echo test" "echo test|| echo test" "echo Je suis un test")

# for (( i = 0; i < ${#arr[@]} ; i++ )); do
#     echo ${arr[$i]} ================ $i

#     if diff <(`${arr[$i]}`) <(./minishell -c ${arr[$i]})
#     then
#         echo -e $(printf "\e[32mOK\e[0m")
#     else
#         echo -e $(printf "\e[31mKO\e[0m")
#     fi
#     echo
#     echo
# done