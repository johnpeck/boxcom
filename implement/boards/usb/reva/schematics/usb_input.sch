v 20110115 2
C 39200 39200 0 0 0 title-bordered-B.sym
T 51200 40300 9 20 1 0 0 0 1
USB input
T 49400 39500 9 10 1 0 0 0 1
1
T 51000 39500 9 10 1 0 0 0 1
5
T 49700 39800 9 10 1 0 0 0 1
usb_input.sch
T 53000 39500 9 10 1 0 0 0 1
John Peck
C 43500 43800 1 0 0 usb_big_typeb.sym
{
T 43600 45800 5 10 1 1 0 0 1
refdes=J400
T 43600 46995 5 10 0 0 0 0 1
device=connector
T 43600 46795 5 10 0 0 0 0 1
footprint=usb_typeb_big.fp
}
T 43500 46100 9 10 1 0 0 0 2
4.75 < Vbus < 5.25
for high-current USB
C 50700 46200 1 0 0 testpoint.sym
{
T 50700 47350 5 10 0 0 0 0 1
footprint=testpoint.fp
T 50700 47550 5 10 0 0 0 0 1
device=connector
T 50700 46950 5 10 0 0 0 0 1
value=red
T 50950 46750 5 10 1 1 0 0 1
refdes=TP400
T 50950 46564 5 10 1 1 0 0 1
label=Vbus
}
C 44200 43000 1 0 0 gnd_bus.sym
N 44400 43800 44400 43400 4
N 45700 44600 45700 43600 4
N 44400 43600 50600 43600 4
T 43500 46700 9 10 1 0 0 0 3
USB 2 can draw 100mA
before it needs to be
configured by a host.
T 53000 39800 9 10 1 0 0 0 1
A
C 49000 45700 1 0 0 bead_50ohm_6a_1206.sym
{
T 49400 46200 5 10 1 1 0 0 1
refdes=FB400
T 49000 45700 5 10 1 1 0 0 1
value=50ohm at 100MHz
}
C 50400 44000 1 0 0 10n_x7r_50v_1206_vert.sym
{
T 50900 44600 5 10 1 1 0 0 1
refdes=C403
T 50900 44400 5 10 1 1 0 0 1
value=10n
}
N 50600 44000 50600 43600 4
N 50600 45100 50600 46000 4
T 44200 42500 9 10 1 0 0 0 2
"bus" ground will be connected
to the chassis.
N 50800 46200 50800 46000 4
N 45700 45500 45700 46000 4
N 45700 45200 48400 45200 4
N 45700 44900 48400 44900 4
C 40400 41700 1 0 0 4_40_mthole_fat.sym
{
T 41200 41700 5 10 1 1 0 0 1
value=4-40 fat
T 41200 41900 5 10 1 1 0 0 1
refdes=HOLE400
}
C 39900 41300 1 0 0 gnd_bus.sym
N 40400 41900 40100 41900 4
N 40100 41700 40100 42200 4
C 39900 40100 1 0 0 gnd_bus.sym
C 41300 40100 1 0 0 gnd_ana.sym
C 39400 40400 1 0 0 0m_1206_horz.sym
{
T 40700 40900 5 10 1 1 0 0 1
refdes=R?
T 40700 40400 5 10 1 1 0 0 1
value=0.0
}
N 40200 40700 40100 40700 4
N 40100 40700 40100 40500 4
N 41400 40700 41500 40700 4
N 41500 40700 41500 40500 4
T 40000 39600 9 10 1 0 0 0 2
Analog to USB/chassis ground
star point.
C 51600 43300 1 0 0 led_green_1206_vert.sym
{
T 51700 45000 5 10 0 0 0 0 1
device=led
T 51700 44800 5 10 0 0 0 0 1
footprint=1206_led.fp
T 52200 43700 5 10 1 1 180 8 1
value=green
T 52200 43900 5 10 1 1 180 8 1
refdes=D400
}
C 51700 44600 1 0 0 180r_1206_vert.sym
{
T 51700 46300 5 10 0 0 0 0 1
footprint=1206_resistor.fp
T 51700 46500 5 10 0 0 0 0 1
device=resistor
T 52000 45100 5 10 1 1 0 0 1
value=180
T 52000 45300 5 10 1 1 0 0 1
refdes=R402
}
C 51600 42400 1 0 0 gnd_bus.sym
N 51800 43300 51800 42800 4
N 51800 44600 51800 44400 4
N 50300 46000 51800 46000 4
N 51800 45800 51800 46300 4
C 51600 46300 1 0 0 vbus.sym
L 42900 41400 42900 40900 3 0 0 0 -1 -1
L 42900 40900 43400 40900 3 0 0 0 -1 -1
L 43400 40900 43400 41400 3 0 0 0 -1 -1
L 43400 41400 42900 41400 3 0 0 0 -1 -1
L 43500 41400 43500 40900 3 0 0 0 -1 -1
L 43500 41400 43450 41350 3 0 0 0 -1 -1
L 43500 41400 43550 41350 3 0 0 0 -1 -1
L 43500 40900 43450 40950 3 0 0 0 -1 -1
L 43500 40900 43550 40950 3 0 0 0 -1 -1
T 43600 41100 9 10 1 0 0 0 1
0.5
L 42900 40800 43400 40800 3 0 0 0 -1 -1
L 42900 40800 42950 40750 3 0 0 0 -1 -1
L 42900 40800 42950 40850 3 0 0 0 -1 -1
L 43400 40800 43350 40750 3 0 0 0 -1 -1
L 43400 40800 43350 40850 3 0 0 0 -1 -1
T 43000 40600 9 10 1 0 0 0 1
0.5
T 42900 41500 9 10 1 0 0 0 3
Panel cutout for
USB.  0.5-inch square
punch is 16-39.
L 45100 41500 45600 41500 3 0 0 0 -1 -1
L 45600 41500 45600 40700 3 0 0 0 -1 -1
L 45600 40700 45100 40700 3 0 0 0 -1 -1
L 45100 40700 45100 41500 3 0 0 0 -1 -1
L 45700 41500 45700 40700 3 0 0 0 -1 -1
L 45700 41500 45650 41450 3 0 0 0 -1 -1
L 45700 41500 45750 41450 3 0 0 0 -1 -1
L 45700 40700 45650 40750 3 0 0 0 -1 -1
L 45700 40700 45750 40750 3 0 0 0 -1 -1
L 45100 40600 45600 40600 3 0 0 0 -1 -1
L 45100 40600 45150 40550 3 0 0 0 -1 -1
L 45100 40600 45150 40650 3 0 0 0 -1 -1
L 45600 40600 45550 40550 3 0 0 0 -1 -1
L 45600 40600 45550 40650 3 0 0 0 -1 -1
T 45200 40400 9 10 1 0 0 0 1
0.5
T 45800 41100 9 10 1 0 0 0 1
0.76
T 45000 41800 9 10 1 0 0 0 2
Panel cutout for
21-1 switch.
C 45000 47700 1 0 0 150r_1206_horz.sym
{
T 46300 48200 5 10 1 1 0 0 1
refdes=R?
T 46300 47700 5 10 1 1 0 0 1
value=150
}
C 39600 48300 1 0 0 switch_green_rocker.sym
{
T 40200 48800 5 10 1 1 0 0 1
refdes=MECH?
T 40200 48600 5 10 1 1 0 0 1
value=Green rocker SPST
}
C 48400 45100 1 0 0 output_right.sym
{
T 49400 45150 5 10 1 1 0 0 1
net=Dminus:1
}
C 48400 44800 1 0 0 output_right.sym
{
T 49400 44850 5 10 1 1 0 0 1
net=Dplus:1
}
C 44100 47600 1 0 0 4pin_mta100_header_in.sym
{
T 44100 47600 5 10 1 1 0 0 1
value=mta100
T 44100 49300 5 10 1 1 0 0 1
refdes=J?
}
C 44900 47400 1 0 0 gnd_bus.sym
C 47200 48000 1 0 0 vbus.sym
N 44900 47900 45100 47900 4
N 45100 47900 45100 47800 4
N 44900 48700 48100 48700 4
N 48100 48700 48100 46000 4
N 44900 49100 48400 49100 4
N 48400 49100 48400 46000 4
N 48400 46000 49100 46000 4
N 48100 46000 45700 46000 4
N 45800 48000 45500 48000 4
N 45500 48000 45500 48300 4
N 44900 48300 45500 48300 4
N 47000 48000 47400 48000 4
C 42000 48200 1 0 0 4pin_mta100_white_recept.sym
{
T 42400 48900 5 10 1 1 0 0 1
refdes=MECH?
T 42400 48700 5 10 1 1 0 0 1
value=mta100
T 42400 48500 5 10 1 1 0 0 1
description=4-pin, white
T 42400 48300 5 10 1 1 0 0 1
comment=24-guage stranded
}
C 40000 42200 1 0 0 testpoint_big.sym
{
T 40250 42750 5 10 1 1 0 0 1
refdes=TP?
T 40250 42564 5 10 1 1 0 0 1
label=0V_bus
}
