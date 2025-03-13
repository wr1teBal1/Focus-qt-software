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

## 设计(week 0)

写了一个简易的qt窗口，还没加上信号和槽，实现了点按高亮显示，急停按钮，模式切换

![截屏2025-03-13 12.33.08_副本](/Users/xuhengrui/Desktop/截屏2025-03-13 12.33.08_副本.png)

![截屏2025-03-13 12.34.03](/Users/xuhengrui/Desktop/截屏2025-03-13 12.34.03.png)
