#!/bin/bash

SRC_DIR="src"
INC_DIR="includes"

function print_function_should_be_static()
{
	echo "    ${func}:"
	echo "        function should be static."
}

function print_static_function_should_not_be_in_the_header()
{
	echo "        function should not be in the header.h"
}

function check_function_not_in_file()
{
	for tmp_file in $(echo "${ALL_C_FILE}" | grep -v "${file}")
	do
		found_command=$(grep -E ".*${func}\(" ${tmp_file})
		if [ ${#found_command} != 0 ]
		then
			return 1;
		fi
	done
	echo "${file/*\//}:"
	return 0;
}

function check_function_not_in_header()
{
	header=$(sed -nE 's|#include "(.*)"|\1|p' ${file})
	is_in_header=$(grep -nE "^[a-zA-Z\_]+\s*\**?${func}\(" ${INC_DIR}/${header})
	if [ ${#is_in_header} != 0 ]
	then
		print_static_function_should_not_be_in_the_header
		if [ ! -z ${REPLACE} ]
		then
			sed -E -i "s|^[a-zA-Z\_]+\s*\**?${func}\(.*||" ${INC_DIR}/${header}
			sed -E -i "${is_in_header/\:*/}d" ${INC_DIR}/${header}
		fi
		return 1
	else
		return 0
	fi
}

function get_function_in_file()
{
	tmp_func=$(sed -nE 's|^[a-zA-Z\_]+\s(\**?[a-z][a-zA-Z\_]*)\(.*|\1|p' ${1} | \
			   grep -vE '^static')
	for func in ${tmp_func}
	do
		check_function_not_in_file
		if [ $? == 0 ]
		then
			if [ ! -z ${REPLACE} ]
			then
				sed -E -i "s|^[a-zA-Z\_]+\s\**?${func}\(|static\t\0|" ${file}
			fi
			print_function_should_be_static
			check_function_not_in_header
		fi
	done
}

while [ "$1" != "" ]
do
	case $1 in
		-R)
			REPLACE=1
			;;
	esac
	shift
done

ALL_C_FILE=$(find $(realpath ${SRC_DIR}) -name "*.c")
for file in ${ALL_C_FILE}
do
	get_function_in_file ${file}
done
