#!/bin/bash

MAKEFILE_PATH="Makefile"

if [ "$1" == "1" ]; then
	SRC_DIR="philo"
	VARIABLE_SRC="SRC_C"
elif [ "$1" == "2" ]; then
	SRC_DIR="philo_bonus"
	VARIABLE_SRC="SRC_TMP"
else
	printf "wrong arg (1|2)\n"
	exit
fi

function insert_at_line()
{
	sed -i "${cursor}i ${1}" ${MAKEFILE_PATH}
	let "cursor=cursor+1"
}

function insert_at_line_with_tab()
{
	sed -i "${cursor}i ${file}" ${MAKEFILE_PATH}
	sed -i "s|^${file}|\t\t\t\t\t   ${file#*\/} \\\\|" ${MAKEFILE_PATH}
	let "cursor=cursor+1"
}

function append_to_variable_src()
{
	sed -i "s|${VARIABLE_SRC}				:=|${VARIABLE_SRC}				:= ${1#*\/} \\\\|" ${MAKEFILE_PATH}
	is_first=1
}

function clean_source_makefile()
{
	begin_src=$(grep -nE "^${VARIABLE_SRC}\s*:=" ${MAKEFILE_PATH})
	begin_src=${begin_src/:*/}
	cursor=${begin_src}
	#sed -i "${cursor}d" ${MAKEFILE_PATH}
	end_src=$(grep -nE '^\s*.*[0-9a-zA-Z]\.c$' ${MAKEFILE_PATH})
	end_src=${end_src/:*/}
	sed -i "${begin_src},${end_src}d" ${MAKEFILE_PATH}
	insert_at_line "${VARIABLE_SRC}				:="
}

function remove_last_backslash()
{
	let "cursor=cursor-1"
	last_src_line=$(sed -n "${cursor}p" ${MAKEFILE_PATH})
	last_src_line=$(echo ${last_src_line} | tr -d '\\' | tr -d ' ' | tr -d '\t')
	sed -i "${cursor}d" ${MAKEFILE_PATH}
	sed -i "${cursor}i ${last_src_line}" ${MAKEFILE_PATH}
	sed -i "s|^${last_src_line}|\t\t\t\t\t   ${last_src_line}|" ${MAKEFILE_PATH}
}

function remove_last_backslash_one()
{
	let "cursor=cursor-1"
	last_src_line=$(sed -n "${cursor}p" ${MAKEFILE_PATH})
	last_src_line=$(echo ${last_src_line} | tr -d '\\' | tr -d ' ' | tr -d '\t')
	last_src_line=$(echo ${last_src_line} | sed "s|${VARIABLE_SRC}:=||")
	sed -i "${cursor}d" ${MAKEFILE_PATH}
	sed -i "${cursor}i ${last_src_line}" ${MAKEFILE_PATH}
	sed -i "s|^${last_src_line}|${VARIABLE_SRC}\t\t\t:= ${last_src_line}|" ${MAKEFILE_PATH}
}

function main()
{
	is_first=0
	nb_src_file=0
	clean_source_makefile
	for file in $(find ${SRC_DIR} -type f -name "*.c" | sort)
	do
		if [ ${is_first} == 0 ]
		then
			append_to_variable_src ${file}
		else
			insert_at_line_with_tab ${file}
		fi
		nb_src_file=$((${nb_src_file} + 1))
	done
	if [ ${nb_src_file} -gt 1 ]; then
		remove_last_backslash
	else
		remove_last_backslash_one
	fi
}

main
