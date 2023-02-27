#!/bin/bash
SYSTEM="oracle-hpc"

case $SYSTEM in
  aws-normal)
    source conf/aws-normal.sh
    ;;

  aws-hpc)
    source conf/aws-hpc.sh
    ;;

  gcp)
    source conf/gcp.sh
    ;;

  azure)
    source conf/azure.sh
    ;;

  oracle)
    source conf/oracle.sh
    ;;

  oracle-hpc)
    source conf/oracle-hpc.sh
    ;;

  daint)
    source conf/daint.sh
    ;;
  
  alps)
    source conf/alps.sh
    ;;

  deep-est)
    source conf/deep-est.sh
    ;;

  *)
    echo -n "Unknown SYSTEM "$SYSTEM
    ;;
esac
