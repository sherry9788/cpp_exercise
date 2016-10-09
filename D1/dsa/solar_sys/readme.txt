文件说明：
模拟太阳系上机报告.pdf		上机报告
正常模式.exe			一个已经编译好的版本
碰撞测试.exe			一个测试版本，在第二年有一次碰撞事件
TextureFragmentShader.fragmentshader
TextVertexShader.fragmentshader
TextVertexShader.vertexshader
TransformVertexShader.vertexshader
这四个文件OpenGL会用到
DDS				星球的贴图
src				源代码
sphere.obj			一个球体模型，OpenGL会用到
bucket.bat			桶结构会用到
Lagrange_Point.nb		计算拉格朗日点解析解的Mathematica文件
glew32.dll			动态链接库
glfw3.dll			动态链接库
msvcp140d.dll			动态链接库
ucrtbased.dll			动态链接库
vcruntime140d.dll		动态链接库
out.xls				输出文件
	
如果老师想编译src的文件的话，需要把
TextureFragmentShader.fragmentshader
TextVertexShader.fragmentshader
TextVertexShader.vertexshader
TransformVertexShader.vertexshader
sphere.obj
DDS
放到源文件目录下

一些快捷键：
方向键or WASD：
可以移动摄像机的position。
HJKL or 鼠标的移动：
可以移动视角。
Q：
加速摄像机移动的速度，摁住不放可以一直增加。
E：
减缓摄像机的移动速度，摁住不放则一直减小。
Z：
增大step。功能在下面介绍。
X：
减小step。功能在下面介绍。
N：
减小period。功能在下面介绍。
M：
增大period。功能在下面介绍。
，：
减小太阳质量。
。：
增大太阳质量。
C：
创建一个新的星体。可以选择创建的行星的名字、质量、半径、轨道半径、轨道类型、轨道倾角等等参数，这些会在console上提供选择。
V：
立即把当前所有行星的位置信息打印在console上。
F：
立刻把摄像机的position固定到某一星球上，此时WASD和方向键失去作用，摄像机随着某一星球运动而运动。可以运动视角。
R：
接触锁定，此时摄像机的position不再随某一星球运动。用户重新获得WASD和方向键的使用权。
P：
暂停计算。所有星球暂时静止，用户可以移动位置和视角。再按一次恢复。
