<h1 align="center">
    IROS 2025 - Code Generation and Monitoring for Deliberation Components in Autonomous Robots
</h1>



## Table of Contents

- [Updates](#updates)
- [Reproduce the results](#reproduce-the-paper-results)
- [License](#license)

## Updates

2025-03-17 added working example

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

if you want to run the tests, edit line 184 of `docker-compose.yml` with one of the following

|**test in paper**|**line to put**|
|:---:|:---:|
|T1|`yarpmanager-console --application $${UC3_DIR}/launch/applications/convince_bt_skills_T1.xml --exit --run --connect"`|
|T2|`yarpmanager-console --application $${UC3_DIR}/launch/applications/convince_bt_skills_T2.xml --exit --run --connect"`|
|T3|`yarpmanager-console --application $${UC3_DIR}/launch/applications/convince_bt_skills_T3.xml --exit --run --connect"`|
|T4|`yarpmanager-console --application $${UC3_DIR}/launch/applications/convince_bt_skills_T4.xml --exit --run --connect"`|
|T5|`yarpmanager-console --application $${UC3_DIR}/launch/applications/convince_bt_skills_T5.xml --exit --run --connect"`|
|T6|`yarpmanager-console --application $${UC3_DIR}/launch/applications/convince_bt_skills_T6.xml --exit --run --connect"`|

and then run all as above.

to see the results of the monitors:

```
 cd laboratory-tour/docker
```
then based on the test:
|**test in paper**|**line to put**|
|:---:|:---:|
|T1|yarpmanager-console --application $${UC3_DIR}/launch/applications/convince_bt_skills_T1.xml --exit --run --connect"|
|T2|yarpmanager-console --application $${UC3_DIR}/launch/applications/convince_bt_skills_T2.xml --exit --run --connect"|
|T3|yarpmanager-console --application $${UC3_DIR}/launch/applications/convince_bt_skills_T3.xml --exit --run --connect"|
|T4|yarpmanager-console --application $${UC3_DIR}/launch/applications/convince_bt_skills_T4.xml --exit --run --connect"|
|T5|yarpmanager-console --application $${UC3_DIR}/launch/applications/convince_bt_skills_T5.xml --exit --run --connect"|
|T6|yarpmanager-console --application $${UC3_DIR}/launch/applications/convince_bt_skills_T6.xml --exit --run --connect"|

## Maintainer

This repository is maintained by:

| | |
|:---:|:---:|
| [<img src="assets/image.png" width="40">](https://github.com/hsp-iit) | [@hsp-iit](https://github.com/hsp-iit) |

