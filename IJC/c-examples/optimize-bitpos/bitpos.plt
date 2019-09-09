
set terminal postscript enhanced; set output "bitpos.ps"

set title "Vliv urovne optimalizace na rychlost funkci bitpos1() a bitpos2()"
set xlabel "Uroven optimalizace prekladace [-]"
set ylabel "Cas [periody hodin CPU]"
set boxwidth 0.1
set style line 1 lt 1 lw 2
set style line 2 lt 2 lw 2
set data style boxes
set xtics 1
plot [-.8:3.8][0:] "bitpos1" using ($3-0.06):1 title "bitpos1()" ls 1, \
                   "bitpos2" using ($3+0.06):1 title "bitpos2()" ls 2

#pause -1 "Stiskni ENTER"
