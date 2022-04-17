#!/bin/bash
#!/bin/ls
#!/bin/echo

PATH=$PATH:/bin:/usr/bin/ls
export PATH

clear



for value in 'echo test' "'echo test && echo test'"
do
    ((i=i+1))
    echo TEST $i ================ ---\> $value

    $value > shell.op
    ./minishell -c "$value" > me.op






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