# KNU_Graduation_Project

##### Welcome to KNU project for graduation (Turtlebot serving robot)
## INSTALLATION

#### Ubuntu Linux (Recommended)

Open Terminal
``` sh
$ cd /path/to/your/catkin_workspace/src
$ git clone https://github.com/hyunhoha/KNU_Graduation_Project.git
$ cd /path/to/your/catkin_workspace
$ catkin_make
$ source devel/setup.bash (Optional)
$ roscore
$ roslaunch knu_project navigation.launch
```
We used ROBOTIS-Turtlebot3 packages. (https://emanual.robotis.com/docs/en/platform/turtlebot3/overview/)

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















