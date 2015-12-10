The **[PROOF Analysis Framework]** **(PAF)** is a tool to easily and quickly implement distributed analysis over [ROOT] trees by hiding as much as possible the inherent complexities of parallel paradigms to the users and by providing a common framework for some of the different technologies available.

The analysis of the complex [LHC] data usually follows a standard path that aims at minimizing not only the amount of data but also the number of observables used. After a number of steps of slimming and skimming the data, the remaining few terabytes of [ROOT] files typically hold a selection of the events and a flat structure for the variables needed that can be more easily inspected and traversed in the final stages of the analysis. [PROOF] arises at this point as an efficient mechanism to distribute the analysis load by taking advantage of all the cores in modern CPUs through [PROOF Lite], or by using PROOF Cluster or PROOF on Demand ([PoD]) tools to build dynamic PROOF cluster on computing facilities with spare CPUs.

However using [PROOF] at the level required for a serious analysis introduces some difficulties that may scare new adopters. We have developed the [PROOF Analysis Framework] to facilitate the development of new analysis by uniformly exposing the [PROOF] related configurations across technologies and by taking care of the tedious and repetitive tasks as much as possible.

A more detailed description and tutorials may be found in: http://www.hep.uniovi.es/PAF

See the [examples](examples) folder for some code examples.

[PROOF Analysis Framework]: http://www.hep.uniovi.es/PAF
[LHC]: http://lhc.cern.ch
[ROOT]: http://root.cern.ch/
[PROOF]: https://root.cern.ch/drupal/content/proof
[PROOF Lite]: https://root.cern.ch/drupal/content/proof-multicore-desktop-laptop-proof-lite
[PoD]: http://pod.gsi.de/
