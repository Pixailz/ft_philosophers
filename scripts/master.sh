#!/bin/bash

lib_dir=(
	"lib/ft_printf"
	"lib/gnl"
	"lib/libft"
)

scripts_list=(
	"arrange_proto.sh"
	"arrange_src_makefile.sh"
)

INC_DIR="includes"
SRC_DIR="src"
SCRIPT_DIR="scripts"

function copy_scripts()
{
	for lib in ${lib_dir[@]}; do
		[ ! -d ${lib}/${SCRIPT_DIR} ] && mkdir ${lib}/${SCRIPT_DIR}
		for file in ${scripts_list[@]}; do
			cp ./${SCRIPT_DIR}/${file} ${lib}/${SCRIPT_DIR}/
		done
	done
}

function configure_scripts()
{
	for lib in ${lib_dir[@]}; do
		cd ${lib}
		inc_file=$(find ./${INC_DIR} -type f -name "*.h")
		inc_file=$(echo ${inc_file} | cut -d'/' -f2-)
		sed -i -E "s|INC_FILE=(.*)|INC_FILE=${inc_file}|" \
												./${SCRIPT_DIR}/arrange_proto.sh
		cd - 1>/dev/null
	done
}

function exec_scripts()
{
	for lib in ${lib_dir[@]}; do
		cd ${lib}
		for script in ${scripts_list[@]}; do
			bash ./${SCRIPT_DIR}/${script}
		done
		cd - 1>/dev/null
	done
}

function main()
{
	copy_scripts
	configure_scripts
	exec_scripts
}

main
