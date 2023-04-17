**************************************************
* 　　模拟电路基础——从系统级到电路级             *
**************************************************
* 　　　　　陈抗生　周金芳                       *
**************************************************
* 　　　　 科学出版社　2020                      *
**************************************************

.title CS_amp_DC

.include 'CS_amp.cdl'

x1 GNDA VDDA vin vout Vbias CS_AMP
c10 vout 0 1p

vvdda VDDA 0 1.8
vgnda GNDA 0 0
vvbias Vbias 0 1.2
vvin vin 0 0.5

.op											* 分析电路直流工作点
.tf v(vout) vvin				* 计算小信号传输函数
.pz v(vout) vvin				* 计算零极点
.dc vvin 0 1.8 0.02 		* 直流仿真，设置扫描变量，
												* 范围0-1.8V，步长为0.02V
.probe dc v(vin) v(vout)												
												
.temp 27								
.option post accurate probe
.lib '..\models\ms018.lib' tt

.end

