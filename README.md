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

## 调研(week 0-1)
---
（被推翻的方案不予展示）

---
学长让我去学习QGC地面站的二次开发，这就开学，先学会了简单的app名字和图标修改

![1742046785594](https://github.com/user-attachments/assets/821908c5-b537-433b-86c4-7bbeec6794f4)

![8acbf29831d87443c0a94586087e400](https://github.com/user-attachments/assets/dedfea7b-b044-4628-ae14-d7a85aefdbe1)


![a2a77eb2cfab52bd9657ababeed4079](https://github.com/user-attachments/assets/7964e044-aa66-4bf1-b911-aa17744388b9)
![42a7d0981c6f80c16de2444e3cdae4e](https://github.com/user-attachments/assets/84c9b53f-1070-4471-94c0-60264b3502ec)


## 技术路线 week2 

通过调研与总结，我们的软件开发，路线大概为

- 需求分析
- 硬件接口确认
- 软件架构设计（包括新增陆行模式及状态机扩展）
- MAVLink协议扩展（或自定义消息） 
- QGC地面站定制 
- 仿真验证 
- 实际硬件调试 
- 优化完善

但大部分为控制组的同学们完成，所以上位机软件开发的流程为

### 理解并梳理接口与需求
#### 明确数据接口
与固件团队充分沟通，确定飞行模式切换及其他控制指令在MAVLink层面的实现情况。包括：
新增或修改的MAVLink消息格式和内容
预期的状态反馈和控制数据
#### 文档与接口说明
获取详细的接口文档、代码注释或设计文档，明确每个控制功能在数据传输和逻辑调用上的要求。
### 分析QGC架构与现有模块
#### 熟悉QGC代码结构
QGC基于Qt和C++开发，主要模块包括：
- MAVLink通信层：负责解析、生成和转发MAVLink消息
- 飞行模式及状态显示模块：用于展示当前飞行状态和控制选项
- UI模块：提供用户操作界面
- 定位修改点
找到当前处理飞行模式切换相关消息的代码区域，以及需要扩展或新增的UI部分，为后续修改和整合做好准备。
### 集成与开发步骤
#### 更新MAVLink解析
如果团队新增了自定义的MAVLink消息，需要：
更新QGC中的MAVLink消息定义
修改消息解析和处理逻辑，确保新增的消息能被正确识别、解析和响应
#### 扩展行走模式控制逻辑
在QGC中新增或修改飞行模式选择界面和状态反馈显示：
- UI层面：新增按钮、下拉菜单或其它控件，允许操作者选择新定义的飞行模式
- 逻辑层面：绑定这些UI控件到对应的MAVLink消息发送函数，同时处理从飞控返回的状态更新
#### 模块化集成
将团队其他成员完成的控制逻辑模块以插件或者模块化组件的形式整合到QGC中，确保：
模块接口清晰、独立
便于后续维护和单独测试
可与现有的QGC MAVLink通信框架无缝对接

### 开发与测试
#### 本地开发与调试
在本地搭建调试环境，使用PX4 SITL仿真或实际硬件环境测试：
验证新增飞行模式的命令是否正确发送
检查QGC界面能否实时显示状态变化和控制反馈
联调测试
与固件团队同步进行联调测试，确保上位机与飞控之间的数据交互无误：
重点关注飞行模式切换过程中的数据延时和错误处理
定期召开联调会议，及时发现并解决问题
### 跨平台
- 跨平台支持
QGC本身支持跨平台开发：
开发完成后，可以利用Qt打包生成Windows可执行程序，同时也可在Android或iOS平台上运行

### 关键在于：
- 接口对齐：明确和文档化MAVLink消息和控制接口。
- 代码整合：熟悉QGC架构，定位需要修改或扩展的模块，将新的控制逻辑模块化整合。
- 联调与测试：通过仿真和实际环境进行全面测试，确保数据传输、状态反馈和界面交互稳定可靠。
- 跨平台支持：利用Qt开发的优势生成Windows和移动端可执行软件，满足不同终端的操作需求。
- 按照这个流程逐步进行，不仅能确保功能正确集成，还能保持代码的可维护性和扩展性。

## 开发开始（week 3）

### 自定义MAVlink （成功）

1. 定义 XML 文件： 添加一个 text 的消息。
2. 生成代码： 使用 MAVLink 代码生成工具生成对应的 C 头文件。
3. 成 QGC： 将生成的头文件放入 QGC 的 MAVLink 目录，并在 QGC 的发送函数中调用打包函数构造消息。
4. 触发发送： 在 QML 中添加按钮，通过调用新接口来发送 text 的命令。
<img width="452" alt="07FBD11A-424D-4B8B-8BFE-5111CBD8BD7B" src="https://github.com/user-attachments/assets/2898e9a8-8d9b-4526-a294-5421053cdde6" />
