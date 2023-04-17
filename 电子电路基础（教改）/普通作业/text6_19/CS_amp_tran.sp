.title CS_amp_TRAN

.include 'CS_amp.cdl'

x1 GNDA VDDA vin vip vout Vbias CS_AMP
c10 vout 0 1p

vvdda VDDA 0 1.8
vgnda GNDA 0 0
vvbias Vbias 0 0.5
.param VCM=1 VD=0.1
vvin vin 0 sin(VCM -0.005 1k 0 0 0)
vvip vip 0 sin(VCM  0.005 1k 0 0 0)

.tran 5u 5m					
.probe v(vip) v(vin) v(vout)		

.temp 27						
.option post accurate probe
.lib '..\models\ms018.lib' tt

.end