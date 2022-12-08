set term x11
set title "ENR 304 Final Project Test"
set xlabel "x"
set ylabel "y"
set xrange [-3:3]
set yrange [0:5]

plot "blah.dat" using 1:2 with dots title ""
