set terminal pdf monochrome enhanced font "sans-serif,12" dashed
set title ""
set xlabel "Simulación"
set ylabel "Miss Rate"
set yrange [0:0.7]
set grid
set key center tmargin
set datafile separator ","
set xtics rotate by 90 right font "sans-serif, 10"
set boxwidth 0.5
set style fill pattern 3
plot 'results.csv' using 10:xtic(6) with boxes fill title "Miss Rate"
set terminal push
set terminal pdf
set out 'missrates.eps'
replot
set term pop
replot
