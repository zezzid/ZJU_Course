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
*　　　　参见PPT第29页

.title CS_AMP_DC

* with PMOS current source load
M1 2 1 0 0 n08 W=10U L=1U 
M2 2 4 3 3 p08 W=10U L=1U 
Vbias 4 0 DC=2.4
VDD 3 0 DC=5
Vin 1 0 DC=2

.OP		                               *直流工作点仿真
.DC Vin 0 5 0.1                    *直流扫描仿真
.probe v(2) v(1) i(M1)  

.option post probe

.MODEL n08 NMOS VTO = 0.70 KP = 110U GAMMA = 0.4  LAMBDA = 0.04 
+ PHI = 0.7 MJ = 0.5 MJSW = 0.38 CGBO = 700P CGSO = 220P CGDO = 220P 
+ CJ = 770U CJSW = 380P LD = 0.016U TOX = 14N
.MODEL p08 PMOS VTO = -0.70 KP = 50U GAMMA = 0.57 LAMBDA = 0.05 
+ PHI = 0.8 MJ = 0.5 MJSW = 0.35 CGBO = 700P CGSO = 220P CGDO = 220P 
+ CJ = 560U CJSW = 350P LD = 0.014U TOX = 14N

.end