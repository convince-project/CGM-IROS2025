ARG base_img=ste93/convince:qt_6.7.3_ubuntu22.04_iron_stable_sim
FROM $base_img
LABEL maintainer="Stefano Bernagozzi"
USER root

ENV DEBIAN_FRONTEND=noninteractive

RUN apt-get update 
RUN apt-get install -y libczmq-dev ros-iron-zmqpp-vendor-dbgsym ros-iron-zmqpp-vendor libczmq-dev libczmq4 curl 

RUN apt install qtbase5-dev libqt5svg5-dev libzmq3-dev libdw-dev libboost-all-dev -y

ENV Qt6_DIR=/home/user1/Qt6.7.3/lib/cmake
RUN usermod -a -G audio user1
# install behavior tree.cpp v3.8
WORKDIR /home/user1
RUN /bin/bash -c "git clone --recurse-submodules https://github.com/BehaviorTree/BehaviorTree.CPP.git -b v3.8 && \
    cd BehaviorTree.CPP && \
    cmake -S . -B build && \
    cmake --build build && \
    cmake --install build"

RUN pip install reelay websocket-client jedi prompt_toolkit

RUN /bin/bash -c "git clone --recurse-submodules https://github.com/BehaviorTree/Groot.git && \
    cd Groot && \
    cmake -S . -B build && \
    cmake --build build && \
    cmake --install build"

USER user1

#add fakeNavigation device
WORKDIR ${robotology_install_folder}

# RUN /bin/bash -c "cd /home/user1 && \
#     sudo apt install maven openjdk-21-jdk -y && \
#     git clone https://github.com/apache/commons-scxml.git && \
#     cd commons-scxml && \
#     mvn && \
#     mvn org.apache.maven.plugins:maven-install-plugin:2.5.2:install-file -Dfile=target/commons-scxml2-2.0-SNAPSHOT.jar"



RUN cd yarp && \
    git remote add ste93 https://github.com/ste93/yarp && \
    git fetch ste93 && \
    git checkout ste93/test/yarpmanager/default_app && \
    cd build && \
    cmake .. \
    -DCMAKE_BUILD_TYPE=Release \
    -DYARP_COMPILE_libYARP_math=ON \
    -DYARP_COMPILE_GUIS=ON \
    -DYARP_COMPILE_DEVICE_PLUGINS=ON \
    -DENABLE_yarpcar_mjpeg=ON \
    -DENABLE_yarpcar_segmentationimage=ON \
    -DENABLE_yarpcar_portmonitor=ON \
    -DENABLE_yarpmod_portaudio=ON \
    -DENABLE_yarpmod_portaudioPlayer=ON \
    -DENABLE_yarpmod_portaudioRecorder=ON \
    -DENABLE_yarpmod_fakeAnalogSensor=ON \
    -DENABLE_yarpmod_fakeBattery=ON  \
    -DENABLE_yarpmod_fakeDepthCamera=ON \
    -DENABLE_yarpmod_fakeIMU=ON  \
    -DENABLE_yarpmod_fakeLaser=ON  \
    -DENABLE_yarpmod_fakeLocalizer=ON \
    -DENABLE_yarpmod_fakeMicrophone=ON  \
    -DENABLE_yarpmod_fakeMotionControl=ON  \
    -DENABLE_yarpmod_fakeNavigation=ON  \
    -DENABLE_yarpmod_fakeSpeaker=ON  \
    -DENABLE_yarpmod_fakebot=ON \
    -DENABLE_yarpmod_laserFromDepth=ON \
    -DENABLE_yarpmod_laserFromExternalPort=ON \
    -DENABLE_yarpmod_laserFromDepth=ON \
    -DENABLE_yarpmod_laserFromPointCloud=ON \
    -DENABLE_yarpmod_laserFromRosTopic=ON \
    -DENABLE_yarppm_soundfilter_resample=ON \
    -DENABLE_yarppm_bottle_compression_zlib=ON \
    -DENABLE_yarppm_depthimage_compression_zlib=ON \
    -DENABLE_yarppm_image_compression_ffmpeg=ON \
    -DENABLE_yarppm_depthimage_to_mono=ON \
    -DENABLE_yarppm_depthimage_to_rgb=ON && \
    make -j11


RUN cd yarp-devices-ros2/ros2_interfaces_ws && /bin/bash -c "source /opt/ros/iron/setup.bash; colcon build"
RUN cd yarp-devices-ros2 && cd build && /bin/bash -c "source /opt/ros/iron/setup.bash; source ${robotology_install_folder}/yarp-devices-ros2/ros2_interfaces_ws/install/setup.bash; cmake .. -DYARP_ROS2_USE_SYSTEM_map2d_nws_ros2_msgs=ON -DYARP_ROS2_USE_SYSTEM_yarp_control_msgs=ON; make -j11"
    
WORKDIR /home/user1 

RUN /bin/bash -c "cd /home/user1 && rm -rf ROSMonitoring"

RUN /bin/bash -c "source /opt/ros/iron/setup.bash && \
    cd /home/user1 && git clone https://github.com/ste93/ROSMonitoring.git -b ros2"

# installing as2fm
RUN /bin/bash -c "/home/user1/convince-python-env/bin/pip install --upgrade pip"
RUN /bin/bash -c "source /opt/ros/iron/setup.bash && \
    cd /home/user1 && \
    git clone https://github.com/convince-project/AS2FM.git && /home/user1/convince-python-env/bin/python -m pip install AS2FM/"

