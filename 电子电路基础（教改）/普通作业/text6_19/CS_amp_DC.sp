.title CS_amp_DC

.include 'CS_amp.cdl'

x1 GNDA VDDA vin vip vout Vbias CS_AMP
c10 vout 0 1p

vvdda VDDA 0 1.8
vgnda GNDA 0 0
vvbias Vbias 0 0.5
.param VCM=1 VD=0.1
vvin vin 0 VCM-VD/2
vvip vip 0 VCM+VD/2

.op				
.dc VD -0.3 0.3 0.005 VCM 0 2 0.2 	
										
.probe v(vout)												
												
.temp 27								
.option post accurate probe
.lib '..\models\ms018.lib' tt

.end

