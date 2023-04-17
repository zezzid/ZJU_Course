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
*　　　　参见PPT第26页

.title DIFF_AMP_DC

* with current mirror load
M1 5 1 6 0 n08 W=10U L=1U 
M2 2 3 6 0 n08 W=10U L=1U 
M3 5 5 4 4 p08 W=10U L=1U 
M4 2 5 4 4 p08 W=10U L=1U 
M5 6 7 0 0 n08 W=10U L=1U 
Vbias 7 0 DC=1.29

VDD 4 0 DC=5

.PARAM VCM=4.81			   *高于4.81V，M1/M2会进入线性区
Vin 1 0 DC=VCM 
Vip 3 0 DC=VCM 

.OP		                               *直流工作点仿真
.DC VCM 0 5 0.1                 *直流扫描仿真
.probe  i(m1)  

.option post probe

.MODEL n08 NMOS VTO = 0.70 KP = 110U GAMMA = 0.4  LAMBDA = 0.04 
+ PHI = 0.7 MJ = 0.5 MJSW = 0.38 CGBO = 700P CGSO = 220P CGDO = 220P 
+ CJ = 770U CJSW = 380P LD = 0.016U TOX = 14N
.MODEL p08 PMOS VTO = -0.70 KP = 50U GAMMA = 0.57 LAMBDA = 0.05 
+ PHI = 0.8 MJ = 0.5 MJSW = 0.35 CGBO = 700P CGSO = 220P CGDO = 220P 
+ CJ = 560U CJSW = 350P LD = 0.014U TOX = 14N

.end