.title CS_amp_AC

.include 'CS_amp.cdl'

x1 GNDA VDDA vin vout Vbias CS_AMP
c10 vout 0 1p

vvdda VDDA 0 1.8
vgnda GNDA 0 0
vvbias Vbias 0 0.7
vvin vin 0 0.6 ac 1 0

.ac dec 10 10 1g			  
.noise v(vout) vvin 10	
.probe vdb(vout) vp(vout)		
.probe inoise onoise				

.temp 27								
.option post accurate probe
.lib '..\models\ms018.lib' tt

.end