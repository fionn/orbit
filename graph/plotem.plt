#!/usr/bin/gnuplot

set xlabel "{/:Italic x}"
set ylabel "{/:Italic y}"

set xrange [-1.2:1.0]
set yrange [-1.0:1.2]

set key off

set size ratio -1

#plot "2.dat" u 1:2 lt 31 title "planet", "2.dat" u 3:4 w l title "moon"
do for [i=1:99999] {
    plot "2.dat" every ::1::i u 3:4 w l
}

pause -1

