待办事项作业工程文档

项目运行主页如下图所示：

<img src="https://cos-1301609895.cos.ap-nanjing.myqcloud.com/KingSummer/clipboard_20220713_125127.png" height=400 >

### 项目一：KingToDo待办事项

#### 一、项目架构

项目采用两层架构：view层（视图）和dao层（数据库操作接口），每一个关于数据库的操作都有相关接口

#### 二、项目整体设计规划

项目区域划分大致如上图所示

- 左上角`我的首页`和`我的待办`为两个按钮，按钮选中会有选中效果

- 分组使用ListWidget来存放，列表中的每个item都是自定义控件，下方按钮可以添加分组，添加分组弹窗如下所示，弹窗也是自定义窗口，使用信号与槽与主页面交互：

<img src="https://cos-1301609895.cos.ap-nanjing.myqcloud.com/KingSummer/clipboard_20220713_125419.png">



- 中间的StackWidget主要自己实现了三个页面：`首页`、`我的待办`和`分组待办`，下方显示的待办事项都是自定义控件，如下所示，选中每一个待办事项都会在右侧显示其详情
- 右侧是一个待办事项详情显示界面
- 排序功能由于时间原因暂时没做