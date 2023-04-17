.title PMOS_DC

M1 2 1 0 0 n18 W=0.9u L=180n m=1
M2 2 3 4 4 p18 W=0.9u L=180n m=1
M3 3 3 4 4 p18 W=0.9u L=180n m=1
VDD 4 0 DC 1.8V
VGND 0 0 DC 0V
R1 3 0 120k
CL 2 0 1p
Vin 1 0 sin(0.5 0.001 1k 0 0 0)

.tran 1u 5m
.probe v(1) v(2)

.temp 27
.option post accurate probe
.lib '..\models\ms018.lib' tt

.end