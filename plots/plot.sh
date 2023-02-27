#!/bin/bash
mkdir -p out/paper
mkdir -p out/paper_pre
mkdir -p out/simulations

# Generate plots from benchmark data
./plot.py
mv out/paper_pre/unidirectional_bw_stripe.pdf out/paper/fig1.pdf
mv out/paper_pre/unidirectional_bw_conc.pdf out/paper/fig2.pdf
mv out/paper_pre/lat_bw.pdf out/paper/fig3.pdf
mv out/paper_pre/uni_vs_bi.pdf out/paper/fig4.pdf
mv out/paper_pre/unidirectional_bw_instances.pdf out/paper/fig5.pdf
mv out/paper_pre/hoverboard.pdf out/paper/fig6.pdf
mv out/paper_pre/os_noise_instance_type_long.pdf out/paper/fig9.pdf
mv out/paper_pre/noise_lat_time_alloc_long.pdf out/paper/fig10.pdf
mv out/paper_pre/noise_lat_instance_type_long.pdf out/paper/fig11.pdf
mv out/paper_pre/noise_bw_time_alloc_long.pdf out/paper/fig12.pdf
mv out/paper_pre/noise_bw_instance_type_long.pdf out/paper/fig13.pdf

# Generate plots from simulation data
./plot_sim.py
mv out/simulations/validation_relative.pdf out/paper/fig14.pdf
mv out/simulations/scalability_nwaydissemination_16.pdf out/paper/fig15.pdf
mv out/simulations/scalability_pipelinedring_536870912.pdf out/paper/fig16.pdf
mv out/simulations/cost_on-demand_nwaydissemination_128_new.pdf out/paper/fig17.pdf
