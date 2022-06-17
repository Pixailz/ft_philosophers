#!/bin/bash

SRC_DIR="philo"
INC_FILE=includes/philosophers.h

while [ "$1" != "" ]
do
	case $1 in
		-R)
			REPLACE=1
			;;
	esac
	shift
done

function insert_at_line()
{
	sed -i "${cursor}i ${1}" ${INC_FILE}
	let "cursor=cursor+1"
}

function clear_header()
{
	begin=$(grep -n '/\* FILES \*/' ${INC_FILE})
	cursor=${begin/:*/}
	sed -i '/\/\* FILES \*\//,/\/\* ############*/d' ${INC_FILE}
	#begin=$(echo "${begin} 2 +p" | dc)
	insert_at_line '/* FILES */'
	insert_at_line '/* ##### */'
	insert_at_line '\\'
}

function get_function_in_file()
{
	tmp_func=$(sed -nE 's|^[a-z0-9A-Z\_]+\s?(\**?[a-zA-Z\_]+)\s(\**?[a-z0-9A-Z\_]+)\(.*|\2|p' ${1} | \
			   grep -vE '^static' | sort)
	tmp_file=$(echo ${file/*${SRC_DIR}\//})
	insert_at_line "// ${tmp_file}"
	for func in ${tmp_func}
	do
		tmp1000=$(echo ${func} | sed 's|\*|\\\*|')
		tmp100=$(grep -nE "^[a-z0-9A-Z\_]+\s?(\**?[a-z0-9A-Z\_]+)\s${tmp1000}\(.*" ${file})
		if [ "${tmp100: -1}" == '\' ]; then
			next_line=$((${tmp100/:*/} + 1))
			next_line=$(sed -n "${next_line}p" ${file})
			insert_at_line "${tmp100/*:/}\\"
			tmp10=$(printf "${next_line};")
			insert_at_line "${tmp10}"
		else
			insert_at_line "$(grep -E "^[a-z0-9A-Z\_]+\s?(\**?[a-z0-9A-Z\_]+)\s${tmp1000}\(.*\)$" ${file});"
		fi
		get_current_tabulation "${func}"
	done
	insert_at_line '\\'
}

function get_current_tabulation()
{
	cursor_tmp=$(grep -n "${1}" ${INC_FILE})
	cursor_tmp=${cursor_tmp/:*/}
	current_line_nb_tab=$(sed -n "${cursor_tmp}p" ${INC_FILE} | sed -nE "s|^(.*)\s\**?[a-z0-9A-Z\_]*\(.*|\1|p" | wc -c)
	current_line_nb_tab=$((${current_line_nb_tab} - 1))
	remainder=$((${current_line_nb_tab} % 4))
	if [ ${remainder} == 0 ]; then
		current_line_nb_tab=$((${current_line_nb_tab} + 4))
	else
		current_line_nb_tab=$((${current_line_nb_tab} + 4 - ${remainder}))
	fi
	if [ ${current_line_nb_tab} -gt ${max_tab_num} ]; then
		max_tab_num=${current_line_nb_tab}
	fi
}

function arrange_one_tabulation()
{
	cursor_tmp=${1/:*/}
	current_line_nb_tab=$(sed -n "${cursor_tmp}p" ${INC_FILE} | sed -nE "s|^(.*)\s\**?[a-z0-9A-Z\_]*\(.*|\1|p" | wc -c)
	current_line_nb_tab=$((${current_line_nb_tab} - 1))
	remainder=$((${current_line_nb_tab} % 4))
	if [ ${remainder} == 0 ]; then
		current_line_nb_tab=$((${current_line_nb_tab} + 4))
	else
		current_line_nb_tab=$((${current_line_nb_tab} + 4 - ${remainder}))
	fi
	current_line_nb_tab=$((${current_line_nb_tab} / 4))
	tab_to_place=$((${max_tab_num} - ${current_line_nb_tab} + 1))
	tmp_tab=""
	while [ ${tab_to_place} != 0 ]; do
		tmp_tab="${tmp_tab}$(printf '\t')"
		tab_to_place=$((${tab_to_place} - 1))
	done
	line=$(sed -n "${cursor_tmp}p" ${INC_FILE})
	if [ "${line: -1}" == '\' ]; then
		formatted_line=$(echo "${line}"\\ | sed "s|\t|${tmp_tab}|")
	else
		formatted_line=$(sed -n "${cursor_tmp}p" ${INC_FILE} | sed "s|\t|${tmp_tab}|")
	fi
	sed -i "${cursor_tmp}d" ${INC_FILE}
	sed -i "${cursor_tmp}i ${formatted_line}" ${INC_FILE}
}

function arrange_tabulation()
{
	for line in $(grep -nE "^[a-z0-9A-Z\_]+\s?(\**?[a-z0-9A-Z\_]+)\s.*\(.*" ${INC_FILE} | cut -d':' -f1); do
		arrange_one_tabulation ${line}
	done
}

function main ()
{
	clear_header
	max_tab_num=0
	ALL_C_FILE=$(find $(realpath ${SRC_DIR}) -name "*.c" | sort)
	for file in ${ALL_C_FILE}
	do
		get_function_in_file ${file}
	done
	insert_at_line "/* ########################################################################## */"
	max_tab_num=$((${max_tab_num} / 4))
	arrange_tabulation
}

main
