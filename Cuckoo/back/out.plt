width=0.001
bin(x,width)=width*floor(x/width)+width/2.0



plot "out.txt" using (bin($1,0.1)):(1.0)/100000 smooth frequency with boxes title "Levy\\_distribution"
set terminal png
set output "out.png"
replot
set terminal wxt