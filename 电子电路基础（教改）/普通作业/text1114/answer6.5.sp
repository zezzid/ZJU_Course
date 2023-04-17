.title HW_chap6.5 
.param W1=5u
VVDS net2 0 DC 1.8V
VVGS net1 0 DC 0.75V
MNM0 net2 net1 0 0 n18 W=W1 L=180n m=1
.temp 27
.op
.dc VVDS 0 1.8 0.1 W1 5u 25u 5u
.lib '..\models\ms018.lib' tt
.option post accurate probe
.print v(net2) v(net1) Id=i(MNM0)
.print Gm=lx7(MNM0) Gds=lx8(MNM0) Cgs=lx20(MNM0) Cgd=par('-lx19(MNM0)')
.end