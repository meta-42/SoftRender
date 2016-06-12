# SoftRender

## 简述

一个光栅化软件渲染器


## 功能
* obj格式模型文件解析
* bmp格式贴图文件解析
* 背面剔除(Backface Culling)
* 透视纹理矫正(Perspective Texture Mapping）
* 视域剔除（View Frustum Culling）
* 中点画线法
* Z-Buffer算法
* 基于左手坐标系，行向量的3D数学库
* 提供4种渲染状态（顶点，线框，贴图，颜色填充）
* 光照（点光源）
* Gouraud Shading
* 支持到256*256纹理
* 扫描线填充算法
* 基于斜率的三角形划分算法

## Example

    //渲染器初始化
    if (engine_init(viewport_width, viewport_height, title) == MRE_INIT_SUCCEED)
    {
        //do something
        engine_start(&tick);
    }

    //摄像机
	float aspect = viewport_width / viewport_height;
	float fovy = PI / 2.f;
	float clip_near = 1.f;
	float clip_far = 500.f;
	camera = *camera_create_perspective(fovy, aspect, clip_near, clip_far);
	Vector3 eye = { 0.f,0.f,-1.f }, lookat = { 0.f, 0.f, 0.f }, up = { 0.f, 1.f,0.f };
	camera_lookat(&camera, eye, lookat, up);
	renderdev_set_camera(&mre.renderdev, camera);

    //模型
    mesh = *mesh_create("mono.obj", "mono.bmp");
    Vector3 position = vector3_zero();
    mesh_set_position(&mesh, position);
    Vector3 rotation = vector3_zero();
    mesh_set_rotation(&mesh, rotation);

    //灯光
    Vector3 position2 = { 0, 10,10 };
    Color col = { 1,1,1 };
    Light light = *light_create_point(col, position2);
    renderdev_set_light(&mre.renderdev, light);

# 常见问题

假如编译时提示这个错误的，请往下看  
Error	C4996	'strcpy': This function or variable may be unsafe. Consider using strcpy_s instead. To disable deprecation, use _CRT_SECURE_NO_WARNINGS. See online help for details.

这个错误是由于VS添加了安全开发生命周期 (SDL) 检查导致的(准确的说是strcpy不够安全，被废弃了).解决方案如下3选一  
1. 可以将strcpy替换为strcpy_s  
2. 右键点击项目->属性->C/C++->预处理(Preprocessor)->第一项(Preprocessor Definition)->编辑->加入"_CRT_SECURE_NO_WARNINGS"  
3. 右键点击项目->属性->C/C++->通用(Preprocessor)->SDL checks->关闭  


我一般直接关闭  

## 联系方式
QQ: 648398613  
Email: 648398613@qq.com
