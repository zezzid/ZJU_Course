.title PMOS_AC

M1 2 1 0 0 n18 W=0.9u L=180n m=1
M2 2 3 4 4 p18 W=0.9u L=180n m=1
M3 3 3 4 4 p18 W=0.9u L=180n m=1
VDD 4 0 DC 1.8V
VGND 0 0 DC 0V
R1 3 0 120k
CL 2 0 1p
Vin 1 0 0.55 ac 1.0

.op

.ac dec 20 100 100meg
.noise v(2) Vin 10
.probe vdb(2) vp(2)
.probe inoise onoise

.temp 27
.option post accurate probe
.lib '..\models\ms018.lib' tt

.end