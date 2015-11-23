call ck cp #demo-autotune-compiler-flags-adapt16-gcc-android-win-i100 #demo-autotune-flags-adapt16-gcc-android-win-pareto
call ck autotune pipeline:program pipeline_from_file=_setup_program_pipeline_tmp.json @autotune_program_pipeline_i100_apply_pareto.json %*
