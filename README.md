CK repository to reproduce ADAPT'16 paper
=========================================

Reproducing results from http://arxiv.org/abs/1511.02603 
via Collective Knowledge's engine to crowdsource 
compiler flag autotuning (iterative compilation) 
across participating devices such as Android mobile 
phones and tables.

This is done as a part of our initiative to collect as many 
public benchmarks and data sets as possible to crowdsource 
compiler autotuning (http://arxiv.org/abs/1506.06256)

Discussion:
* https://www.reddit.com/r/adaptworkshop/comments/3sngjk/adapt16_submission_iterative_compilation_on/

Our related work:

* http://cTuning.org
* http://cTuning.org/ae

* http://dl.acm.org/citation.cfm?id=1880047
* https://hal.inria.fr/hal-01054763
* http://arxiv.org/abs/1506.06256
* http://arxiv.org/abs/1407.4075
* http://cknowledge.org/interactive-report

* Android App to crowdsource iterative compilation: https://play.google.com/store/apps/details?id=com.collective_mind.node

* Participating mobile phones and tablets in crowd-tuning: http://cTuning.org/crowdtuning-mobiles
* Processors from above mobile phones: http://cTuning.org/crowdtuning-processors
* Some results from crowdtuning: http://cTuning.org/crowdtuning-results
* cTuning benchmarks in CK format: http://github.com/ctuning/ctuning-programs

See CK documentation to prepare crowd-tuning:
* https://github.com/ctuning/ck/wiki/Getting_started_guide_tools

Prerequisites
=============
* Collective Knowledge Framework: http://github.com/ctuning/ck

Installation
============

> ck pull repo:reproduce-adapt16

Check autotuning scripts for Android (including graphs)

> ck find script:autotuning-compiler-flags-adapt16*

Check CK-based iterative compilation results for GCC 4.9 
and CLANG 3.5  on Huawei Y330 Android mobile phone

> ck find experiment:*adapt16*