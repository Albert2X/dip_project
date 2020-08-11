更新：
        视图：
	 新增单通道视图
        增强：
	新增撤销按键 （利用循环栈实现）
	新增亮度调节
	新增色调调节
	新增单通道分离
        滤波：
	初始ui里面的label为 setScaledContents(true);
	初始化ui里面的总布局 mainlayout ->setSizeConstraint(QLayout::SetNoConstraint);  
	以上两个初始化是为应对窗口显示过大无法正常显示的问题

注意：新增功能按钮未做语言转换功能，故不支持多语言