v 20110115 2
C 39200 39200 0 0 0 title-bordered-B.sym
T 51200 40300 9 20 1 0 0 0 1
USB power
T 49400 39500 9 10 1 0 0 0 1
4
T 51000 39500 9 10 1 0 0 0 1
5
T 49900 39800 9 10 1 0 0 0 1
power.sch
T 53000 39500 9 10 1 0 0 0 1
John Peck
C 39800 44800 1 0 0 usb_big_typeb.sym
{
T 39900 46800 5 10 1 1 0 0 1
refdes=J400
T 39900 47995 5 10 0 0 0 0 1
device=connector
T 39900 47795 5 10 0 0 0 0 1
footprint=usb_typeb_big.fp
}
C 50800 44800 1 0 0 2200n_x7r_50v_1206_vert.sym
{
T 50900 46200 5 10 0 0 0 0 1
footprint=1206_capacitor.fp
T 50900 46400 5 10 0 0 0 0 1
device=capacitor
T 51300 45200 5 10 1 1 0 0 1
value=2.2u
T 51300 45400 5 10 1 1 0 0 1
refdes=C401
}
N 49700 46300 51000 46300 4
N 48800 45400 48800 45100 4
N 47900 45100 47900 45200 4
N 47900 45200 48800 45200 4
N 47100 43800 51000 43800 4
N 51000 43800 51000 44800 4
N 47900 44000 47900 43800 4
N 48800 43900 48800 43800 4
N 47100 43200 47100 44800 4
N 46500 46300 47900 46300 4
C 53400 48700 1 0 0 3v3_pos.sym
N 49900 45900 49900 46300 4
N 49900 44700 49900 43800 4
C 47900 45400 1 0 0 lt3080est.sym
{
T 47895 47195 5 10 0 0 0 0 1
footprint=sot_223.fp
T 47895 47395 5 10 0 0 0 0 1
device=regulator
T 48195 46595 5 10 1 1 0 0 1
value=lt3080est
T 48195 46795 5 10 1 1 0 0 1
refdes=U400
}
N 49700 46000 49900 46000 4
T 48100 43500 9 10 1 0 0 0 1
Vout = Rset x 10uA
T 49000 42800 9 10 1 0 0 0 3
Minimum load current for lt3080
is 1mA (maximum).  Choose Rlmin
to flow this current.
T 53200 47000 9 10 1 0 0 0 4
The AVR Butterfly board requires
3.1V <= Vcc <= 4.5V, though the
ATmega169PA can run on
1.8V <= Vcc <= 5.5V.
T 48200 47200 9 10 1 0 0 0 3
lt3080 has a dropout
voltage of 1.2V with
100mA load.
C 46900 44800 1 0 0 1u0_x7r_50v_1206_vert.sym
{
T 47000 46400 5 10 0 0 0 0 1
device=capacitor
T 47400 45400 5 10 1 1 0 0 1
refdes=C400
T 47000 46200 5 10 0 0 0 0 1
footprint=1206_capacitor.fp
T 47400 45200 5 10 1 1 0 0 1
value=1.0u
}
C 47700 44000 1 0 0 1u0_x7r_50v_1206_vert.sym
{
T 47800 45600 5 10 0 0 0 0 1
device=capacitor
T 48200 44600 5 10 1 1 0 0 1
refdes=C402
T 47800 45400 5 10 0 0 0 0 1
footprint=1206_capacitor.fp
T 48200 44400 5 10 1 1 0 0 1
value=1.0u
}
T 39800 47100 9 10 1 0 0 0 2
4.75 < Vbus < 5.25
for high-current USB
C 44400 46600 1 0 0 testpoint.sym
{
T 44400 47750 5 10 0 0 0 0 1
footprint=testpoint.fp
T 44400 47950 5 10 0 0 0 0 1
device=connector
T 44400 47350 5 10 0 0 0 0 1
value=red
T 44650 47150 5 10 1 1 0 0 1
refdes=TP400
T 44650 46964 5 10 1 1 0 0 1
label=Vbus
}
C 54400 48500 1 0 0 testpoint.sym
{
T 54400 49650 5 10 0 0 0 0 1
footprint=testpoint.fp
T 54400 49850 5 10 0 0 0 0 1
device=connector
T 54400 49250 5 10 0 0 0 0 1
value=red
T 54650 49050 5 10 1 1 0 0 1
refdes=TP401
T 54650 48864 5 10 1 1 0 0 1
label=+3.3V
}
N 51000 46500 52300 46500 4
T 49000 44200 9 10 1 0 0 0 1
Rset
T 50100 45000 9 10 1 0 0 0 1
Rlmin
C 40900 40200 1 0 0 2pin_mta100_header_in.sym
{
T 40900 41600 5 10 0 0 0 0 1
footprint=2pin_mta100_pol.fp
T 40900 41800 5 10 0 0 0 0 1
device=connector
T 40900 40200 5 10 1 1 0 0 1
value=mta100
T 40900 41100 5 10 1 1 0 0 1
refdes=J403
}
T 41800 40800 9 10 1 0 0 0 1
J401:10
T 41800 40400 9 10 1 0 0 0 1
J401:9
T 40900 41400 9 10 1 0 0 0 2
Solder connector to make Vcc_ext
connection on Butterfly board.
C 46900 42800 1 0 0 gnd_ana.sym
C 53300 41200 1 0 0 gnd_ana.sym
N 53500 41600 53500 41900 4
C 43300 43700 1 0 0 led_green_1206_vert.sym
{
T 43400 45400 5 10 0 0 0 0 1
device=led
T 43400 45200 5 10 0 0 0 0 1
footprint=1206_led.fp
T 43900 44100 5 10 1 1 180 8 1
value=green
T 43900 44300 5 10 1 1 180 8 1
refdes=D400
}
C 43400 45000 1 0 0 180r_1206_vert.sym
{
T 43400 46700 5 10 0 0 0 0 1
footprint=1206_resistor.fp
T 43400 46900 5 10 0 0 0 0 1
device=resistor
T 43700 45500 5 10 1 1 0 0 1
value=180
T 43700 45700 5 10 1 1 0 0 1
refdes=R402
}
C 43300 46700 1 0 0 vbus.sym
C 43300 42800 1 0 0 gnd_bus.sym
N 47100 45900 47100 46300 4
N 46500 43400 47100 43400 4
N 43500 43700 43500 43200 4
N 45300 43400 43500 43400 4
N 43500 45000 43500 44800 4
N 43500 46700 43500 46200 4
N 45300 46300 43500 46300 4
N 44500 46600 44500 46300 4
N 42000 46500 43500 46500 4
C 40500 44000 1 0 0 gnd_bus.sym
N 40700 44800 40700 44400 4
N 42000 45600 42000 44600 4
N 42000 44600 40700 44600 4
T 39800 43200 9 10 1 0 0 0 3
USB 2 can draw 100mA
before it needs to be
configured by a host.
C 49800 44700 1 0 0 3k30_1206_vert.sym
{
T 49800 46400 5 10 0 0 0 0 1
footprint=1206_resistor.fp
T 49800 46600 5 10 0 0 0 0 1
device=resistor
T 50100 45200 5 10 1 1 0 0 1
value=3.3k
T 50100 45400 5 10 1 1 0 0 1
refdes=R403
}
C 48700 43900 1 0 0 330k_1206_vert.sym
{
T 48700 45600 5 10 0 0 0 0 1
footprint=1206_resistor.fp
T 48700 45800 5 10 0 0 0 0 1
device=resistor
T 49000 44400 5 10 1 1 0 0 1
value=330k
T 49000 44600 5 10 1 1 0 0 1
refdes=R405
}
C 53400 41900 1 0 0 testpoint_big.sym
{
T 53400 43050 5 10 0 0 0 0 1
footprint=testpoint_big.fp
T 53400 43250 5 10 0 0 0 0 1
device=connector
T 53400 42650 5 10 0 0 0 0 1
value=white
T 53650 42450 5 10 1 1 0 0 1
refdes=TP402
T 53650 42264 5 10 1 1 0 0 1
label=0V_ana
}
C 54200 45800 1 0 0 2pin_mta100_header_out.sym
{
T 54200 47100 5 10 0 0 0 0 1
footprint=2pin_mta100_pol.fp
T 54200 47300 5 10 0 0 0 0 1
device=connector
T 54500 45800 5 10 1 1 0 0 1
value=mta100
T 54500 46700 5 10 1 1 0 0 1
refdes=J401
}
C 54000 45200 1 0 0 gnd_ana.sym
N 53500 46500 54200 46500 4
N 54200 46100 54200 45600 4
C 54200 43800 1 0 0 2pin_mta100_header_out.sym
{
T 54200 45100 5 10 0 0 0 0 1
footprint=2pin_mta100_pol.fp
T 54200 45300 5 10 0 0 0 0 1
device=connector
T 54500 43800 5 10 1 1 0 0 1
value=mta100
T 54500 44700 5 10 1 1 0 0 1
refdes=J402
}
C 54000 43300 1 0 0 gnd_ana.sym
N 54200 44100 54200 43700 4
N 53500 44500 54200 44500 4
N 52000 46500 52000 44500 4
N 52000 44500 52300 44500 4
T 53000 39800 9 10 1 0 0 0 1
B
C 50600 41100 1 0 0 2pin_mta100_white_recept.sym
{
T 51000 41800 5 10 1 1 0 0 1
refdes=MECH400
T 50600 42150 5 10 0 0 0 0 1
device=connector
T 51000 41600 5 10 1 1 0 0 1
value=mta100
T 51000 41400 5 10 1 1 0 0 1
description=2-pin, white
T 51000 41200 5 10 1 1 0 0 1
comment=24-guage stranded
}
C 48400 41100 1 0 0 2pin_mta100_white_recept.sym
{
T 48800 41800 5 10 1 1 0 0 1
refdes=MECH401
T 48400 42150 5 10 0 0 0 0 1
device=connector
T 48800 41600 5 10 1 1 0 0 1
value=mta100
T 48800 41400 5 10 1 1 0 0 1
description=2-pin, white
T 48800 41200 5 10 1 1 0 0 1
comment=24-guage stranded
}
C 51500 46200 1 0 0 0m_1206_horz.sym
{
T 51500 47700 5 10 0 0 0 0 1
device=resistor
T 52800 46700 5 10 1 1 0 0 1
refdes=R400
T 51500 47500 5 10 0 0 0 0 1
footprint=1206_resistor.fp
T 52800 46200 5 10 1 1 0 0 1
value=0.0
}
C 51500 44200 1 0 0 0m_1206_horz.sym
{
T 51500 45700 5 10 0 0 0 0 1
device=resistor
T 52800 44700 5 10 1 1 0 0 1
refdes=R404
T 51500 45500 5 10 0 0 0 0 1
footprint=1206_resistor.fp
T 52800 44200 5 10 1 1 0 0 1
value=0.0
}
C 44500 46000 1 0 0 0m_1206_horz.sym
{
T 44500 47500 5 10 0 0 0 0 1
device=resistor
T 45800 46500 5 10 1 1 0 0 1
refdes=R401
T 44500 47300 5 10 0 0 0 0 1
footprint=1206_resistor.fp
T 45800 46000 5 10 1 1 0 0 1
value=0.0
}
C 44500 43100 1 0 0 0m_1206_horz.sym
{
T 44500 44600 5 10 0 0 0 0 1
device=resistor
T 45800 43600 5 10 1 1 0 0 1
refdes=R406
T 44500 44400 5 10 0 0 0 0 1
footprint=1206_resistor.fp
T 45800 43100 5 10 1 1 0 0 1
value=0.0
}
N 51000 45900 51000 48500 4
C 51500 48200 1 0 0 0m_1206_horz.sym
{
T 51500 49700 5 10 0 0 0 0 1
device=resistor
T 52700 48700 5 10 1 1 0 0 1
refdes=R407
T 51500 49500 5 10 0 0 0 0 1
footprint=1206_resistor.fp
T 52800 48200 5 10 1 1 0 0 1
value=0.0
}
N 51000 48500 52300 48500 4
N 53500 48500 54500 48500 4
N 53800 48700 53800 48500 4
C 50900 48500 1 0 0 testpoint.sym
{
T 50900 49650 5 10 0 0 0 0 1
footprint=testpoint.fp
T 50900 49850 5 10 0 0 0 0 1
device=connector
T 50900 49250 5 10 0 0 0 0 1
value=red
T 51150 49050 5 10 1 1 0 0 1
refdes=TP403
T 51150 48864 5 10 1 1 0 0 1
label=Vreg
}
T 47100 48100 9 10 1 0 0 0 3
lt3080 in SOT-223 package has
junction-to-ambient tempco of
55 C/W, 125C max junction temp.
T 52300 45400 9 10 1 0 0 0 2
100mA max output
limited by USB
