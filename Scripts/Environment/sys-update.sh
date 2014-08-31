#! /bin/sh
### BEGIN INIT INFO
# Provides:          system update&upgrade
# Required-Start:
# Required-Stop:
# Default-Start:     always execute
# Default-Stop:      
# Short-Description: Execute a full systeme update and upgrade without user intervention.
# Description:
### END INIT INFO

PATH=/sbin:/usr/sbin:/bin:/usr/bin

do_start () {
    apt-get update && apt-get -y upgrade
    date +"%d-%m-%y" > /home/poly/lastSystUpgrade
}

case "$1" in
  start)
	do_start
	;;
  restart|reload|force-reload)
	echo "Error: argument '$1' not supported" >&2
	exit 3
	;;
  stop)
	;;
  *)
	echo "Usage: $0 start|stop" >&2
	exit 3
	;;
esac
