width=0.001
bin(x,width)=width*floor(x/width)+width/2.0

beta=1.8
sigma=(gamma(1+beta)*sin(pi*beta/2)/gamma((1+beta)/2)*beta*2**((beta-1)/2))**(1/beta)
f(x,s)=1/sqrt(2*pi*s*s)*exp(-(x)**2/(2*s))

plot "out.txt" using (bin($1,width)):(1.0)/500 smooth frequency with boxes,f(x,sigma)/(abs(f(x,1)))**(1/beta)