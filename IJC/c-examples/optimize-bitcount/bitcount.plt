
set terminal postscript enhanced; set output "bitcount.ps"

set title "Vliv urovne optimalizace na rychlost funkci bitcount1() a bitcount2()"
set xlabel "Uroven optimalizace prekladace [-]"
set ylabel "Cas [periody hodin CPU]"
set boxwidth 0.1
set style line 1 lt 1 lw 2
set style line 2 lt 2 lw 2
set data style boxes
set xtics 1
plot [-.8:3.8][0:] "bitcount1" using ($3-0.06):1 title "bitcount1()" ls 1, \
                   "bitcount2" using ($3+0.06):1 title "bitcount2()" ls 2

#pause -1 "Stiskni ENTER"
