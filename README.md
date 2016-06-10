# SoftRender

## 简述
    一个软渲染器， 没有使用其他第三方库，功能简单，晚些补充说明

编译时提示这个错误的，请往下看  
Error	C4996	'strcpy': This function or variable may be unsafe. Consider using strcpy_s instead. To disable deprecation, use _CRT_SECURE_NO_WARNINGS. See online help for details.	MRender	c:\users\administrator\desktop\mrender-master\mrender-master\mrender\texture.c	9	

这个错误是由于VS添加了安全开发生命周期 (SDL) 检查导致的(准确的说是strcpy不够安全，被废弃了).解决方案如下3选一  
1.可以将strcpy替换为strcpy_s  
2.右键点击项目->属性->C/C++->预处理(Preprocessor)->第一项(Preprocessor Definition)->编辑->加入"_CRT_SECURE_NO_WARNINGS"  
3.右键点击项目->属性->C/C++->通用(Preprocessor)->SDL checks->关闭  

 我一般直接关闭  
 
## 联系方式
QQ: 648398613  
Email: 648398613@qq.com

 
