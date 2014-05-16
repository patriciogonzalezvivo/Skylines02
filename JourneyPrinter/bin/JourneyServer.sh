#!/bin/bash
# /etc/init.d/JourneyServer.sh

### BEGIN INIT INFO
# Provides:          JourneyServer
# Required-Start:    $remote_fs $syslog
# Required-Stop:     $remote_fs $syslog
# Default-Start:     2 3 4 5
# Default-Stop:      0 1 6
# Short-Description: JourneyPrinter script
# Description:       runs JourneyPrinter at the begining of a session
### END INIT INFO

USER=pi
OUT=journey.log

case "$1" in

start)
  echo "Starting JourneyPrinter"
  cd /home/pi/openFrameworks/apps/Skylines02/JourneyPrinter/bin
  while : ; do
  	sudo -u $USER ./JourneyPrinter>> $OUT 2>>$OUT&
  	sleep 30; 
	done
	;;

stop)
	killall JourneyPrinter
	;;

*)
	echo "usage: $0 (start|stop)"
esac

exit 0
