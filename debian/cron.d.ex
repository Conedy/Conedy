#
# Regular cron jobs for the neurosim package
#
0 4	* * *	root	[ -x /usr/bin/neurosim_maintenance ] && /usr/bin/neurosim_maintenance
