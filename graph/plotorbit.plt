#!/usr/bin/gnuplot

#set xlabel "{/:Italic x}"
#set ylabel "{/:Italic y}"

set size ratio -1

set key off
unset border
unset tics

set terminal pngcairo size 2000, 2000 crop transparent
set output "ring_cairo.png"

plot "output.dat" u 1:2 lt 31 title "star", "output.dat" u 3:4 w l title "planet", "output.dat" u 5:6 w l title "moon"

pause -1

