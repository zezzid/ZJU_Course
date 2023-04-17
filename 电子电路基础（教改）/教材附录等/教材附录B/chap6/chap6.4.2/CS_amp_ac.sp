**************************************************
* 　　模拟电路基础——从系统级到电路级             *
**************************************************
* 　　　　　陈抗生　周金芳                       *
**************************************************
* 　　　　 科学出版社　2020                      *
**************************************************

.title CS_amp_AC

.include 'CS_amp.cdl'

x1 GNDA VDDA vin vout Vbias CS_AMP
c10 vout 0 1p

vvdda VDDA 0 1.8
vgnda GNDA 0 0
vvbias Vbias 0 1.2
vvin vin 0 0.5 ac 1 0

.ac dec 10 10 1g			  *交流仿真，从10Hz到1GHz，每10倍频程扫描10个点
.noise v(vout) vvin 10	*计算等效输出噪声和输入噪声
.probe vdb(vout) vp(vout)		*打印输出幅频特性
.probe inoise onoise				*打印输出噪声和等效输入噪声

.temp 27								
.option post accurate probe
.lib '..\models\ms018.lib' tt

.end