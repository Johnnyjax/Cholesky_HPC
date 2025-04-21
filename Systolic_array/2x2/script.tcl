
####
open_project chol
set_top top
add_files chol.cpp
add_files chol.h
add_files -tb chol_tb.cpp
open_solution "solution1"
set_part  {xc7z020clg400-1}
create_clock -period 10

csynth_design

exit

