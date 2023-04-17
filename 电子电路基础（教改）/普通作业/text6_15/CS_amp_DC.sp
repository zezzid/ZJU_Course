.title CS_amp_DC

.include 'CS_amp.cdl'

x1 GNDA VDDA VSS vin vout Vbias CS_AMP
c10 vout 0 1p

vvdda VDDA 0 1.8
vgnda GNDA 0 0
vvss VSS 0 -1.8
vvbias Vbias 0 -1.22
vvin vin 0 0.5

.op											
.tf v(vout) vvin				
.pz v(vout) vvin				
.dc vvin 0 1.8 0.02 		
												
.probe dc v(vin) v(vout)												
												
.temp 27								
.option post accurate probe
.lib '..\models\ms018.lib' tt

.end

