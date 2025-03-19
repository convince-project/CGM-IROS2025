<h1 align="center">
    IROS 2025 - Code Generation and Monitoring for Deliberation Components in Autonomous Robots
</h1>

<!-- <p align="center"><img src="assets/image.png" alt=""/></p> -->
<!-- 
<div align="center">
  Journal, vol. X, no. y, pp. abc-def, Month Year
</div>

<div align="center">
  <a href=""><b>Paper</b></a> |
  <a href=""><b>arXiv</b></a> |
  <a href=""><b>Video</b></a> |
</div> -->


## Table of Contents

- [Updates](#updates)
<!-- - [Installation](#installation) -->
- [Reproduce the results](#reproduce-the-paper-results)
<!-- - [Run the code with custom data](#run-the-code-with-custom-data-optional) -->
- [License](#license)
<!-- - [Citing this paper](#citing-this-paper) -->

## Updates

2025-03-17 added working example

<!-- ## Installation

```console
<all the instructions require to install your software>
```
:warning: In this section it would be good to provide the user with all the information necessary to install the correct dependencies, with the correct versions. If the dependencies are built from sources, indicating a specific commit/tag represents an alternative to specifying the version. -->

<!-- ### Execution inside a container (alternative)

look in the specific folders -->
 ## Reproduce the paper results

 to run the code you need docker installed 

 then 
 ```
 cd laboratory-tour/docker
 docker compose pull
 sudo xhost +
 docker compose up environment 
 ```
after this some windows will open, you need to find yarpmanager:
<img src="assets/yarpmanager_not_started.png" width="1700">
then, after gazebo is started, start all the application from 0, leaving 2 or 3 seconds after each (it needs to be green)

after that you will be in this situation:

<img src="assets/yarpmanager_started.png" width="1700">

once started, you need to go back to the terminal and start the oracles. 

```
docker compose up run_oracles
```

then wait 30 seconds till the oracles starts correctly

after that start the system 

```
docker compose up run_all_monitors
```

-----------------------------------

if you want to run the tests
<!--Before running the experiments, it is suggested to run the following sanity checks to make sure that the environment is properly configure:

```console
<all the instructions required to check that the environent has been configured properly>
```

Instructions for reproducing the experiments:

```console
<all the instructions required to reproduce the results>
```

Adding an example of the expected outcome might be useful.

## Run the code with custom data (optional)

Adding information on the structure of the input data and how it gets processed might be useful.

```console
<all the instructions required to run your code on custom data>
```
-->
<!-- ## License

Information about the license.

:warning: Please read [these](https://github.com/hsp-iit/organization/tree/master/licenses) instructions on how to license HSP code. -->

<!-- ## Citing this paper

```bibtex
@ARTICLE{9568706,
author={Author A, ..., Author Z},
journal={Journal},
title={Title},
year={Year},
volume={X},
number={y},
pages={abc-def},
doi={DOI}
}
``` -->

## Maintainer

This repository is maintained by:

| | |
|:---:|:---:|
| [<img src="assets/image.png" width="40">](https://github.com/hsp-iit) | [@hsp-iit](https://github.com/hsp-iit) |

