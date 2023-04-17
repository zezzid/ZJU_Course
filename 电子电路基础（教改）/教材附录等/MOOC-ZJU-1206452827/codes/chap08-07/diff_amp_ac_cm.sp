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
*　　　　参见PPT第23页

.title DIFF_AMP_AC

* with current mirror load
M1 5 1 6 0 n08 W=10U L=1U 
M2 2 1 6 0 n08 W=10U L=1U 
M3 5 5 4 4 p08 W=10U L=1U 
M4 2 5 4 4 p08 W=10U L=1U 
M5 6 7 0 0 n08 W=10U L=1U 
Vbias 7 0 DC=1.29

VDD 4 0 DC=5
CL 2 0 1P

.PARAM VCM=2  
Vin 1 0 DC=VCM AC=1

.OP		                               *直流工作点仿真
.AC dec 10 10 1g                *交流仿真
.probe vdb(2) vp(2)

.option post probe

.MODEL n08 NMOS VTO = 0.70 KP = 110U GAMMA = 0.4  LAMBDA = 0.04 
+ PHI = 0.7 MJ = 0.5 MJSW = 0.38 CGBO = 700P CGSO = 220P CGDO = 220P 
+ CJ = 770U CJSW = 380P LD = 0.016U TOX = 14N
.MODEL p08 PMOS VTO = -0.70 KP = 50U GAMMA = 0.57 LAMBDA = 0.05 
+ PHI = 0.8 MJ = 0.5 MJSW = 0.35 CGBO = 700P CGSO = 220P CGDO = 220P 
+ CJ = 560U CJSW = 350P LD = 0.014U TOX = 14N

.end