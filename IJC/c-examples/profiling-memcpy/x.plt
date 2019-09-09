set term postscript color; set output "x.ps"
set grid
set nokey
set logscale x
set xlabel "block size [KiB]"
set ylabel "memory bandwidth [B/clock]"
#set data style dots
#set data style linespoints
set data style lines 
plot [][0:] "x" using 1:2 lw 3
#pause -1

