echo Building R
cd ../../
R CMD REMOVE PBDE
R CMD INSTALL PBDE
cd PBDE/tests
echo Testing R
Rscript test_kernel.R
