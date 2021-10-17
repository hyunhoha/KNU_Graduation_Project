# KNU_Graduation_Project

##### Welcome to KNU project for graduation (Turtlebot serving robot)

## INSTALLATION

#### Ubuntu Linux (Recommended)

###### prerequisites
We used ROBOTIS-Turtlebot3 packages. (https://emanual.robotis.com/docs/en/platform/turtlebot3/overview/)

- 프로젝트가 turtlebot3에서 제공해주는 package를 사용하기 때문에, 관련 패키지를 설치해주어야 합니다.
- ros melodic (or noetic) install -> (http://wiki.ros.org/melodic/Installation/Ubuntu)
- ros turtlebot3 packages install -> (https://emanual.robotis.com/docs/en/platform/turtlebot3/quick-start/)
- 추가로, turtlebot3_gazebo(simulation), turtlebot3_navigation, turtlebot3_slam 패키지가 모두 필요합니다.

Open Terminal
``` sh
$ git clone https://github.com/hyunhoha/KNU_Graduation_Project.git -> knu_ws/src/knu_project만 복사해서 workspace/src 아래에 붙여넣기하시면 됩니다.
$ cd /path/to/your/catkin_workspace
$ catkin_make
$ source devel/setup.bash (Optional)
$ roscore
$ roslaunch knu_project navigation.launch
```

#### roslaunch로 실행하지 않는 경우 따로따로 실행법
```
$ roscore
$ roslaunch turtlebot3_gazebo turtlebot3_knu_cafe.launch // 이 전에, $ roscd turtlebot3_gazebo로 이동하여, cd launch, 다른 launch파일을 복사해서, knu_cafe.launch를 새로 만들고, arg parameter를 사용중인 cafe3.world로 바꾸어야 합니다.
$ roslaunch turtlebot3_navigation turtlebot3_navigation.launch map_file:={path/to/knu_project}/nav_map/cafe_map.yaml
$ rosrun knu_project key_navigation
```

roslaunch로 다같이 묶은 것입니다.

## How to contribute
#### Ubuntu Linux

Clone this repo 
```
$ git clone https://github.com/hyunhoha/KNU_Graduation_Project.git
$ cd KNU_Graduation_Project
```
Then, you can access this repo on your local environment.
Modify this repo (create, update, delete files)

1. Add the changes so that git can track changes. (git add를 통해 git이 변화를 인지할 수 있도록 해준다.)
2. Commit the changes with messages to reflect the changes. (변경사항을 반영하는데, 변경사항을 메시지로 기록해주세요. (무엇을 수정했는지))
3. Push changes to repository (수정사항을 git server에 반영합니다. 수행 결과 변경사항이 전체에 반영됩니다.)
```
$ git add .
$ git commit -m "what I've updated"
$ git push origin {main, or your branch} -> type your name and token
```

#### Windows
git cli 혹은 github desktop을 사용합니다.

### Branch에 관하여
main Branch가 메인
```
$ git branch {your new branch name} // make new branch
$ git switch {branch name} // move to other branch
```

- Github은 일종의 버전관리 툴입니다.
- main : version 1.0.1 -> version 1.0.2 -> ... version 1.3.2
- other branch : version 1.0.1 -> ...

###### 이런 식으로, Branch가 서로 다르면 서로간에 영향을 미치지 않습니다.
- commit, push할 때마다 각 Branch의 version은 새로 update됩니다.
- 파일이 망가져도, 이전 버전으로 되돌아갈 수 있기 때문에 관리가 쉽습니다.

각 Branch에서 파일을 수정하고, 다시 main Branch로 반영할 때는 Merge를 사용합니다.

Branch -> Balancing / Projection / navigation / other project ..


## 새로운 맵을 만들고 테스트해보기
새로 맵을 만들게 되면, 이를 Gazebo로 열고, turtlebot3_navigation node를 통해 map을 작성해야 합니다.

```
roscd turtlebot3_gazebo
cd launch
```
그리고, 

- 새로운 launch file을 만들고, arg에 새로 만든 맵 파일의 경로를 입력해줍니다.
- roslaunch turtlebot3_gazebo {새로 만든 launch file}로 실행합니다.
- roslaunch turtlebot3_slam turtlebot3_slam.launch
- roslaunch turtlebot3_teleop ~~~
 
하여 새로 맵을 만들고 저장해주고, knu_project 폴더 내의 launch파일을 새로 만들거나 수정하면 됩니다.











