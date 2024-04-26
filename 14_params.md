# 14. Madgraph Parameters setting

[**chapter thirteen**](13_import.md)

## 14.1 The Madgraph configuration files

Inside any Madgraph process folder the sub-folder `Cards` contains configuration files for the setup of the production process.
The table below shows a list of them with their description.

| file | content |
| ----------- | ----------- |
| run_card.dat | data taking conditions description: beam energy, pdfs, event selection, ... |
| param_card.dat | physics process description: particles definition, process definition, ... |
| mg5_configuration.txt | generic setup: external linked libraries, running mode, ... |
|  |  |
|  |  |
|  |  |
|  |  |

## 14.2 how configuration files are read

The config file are read in the following order.
when running from ./bin/mg5_aMC executable:
1. value default (hardcoded in the code)
2. system-wide config file (need environment variable MADGRAPH_BASE)
3. home config file (need environment variable HOME)
4. input/mg5_configuration.txt

When running from "process" directory:
1. value default (hardcoded in the code)
2. system-wide config file (need environment variable MADGRAPH_BASE)
3. home config file (need environment variable HOME)
4. Cards/me5_configuration.txt
5. input/mg5_configuration.txt (need that of the previous step defines mg5_dir=)
6. Cards/me5_configuration.txt (rerun only if "mg5_dir" was set)

