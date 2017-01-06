#!/bin/sh

PROGNAME=$(basename $0)
FILE=".logfile"

usage() {
  echo ""
  echo "SystemII tools v1.0 Options:"
  echo "  -ca  : Execute 'make clean all'."
  echo "  -p   : Execute 'make program'."
  echo "  -cap : Execute 'make clean all program'"
  echo "  -l   : H8 serial log store to '$FILE'"
  echo "  -t   : To display '$FILE' "
  echo "  -s   : "
}

for OPT in "$@"
do
  case "$OPT" in
    # help message
    '-h' )
      usage
      ;;
    '-ca' )
      make clean all
      ;;

    '-p' )
      make program
      ;;

    '-cap' )
      make clean all program
      ;;

    '-l' )
      cat /dev/ttyS0 > $FILE
      ;;

    '-t' )
      tailf $FILE
      ;;

    '-s' )
      if [[ -z "$2" ]] || [[ "$2" =~ ^-+ ]]; then
        grep -Ew "[^\s\S]+" $file | sed -e "s/[^0-9.]*//" > logfile
        rm -f $file
      else
        grep -Ew "[^\s\S]+" $file | sed -e "s/[^0-9.]*//" > $2
        rm -f $file
      fi
      ;;

    '--'|'-' )
      echo "$PROGNAME: Invalid argument. Please refer to '$PROGNAME -h'" 1>&2
      ;;

    -*)
      echo "$PROGNAME: Invalid argument. Please refer to '$PROGNAME -h'" 1>&2
      ;;

    *)
      if [[ ! -z "$1" ]] && [[ ! "$1" =~ ^-+ ]]; then
        echo "$PROGNAME: Invalid argument. Please refer to '$PROGNAME -h'" 1>&2
      fi
      ;;
  esac
done
echo ""
