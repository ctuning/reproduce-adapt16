rem call ck rm experiment:demo-autotune-flags-adapt16-gcc-android-win-i10-pareto
rem call ck cp experiment:demo-autotune-flags-adapt16-gcc-android-win-i10 :demo-autotune-flags-adapt16-gcc-android-win-i10-pareto
call ck autotune pipeline:program pipeline_from_file=_setup_program_pipeline_tmp.json @autotune_program_pipeline_i10_apply_pareto.json %*
