#!/usr/bin/gnuplot

set terminal pngcairo

set xlabel "{/:Italic x}"
set ylabel "{/:Italic y}"

set xrange[-50:40]
set yrange[-40:40]

set key off

set size ratio -1

#plot "3.dat" u 1:2 lt 31 title "star", "3.dat" u 3:4 w l title "planet", "3.dat" u 5:6 w l title "moon"
n=0
do for [i=1:999] {
    n=n+1
    set output sprintf('animation/3_%03.0f.png',n)
    plot "3.dat" every ::1::i u 3:4 w l, "3.dat" every ::1::i u 5:6 w l
}

#pause -1

