.title CS_amp_AC

.include 'CS_amp.cdl'

x1 GNDA VDDA vin vip vout Vbias CS_AMP
c10 vout 0 1p

vvdda VDDA 0 1.8
vgnda GNDA 0 0
vvbias Vbias 0 0.5
.param VCM=1 VD=0.1
vvin vin 0 DC VCM AC VD/2 -180
vvip vip 0 DC VCM AC VD/2

.ac dec 10 10 1g			  
.probe vdb(vout) vp(vout)				

.temp 27								
.option post accurate probe
.lib '..\models\ms018.lib' tt

.end