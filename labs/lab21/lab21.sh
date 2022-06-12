#!/usr/bin/env bash

function die() {
	for MSG in "$@"; do
		echo "$MSG" 1>&2
	done
	exit 1
}

SUFFIX=''
NUMBER=0
PATH_FILES='.'
SHOW_NUMBER=0
SEPARATOR=''
COPY_TEXT=''

while [[ ${1::1} == '-' ]]; do
	case "$1" in
		-h|--help) 
			echo -e "$0\nУдлинение файлов с указанным суффиксом до заданной длины путём присоединения к ним необходимого числа копий некоторого файла\n"
			echo -e "$0 [OPTION] SUFFIX NUMBER [FILE]\n\nЕсли FILE не указан, то чтение со стандартного ввода\n"
			echo -e "-c\n\tВывести количество присоединённых копий для каждого файла\n\n-s, --separator SEPARATOR\n\tВставить между копиями SEPARATOR (по умолчанию '')\n"
			echo -e "-p, --path PATH_FILES\n\tПуть до файлов\n\n-h, --help\n\tCправка\n"
			echo -e "Пример\n\t$0 .txt 100 file \tДополняет все файлы с суффиксом .txt до 100 знаков копиями содержимого файла file"
			die
			;;
		-c) SHOW_NUMBER=1 ;;
		-p|--path) PATH_FILES="$2"; shift ;;
		-s|--separator) SEPARATOR="$2"; shift ;;
		*) die "Неверный ключ $1" ;;
	esac
	shift
done

if [[ $# < 2 || $# > 3 ]]; then
	die "Неверное количество аргументов"
fi 
SUFFIX="$1";
NUMBER="$2";
if [[ $# == 3 ]]; then
	if [[ ! -f $3 ]]; then
		die "$3 does not exist or is not a file"
	else
		COPY_TEXT="$(cat $3)"
	fi
else
	while read LINE; do
		COPY_TEXT="$COPY_TEXT$LINE"
	done
fi

if [[ -z $COPY_TEXT ]]; then
	die "copy text is empty"
fi

COPY_TEXT="$SEPARATOR$COPY_TEXT"

while read FILENAME; do
	text="$(cat $FILENAME)"
	copy_n=0
	if ((${#text}<$NUMBER)); then
		let copy_n="($NUMBER-${#text})/(${#COPY_TEXT})"
		for ((i=0; i<"$copy_n"; i++)); do 
			text="$text$COPY_TEXT"
		done
		text="$text${COPY_TEXT::($NUMBER-${#text})}"
		cat > $FILENAME <<< "$text"
	fi
	if (($SHOW_NUMBER == 1)); then
		echo "$FILENAME - $copy_n"
	fi
done < <(find "$PATH_FILES" -maxdepth 1 -type f -name "*$SUFFIX")
