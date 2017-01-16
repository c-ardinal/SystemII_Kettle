#!/bin/sh


PROGNAME=$(basename $0)
FILE="serial.log"


usage() {
  echo ""
  echo "System-II tools v1.0 Options:"
  echo "  -ca  : Execute 'make clean all'."
  echo "  -p   : Execute 'make program'."
  echo "  -cap : Execute 'make clean all program'."
  echo "  -s   : H8 serial log store to '$FILE'."
  echo "  -d   : Display '$FILE' at realtime."
  echo "  -f   : Fairing '$FILE' and output to \$2."
}


for OPT in "$@"
do
  case "$OPT" in
    # help message
    '-h' )
      usage
      ;;
    # Program compile
    '-ca' )
      make clean all
      ;;
	# To transfer .srec file to H8
    '-p' )
      make program
      ;;
	# Program compile and transfer to H8
    '-cap' )
      make clean all program
      ;;
	# Store serial comm 
    '-s' )
      cat /dev/ttyUSB0 > ${FILE}
      ;;
	# Show logfile at real time
    '-d' ) 
      tailf ${FILE}
      ;;
	# Fairing logfile
    '-f' )
      grep -Ew "[^\s\S]+" ${FILE} | sed -e "s/[^0-9.]*//" > ${FILE}2 ; mv ${FILE}2 ${FILE}
      ;;
	# Error message
    '--'|'-' )
      echo "$PROGNAME: Invalid argument. Please refer to '$PROGNAME -h'" 1>&2
      ;;
	# Error message
    -*)
      echo "$PROGNAME: Invalid argument. Please refer to '$PROGNAME -h'" 1>&2
      ;;
	# Error message
    *)
      if [[ ! -z "$1" ]] && [[ ! "$1" =~ ^-+ ]]; then
        echo "$PROGNAME: Invalid argument. Please refer to '$PROGNAME -h'" 1>&2
      fi
      ;;
  esac
done


echo ""
