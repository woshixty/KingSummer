##### 作业简介

实现了一个Echo服务器，服务端和客户端可以进行双向通信，服务端发送的消息会转发到所有的已连接客户端

所有收到的消息都会显示消息来源

##### 运行截图

<img src="https://cos-1301609895.cos.ap-nanjing.myqcloud.com/KingSummer/clipboard_20220715_100952.png">



### 1、模块设计

#### （1）EchoClient

该模块下封装了KEchoClient的工具类

主要实现消息发送与接受的循环

#### （2）EchoServer

该模块下封装了KEchoServer的工具类，内封装有list（保存客户端连接的socket）

实现客户端连接和数据收发功能，每次发送数据都会转发到所有已连接客户端

#### （3）KUtils（lib静态库）

该模块主要提供公共处理工具类

##### a、Socket的封装

对服务端Socket（KSocketServer）和客户端Socket（KSocket）分别进行封装

- KSocket提供数据的收发的功能
- KSocketServer提供接受连接的功能

服务端的数据收发也会使用KSocket进行

##### b、KThread的封装

借鉴Java创建线程的思想

定义一个接口类`KRunnable`，里面有一个纯虚方法`virtual void runtask() = 0;`

`THread`接收一个`KRunnable`虚基类的实例对象，在`THread`中会创建一个线程执行该实例对象的`runtask()`方法

