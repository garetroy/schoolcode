When running serial:

Inclusive counts of docomputation (cycles)-3.033E+08
Inclusive Time of docomputation-121

cycle/time ~= 2,506,611

When running parallel:

Inclusive counts of docomputation (cycles)-2.004E+09 
Inclusive Time of docomputation-847ms

cycle/time ~= 2,365,998

When Running serial vs parallel I found some interesting results. I had to comment out the omp parts within the code to test with tau in serial. We are spending more time in parallel on docomputation, this is because we have thread nums that are increasing and will make the forloop go longer. the amounts of cycles per docomputation were only ten times in the parallel version, which I found interesting. What is more interesting is even though we are doing more work in the parallel function and we have more cycles, our ratio to cycles/time is lower than running it in serial. It shows a more efficent use of cycles for docomputation. Though the ratios were not that much different.  
