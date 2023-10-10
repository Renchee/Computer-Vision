set terminal pngcairo enhanced size 800,600
set output 'psnr_plot.png'
set xlabel 'Kernel size'
set ylabel 'PSNR'
set title 'PSNR vs. Kernel Size'
plot 'psnr_data.txt' using 1:2 with linespoints title 'Mean Filter', '' using 1:3 with linespoints title 'Gaussian Filter'
