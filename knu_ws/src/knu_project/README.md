### knu_project Details

#### Map에 관하여

- 현재 사용중인 map은 worlds/cafe3.world 파일입니다.
- 수정 시, worlds/ 폴더에서, gazebo cafe3.world로 열고, 왼쪽 manu에서 insert하여 이미 만들어진 모델을 추가할 수 있습니다.
- 또한, model editor로 직접 모델을 만들어서 추가할 수도 있습니다.
- 혹은, Gazebo Tutorial에서 world파일에서 직접 모델을 추가하는 방법 : http://gazebosim.org/tutorials?tut=build_model 
- 맵 수정 후, Save world를 통해 저장해주시면 됩니다.

#### 실행할 때 Map 변경 방법
- launch/ 폴더에 navigation.launch 파일에서, empty_world.launch 파일 include하는 부분에서 arg의 world_name을 수정해주면 됩니다.

#### roslaunch로 실행하지 않는 경우 따로따로 실행법
```
$ roscore
$ roslaunch turtlebot3_gazebo turtlebot3_knu_cafe.launch
$ roslaunch turtlebot3_navigation turtlebot3_navigation.launch map_file:={path/to/knu_project}/nav_map/cafe_map.yaml
$ rosrun knu_project key_navigation
```

roslaunch로 다같이 묶은 것입니다.

world파일에서 각 Table의 좌표를 <Pose> 태그에서 확인할 수 있습니다.
.py 파일은 /src 폴더에 만들고, chmod +x로 실행권한을 주면 catkin_make 없이도 알아서 인식합니다.

