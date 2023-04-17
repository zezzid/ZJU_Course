**************************************************
* 　　模拟电路基础——从系统级到电路级             *
**************************************************
* 　　　　　陈抗生　周金芳                       *
**************************************************
* 　　　　 科学出版社　2020                      *
**************************************************

.title CS_amp_TRAN

.include 'CS_amp.cdl'

x1 GNDA VDDA vin vout Vbias CS_AMP
c10 vout 0 1p

vvdda VDDA 0 1.8
vgnda GNDA 0 0
vvbias Vbias 0 1.2
vvin vin 0 sin(0.5 0.001 1k 0 0 0)

.tran 1u 5m					*瞬态仿真，步长1us，总时长5ms
.probe v(vin) v(vout)		*打印vin、vout节点电压

.temp 27						
.option post accurate probe
.lib '..\models\ms018.lib' tt

.end