# install SCAN
USER user1
RUN /bin/bash -c "curl https://sh.rustup.rs -sSf | sh -s -- -y"

# curl --proto '=https' --tlsv1.2 -sSf https://sh.rustup.rs -y| sh "

RUN /bin/bash -c "source /home/user1/.cargo/env && cargo install --git https://github.com/convince-project/scan"

RUN /bin/bash -c "sudo apt install gobject-introspection libgirepository1.0-dev -y"
RUN /bin/bash -c "cd /home/user1/ && \
python3 -m venv monitoring-python-env && \
/home/user1/monitoring-python-env/bin/pip install --upgrade pip && \
/home/user1/monitoring-python-env/bin/pip install websocket_client rospy_message_converter pyyaml reelay jedi pycairo PyGObject==3.50.0 prompt_toolkit"


RUN echo "export PATH=\$PATH:/home/user1/Groot/build" >> ~/.bashrc

RUN /bin/bash -c "echo 'updated on 2025023061457' && \
    source /opt/ros/iron/setup.bash && \
    cd /home/user1 && \
    git clone https://github.com/convince-project/CGM-IROS2025.git && \
    mv CGM-IROS2025 UC3 && \
    source /opt/ros/iron/setup.bash && \
    cd /home/user1/UC3/laboratory-tour/ && \
    colcon build --base-paths src/* --packages-ignore face_expressions_wrapper dialog_component"


RUN echo "source /home/user1/UC3/laboratory-tour/install/setup.bash" >> ~/.bashrc
# 

# RUN /bin/bash -c "source /opt/ros/iron/setup.bash && \
#     cd /home/user1/ROSMonitoring/generator/ros2_devel && \
#     /home/user1/monitoring-python-env/bin/python generator --config_file /home/user1/UC3/laboratory-tour/monitoring/monitor_prop1.yaml && \
#     /home/user1/monitoring-python-env/bin/python generator --config_file /home/user1/UC3/laboratory-tour/monitoring/monitor_prop2.yaml && \
#     /home/user1/monitoring-python-env/bin/python generator --config_file /home/user1/UC3/laboratory-tour/monitoring/monitor_prop3.yaml && \
#     /home/user1/monitoring-python-env/bin/python generator --config_file /home/user1/UC3/laboratory-tour/monitoring/monitor_prop4.yaml && \
#     /home/user1/monitoring-python-env/bin/python generator --config_file /home/user1/UC3/laboratory-tour/monitoring/monitor_prop5.yaml && \
#     /home/user1/monitoring-python-env/bin/python generator --config_file /home/user1/UC3/laboratory-tour/monitoring/monitor_test_intro.yaml && \
#     cd /home/user1/UC3/laboratory-tour/monitoring/monitor_prop1_ws/src/ && \
#     colcon build && \
#     cd /home/user1/UC3/laboratory-tour/monitoring/monitor_prop2_ws/src/ && \
#     colcon build && \
#     cd /home/user1/UC3/laboratory-tour/monitoring/monitor_prop3_ws/src/ && \
#     colcon build && \
#     cd /home/user1/UC3/laboratory-tour/monitoring/monitor_prop4_ws/src/ && \
#     colcon build && \
#     cd /home/user1/UC3/laboratory-tour/monitoring/monitor_test_intro_ws/src/ && \
#     colcon build && \
#     cd /home/user1/UC3/laboratory-tour/monitoring/monitor_prop5_ws/src/ && \
#     colcon build"



# RUN /bin/bash -c "source /opt/ros/iron/setup.bash && \
#     cd /home/user1/ && \
#     git clone https://github.com/convince-project/MOON.git -b dev/model-monitoring && \
#     cd /home/user1/MOON/ModelMonitor/modeloracle && \
#     mvn install"


# RUN /bin/bash -c "source /opt/ros/iron/setup.bash && \
#     cd /home/user1/MOON/ModelMonitor/config_generator && \
#     python3 config_gen.py --monitor-ws-path /home/user1/UC3/laboratory-tour/monitoring/monitor_skill_battery/src --oracle-address 127.0.0.1:8081 /home/user1/UC3/laboratory-tour/model-high-level/Skills/BatteryLevelSkill.scxml"

# RUN /bin/bash -c "source /opt/ros/iron/setup.bash && \
#     cd /home/user1/ROSMonitoring/generator/ros2_devel && \
#     /home/user1/monitoring-python-env/bin/python generator --config_file  /home/user1/MOON/ModelMonitor/config_generator/monitor_BatteryLevelSkill.yaml && \
#     cd /home/user1/UC3/laboratory-tour/monitoring/monitor_skill_battery/src && \
#     colcon build"


# as2fm_scxml_to_jani --generated-scxml-dir model_low_level_dir main.xml

ENV PATH=${PATH}:/home/user1/.local/bin

ENV LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:/usr/local/src/robot/yarp/build/lib/


# mvn exec:java -Dexec.mainClass=io.github.convince.moon.Oracle -Dexec.args="--ioshape /home/user1/MOON/ModelMonitor/config_generator/BatteryLevelSkill_ioshape.json --statemachine /home/user1/UC3/laboratory-tour/model_scxml/BatteryLevelSkill.scxml --address 127.0.0.1:8081"

