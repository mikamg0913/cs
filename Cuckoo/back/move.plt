set autoscale
set xlabel "x"
set ylabel "y"
plot "move.txt" using 1:2 with lp title "Levy\\_flight"
set terminal png
set output "move.png"
replot
set terminal wxt
