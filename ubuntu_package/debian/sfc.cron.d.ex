#
# Regular cron jobs for the sfc package
#
0 4	* * *	root	[ -x /usr/bin/sfc_maintenance ] && /usr/bin/sfc_maintenance
