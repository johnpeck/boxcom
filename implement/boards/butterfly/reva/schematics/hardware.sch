v 20121123 2
C 45900 55200 1 0 0 2pin_mta100_white_recept.sym
{
T 46300 55900 5 10 1 1 0 0 1
refdes=MECH113
T 45900 56250 5 10 0 0 0 0 1
device=connector
T 46300 55700 5 10 1 1 0 0 1
value=mta100
T 46300 55500 5 10 1 1 0 0 1
description=2-pin, white
T 46300 55300 5 10 1 1 0 0 1
comment=24-guage stranded
}
C 48000 55200 1 0 0 2pin_mta100_white_recept.sym
{
T 48400 55900 5 10 1 1 0 0 1
refdes=MECH114
T 48000 56250 5 10 0 0 0 0 1
device=connector
T 48400 55700 5 10 1 1 0 0 1
value=mta100
T 48400 55500 5 10 1 1 0 0 1
description=2-pin, white
T 48400 55300 5 10 1 1 0 0 1
comment=24-guage stranded
}
C 53500 56800 1 0 0 6pin_avr_isp.sym
{
T 53500 58600 5 10 0 0 0 0 1
device=connector
T 53500 58400 5 10 0 0 0 0 1
footprint=hdr_100p_3c_2r.fp
T 54800 56800 5 10 1 1 0 0 1
value=6pin ISP
T 54495 58070 5 10 1 1 0 0 1
refdes=J102
}
C 45200 50900 0 0 0 title-bordered-B.sym
T 55900 52000 9 20 1 0 0 0 1
Butterfly hardware
T 55500 51200 9 12 1 0 0 0 1
1
T 56900 51200 9 12 1 0 0 0 1
1
T 58900 51500 9 10 1 0 0 0 1
A
T 59100 51200 9 12 1 0 0 0 1
John R Peck
T 55600 51500 9 12 1 0 0 0 1
hardware.sch
T 53100 60700 9 10 1 0 0 0 2
AVR Butterfly requires
3.1V <= Vcc <= 4.5V
C 50200 57000 1 0 0 3pin_mta100_header_in_ra.sym
{
T 50200 59000 5 10 0 0 0 0 1
footprint=2pin_mta100_pol_ra.fp
T 50200 59200 5 10 0 0 0 0 1
device=connector
T 50200 57200 5 10 1 1 0 0 1
value=mta100
T 50200 58500 5 10 1 1 0 0 1
refdes=J101
T 50200 57000 5 10 1 1 0 0 1
comment=Right angle
}
C 48000 57400 1 0 0 3pin_mta100_white_recept.sym
{
T 48400 58100 5 10 1 1 0 0 1
refdes=MECH112
T 48000 58450 5 10 0 0 0 0 1
device=connector
T 48400 57900 5 10 1 1 0 0 1
value=mta100
T 48400 57700 5 10 1 1 0 0 1
description=3-pin, white
T 48400 57500 5 10 1 1 0 0 1
comment=24-guage stranded
}
C 53200 58400 1 0 0 avr_butterfly.sym
{
T 55900 59700 5 10 0 0 0 0 1
device=butterfly
T 53200 60200 5 10 1 1 0 0 1
refdes=MECH104
T 53200 60000 5 10 1 1 0 0 1
value=AVR Butterfly
}
C 59400 56200 1 0 0 led_red_t1_vert.sym
{
T 60000 56600 5 10 1 1 180 8 1
value=red
T 60000 56800 5 10 1 1 180 8 1
refdes=D100
}
C 59500 54600 1 0 0 130r_250mw_vert.sym
{
T 59800 55300 5 10 1 1 0 0 1
refdes=R100
T 59800 55100 5 10 1 1 0 0 1
value=130
}
T 48000 54500 9 10 1 0 0 0 1
Power cable
T 59100 54000 9 10 1 0 0 0 1
Debug blinker
T 48100 56700 9 10 1 0 0 0 1
RS232 cable
C 48100 59700 1 0 0 2pin_mta100_white_recept.sym
{
T 48500 60400 5 10 1 1 0 0 1
refdes=MECH103
T 48100 60750 5 10 0 0 0 0 1
device=connector
T 48500 60200 5 10 1 1 0 0 1
value=mta100
T 48500 60000 5 10 1 1 0 0 1
description=2-pin, white
T 48500 59800 5 10 1 1 0 0 1
comment=24-guage stranded
}
C 45900 57400 1 0 0 3pin_mta100_white_recept.sym
{
T 46300 58100 5 10 1 1 0 0 1
refdes=MECH111
T 45900 58450 5 10 0 0 0 0 1
device=connector
T 46300 57900 5 10 1 1 0 0 1
value=mta100
T 46300 57700 5 10 1 1 0 0 1
description=3-pin, white
T 46300 57500 5 10 1 1 0 0 1
comment=24-guage stranded
}
C 50200 54900 1 0 0 2pin_mta100_header_in.sym
{
T 50200 56300 5 10 0 0 0 0 1
footprint=2pin_mta100_pol.fp
T 50200 56500 5 10 0 0 0 0 1
device=connector
T 50200 54900 5 10 1 1 0 0 1
value=mta100
T 50200 55800 5 10 1 1 0 0 1
refdes=J103
}
T 51100 55500 9 10 1 0 0 0 1
J401:10
T 51100 55100 9 10 1 0 0 0 1
J401:9
C 56500 59800 1 0 0 4_40x1_2_female_hex_standoff.sym
{
T 57000 60000 5 10 1 1 0 0 1
value=4-40 x 1/2 female hex
T 57000 60200 5 10 1 1 0 0 1
refdes=MECH105
}
C 59100 59800 1 0 0 4_40x1_2_female_hex_standoff.sym
{
T 59600 60000 5 10 1 1 0 0 1
value=4-40 x 1/2 female hex
T 59600 60200 5 10 1 1 0 0 1
refdes=MECH106
}
C 56500 58200 1 0 0 4_40x1_4phillips_zinc.sym
{
T 57000 58400 5 10 1 1 0 0 1
value=4-40 x 1/4 phillips
T 57000 58600 5 10 1 1 0 0 1
refdes=MECH109
T 57000 58200 5 10 1 1 0 0 1
comment=Zinc-plated
}
C 59100 60800 1 0 0 4_40x1_4phillips_zinc.sym
{
T 59600 61000 5 10 1 1 0 0 1
value=4-40 x 1/4 phillips
T 59600 61200 5 10 1 1 0 0 1
refdes=MECH101
T 59600 60800 5 10 1 1 0 0 1
comment=Zinc-plated
}
C 56500 60800 1 0 0 4_40x1_4phillips_zinc.sym
{
T 57000 61000 5 10 1 1 0 0 1
value=4-40 x 1/4 phillips
T 57000 61200 5 10 1 1 0 0 1
refdes=MECH100
T 57000 60800 5 10 1 1 0 0 1
comment=Zinc-plated
}
C 59100 58200 1 0 0 4_40x1_4phillips_zinc.sym
{
T 59600 58400 5 10 1 1 0 0 1
value=4-40 x 1/4 phillips
T 59600 58600 5 10 1 1 0 0 1
refdes=MECH110
T 59600 58200 5 10 1 1 0 0 1
comment=Zinc-plated
}
T 47200 59200 9 10 1 0 0 0 1
Power monitor output --> ADC input (ADC 4)
C 45900 59700 1 0 0 2pin_mta100_white_recept.sym
{
T 46300 60400 5 10 1 1 0 0 1
refdes=MECH102
T 45900 60750 5 10 0 0 0 0 1
device=connector
T 46300 60200 5 10 1 1 0 0 1
value=mta100
T 46300 60000 5 10 1 1 0 0 1
description=2-pin, white
T 46300 59800 5 10 1 1 0 0 1
comment=24-guage stranded
}
C 50200 59500 1 0 0 2pin_mta100_header_in.sym
{
T 50200 60900 5 10 0 0 0 0 1
footprint=2pin_mta100_pol.fp
T 50200 61100 5 10 0 0 0 0 1
device=connector
T 50200 59500 5 10 1 1 0 0 1
value=mta100
T 50200 60400 5 10 1 1 0 0 1
refdes=J100
}
T 51100 60100 9 10 1 0 0 0 1
J402:1
T 51100 59700 9 10 1 0 0 0 1
J402:2
T 59100 57500 9 10 1 0 0 0 1
J400:5 (PB4)
T 59000 54300 9 10 1 0 0 0 1
J400:9 (Ground)
C 49400 52900 1 0 0 binding_post_black_chassis.sym
{
T 50500 53100 5 10 1 1 0 0 1
value=binding post
T 50950 53750 5 10 1 1 0 0 1
refdes=J104
T 50500 52950 5 10 1 1 0 0 1
comment=black
}
C 49400 51800 1 0 0 binding_post_red_chassis.sym
{
T 50500 52000 5 10 1 1 0 0 1
value=binding post
T 50950 52650 5 10 1 1 0 0 1
refdes=J105
T 50500 51850 5 10 1 1 0 0 1
comment=red
}
C 47200 52600 1 0 0 3pin_mta100_white_recept.sym
{
T 47600 53300 5 10 1 1 0 0 1
refdes=MECH115
T 47200 53650 5 10 0 0 0 0 1
device=connector
T 47600 53100 5 10 1 1 0 0 1
value=mta100
T 47600 52900 5 10 1 1 0 0 1
description=3-pin, white
T 47600 52700 5 10 1 1 0 0 1
comment=24-guage stranded
}
T 48100 51700 9 10 1 0 0 0 1
Monitored power output
T 51700 52600 9 10 1 0 0 0 3
Binding posts need
0.328 inch mounting
hole
C 56500 59000 1 0 0 4_washer_lock_zinc.sym
{
T 57000 59200 5 10 1 1 0 0 1
value=#4 lock washer
T 57000 59400 5 10 1 1 0 0 1
refdes=MECH107
T 57000 59000 5 10 1 1 0 0 1
comment=Zinc-plated
}
C 59100 59000 1 0 0 4_washer_lock_zinc.sym
{
T 59600 59200 5 10 1 1 0 0 1
value=#4 lock washer
T 59600 59400 5 10 1 1 0 0 1
refdes=MECH108
T 59600 59000 5 10 1 1 0 0 1
comment=Zinc-plated
}
