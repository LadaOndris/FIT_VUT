# gnuplot this-file
set term postscript color; set output "time-profile.ps"
set logscale y
set ylabel "interruption time [us]"
set xlabel "time [us]"
set nokey
set grid
set style data points
set style data impulses
set title "time-profile output"
plot "time-profile.out" using 2:3 lw 1
