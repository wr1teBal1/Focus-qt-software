# Focus-qt-software
Focus基于qt开发的陆空两栖机器人上位机人机交互软件开发日志software
## 声明：
- 本人为毫无硬软件实际应用知识的大一小登
- 进度过慢请学长们多多包涵
- 求指导！！！
## 第一步 调研
- 学长说先不用着急学习基础知识
- 先去学习大家是怎么开发这样的软件的
- 然后给出一个大致的研发路程
- 所以我的第一步是做一下调研
- 做出详细的开发思维导图
- 然后重点各个击破
### Week 0
- 在github上遍历了中文的此类开源项目，可是大多star数极少
- 放到下面，可能有点用处
---
- [这个是开发完成度较高的一款](https://github.com/chengyangkj/Ros_Qt5_Gui_App)
- [一个基于Qt 的机器人上位机控制系统(定位、地图标记、轨迹显示、控制、实时视频、热感视频等)](https://github.com/xpxh1724/Sony-Rescue_robot)
- [ROS安防机器人的上位控制软件，使用QT编写](https://github.com/Nyar-D/RobotUpperControl)
- [灯哥开源的菠萝动力开源四足控制软件（Py-Apple Dynamics ），集成了开发四足机器人所需要必须基础库，是一套完整的全开源的四足机器人控制软件程序。](https://github.com/ToanTech/py-apple-dynamics)
- [基于Qt开发环境，开发运用于双并联机器人的人机交互软件，实现控制器参数配置，编码器数据的实时反馈，并联机器人的参数设置、基于点位运动模式进行电机位置控制，多线程控制6个电机](https://github.com/lynnllh/3PRRGUI)
- [扫地机器人Qt上位机](https://github.com/confidentFeng/cleanRobot)
---
接下来是Google下来的文章
- [Qt与机器人控制](https://modstart.com/p/v7bmw0863pdyogyp)
- [想骂人了，这个🔗是qt用ros开发的全流程，可是不给看QWQ](https://blog.csdn.net/XrxVue/article/details/133618933)
- [感觉这个文章很重要，基础的ros和qt链接](https://my.oschina.net/emacs_8809069/blog/17313941)
## 开发流程

1. **设计**
   - 确定机器人的功能需求
   - 设计gui
2. **实现**
   - 编写 ROS 2 节点代码
   - 使用 Qt 设计用户界面
3. **测试**
   - 在 macOS 上测试功能
   - 使用模拟器或实际硬件验证
4. **部署**
   - 将代码部署到目标 Linux 系统
   - 进行集成测试和性能优化

## 调研(week 0-1)
---
（被推翻的方案）

写了一个简易的qt窗口，还没加上信号和槽，实现了点按高亮显示，急停按钮，模式切换
<img width="1189" alt="截屏2025-03-13 12 33 08" src="https://github.com/user-attachments/assets/705fa228-0e20-4a12-8175-694847b9f1a6" />
<img width="1227" alt="截屏2025-03-13 12 34 03" src="https://github.com/user-attachments/assets/1d29a6a3-101d-45c1-be0e-bb800205735c" />
---
学长让我去学习QGC地面站的二次开发，这就开学，先学会了简单的app名字和图标修改

![1742046785594](https://github.com/user-attachments/assets/821908c5-b537-433b-86c4-7bbeec6794f4)

![8acbf29831d87443c0a94586087e400](https://github.com/user-attachments/assets/dedfea7b-b044-4628-ae14-d7a85aefdbe1)


![a2a77eb2cfab52bd9657ababeed4079](https://github.com/user-attachments/assets/7964e044-aa66-4bf1-b911-aa17744388b9)
![42a7d0981c6f80c16de2444e3cdae4e](https://github.com/user-attachments/assets/84c9b53f-1070-4471-94c0-60264b3502ec)
### 控制模式
无人系统的控制模式可以分为直接控制模式和间接控制模式。直接控制模式下，底层
控制器（自驾仪、飞控板）响应遥控系统和地面控制系统的指令，去完成特定的任务。直
接控制模式通常采用无线通信的方案，受到通信带宽和延迟的限制，通常只能传递简单的
指令（遥控信号、起飞降落命令、航路飞行命令等）给底层控制器，最终由后者去完成载
具的任务控制。而间接控制模式下，机载可控制系统和底层控制器都装载在载具上，可以
通过有线方式进行高速传数，因此机载控制系统可以发送更高频率的控制指令，获得更高
的控制权限，例如可以直接实时控制载具的速度、姿态、加速度、角速度等。
### 控制接口使用
外部控制中根据控制的方式和工具的不同可以分为：遥控操控、Mavlink 通信、
Pymavlink、Mavsdk、Mavros、ROS1/2 几种方式。同时，结合 MATLAB/Simulink 中的中上
层控制算法库，实现轨迹规划和控制指令的输出。

PS:Pixhawk2.4.8开发常用地面站为misson planer，之后版本的常用为QGC（QGroundControl）。


