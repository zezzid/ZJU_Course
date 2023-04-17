**************************************************
* 　　模拟电路基础——从系统级到电路级             *
**************************************************
* 　　　　　陈抗生　周金芳                       *
**************************************************
* 　　　　 科学出版社　2020                      *
**************************************************

.title OPA_CMRR

.include 'OPA.cdl'

x1 1 2 3 4 5 OPAMP
* 1 vip
* 2 vin
* 3 vout
* 4 VDD
* 5 VSS
VDD 4 0 DC  2.5 
VSS 0 5 DC  2.5
CL 3 0 10P
.PARAM VCM=1
VCM1 1 0 DC 0 AC VCM
VCM2 2 3 DC 0 AC VCM 

.ac dec 10 1 1g
.probe ac vdb(3) vp(3)
.probe ac cmrr_db=par('- vdb(3)') cmrr_phase=par('- vp(3)')
* Vout / Vcm = 1 / CMRR		Allen eq. 6.6-3, fig. 6.6-7
* cmrr_db = - (vdb(3))   	即，仅正负号区别
* cmrr_phase = - (vp(3))  即，仅正负号区别

.temp 27								
.option post accurate probe

.end