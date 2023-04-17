*-----------------------------------------------
* 　　　　模拟电路基础：                        
* 　　　　　　从系统级到电路级                  
*-----------------------------------------------
*　　　　陈抗生，周金芳                        
*　　　　科学出版社　2019                      
*-----------------------------------------------
*　　　　中国大学MOOC: 
*  https://www.icourse163.org/course/ZJU-1206452827
*-----------------------------------------------
*
*　　　　参见PPT第10页

.title OPAMP_open_loop

.include 'OPA.cdl'

X1 1 2 3 4 5 OPAMP
* 1 vip  * 2 vin  * 3 vout  * 4 VDD  * 5 VSS
VDD 4 0 DC  2.5
VSS 0 5 DC  2.5
vvip 1 0 DC 0 AC 1.0
vvin 2 0 DC 0
CL 3 0 10P

.OP										 * 直流工作点仿真

.DC vvip -0.005 0.005 100U * 直流扫描仿真
.probe dc v(3)						

.AC dec 10 10 1g                   * 交流仿真
.print ac vdb(3) vp(3)

.option post probe

.end