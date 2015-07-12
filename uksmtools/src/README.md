uksmtools
========

Simple tool to monitor and control UKSM.

Compiling
---------

### Prerequisites

* gcc
* make

### Compilation

Enter **uksmtools** directory and type `make`.

### Installation

Type `sudo make install` to install uksmstat and uksmctl binaries into bin directory.

Usage
-----

### Prerequisites

You need UKSM-enabled kernel, e.g. pf-kernel.

### uksmstat

* -a — shows whether UKSM is active
* -u — shows unshared memory
* -s — shows saved memory
* -c — shows scanned memory
* -k — uses kibibytes
* -m — uses mebibytes
* -g — uses gibibytes
* -p — increases precision (specify -pppp… for better precision)
* -v — be verbose (up to -vv)
* -h — shows this help		

Typical usage: `uksmstat -sppv`.

### uksmctl

* -a — activates UKSM
* -d — deactivates UKSM
* -t — toggles UKSM state
* -v — be verbose (up to -vv)
* -h — shows this help	

Typical usage: `sudo uksmctl -a`.

Distribution and Contribution
-----------------------------

uksmstat is provided under terms and conditions of GPLv3+. See file "COPYING" for details. Mail any suggestions, bugreports and comments to me: oleksandr@natalenko.name.
