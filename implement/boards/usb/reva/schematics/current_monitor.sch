v 20110115 2
C 39200 39200 0 0 0 title-bordered-B.sym
T 50900 40300 9 20 1 0 0 0 1
Current monitor
T 49400 39500 9 10 1 0 0 0 1
4
T 51000 39500 9 10 1 0 0 0 1
5
T 49500 39800 9 10 1 0 0 0 1
current_monitor.sch
T 53000 39500 9 10 1 0 0 0 1
John Peck
T 53000 39800 9 10 1 0 0 0 1
B
C 44200 46900 1 0 0 lt6106-a.sym
{
T 45451 47201 5 10 1 1 0 0 1
value=lt6106
T 45451 47391 5 10 1 1 0 0 1
refdes=U?
}
C 44000 40900 1 0 0 lt6106-b.sym
{
T 44494 41400 5 10 1 1 0 0 1
refdes=U?
T 44500 41214 5 10 1 1 0 0 1
value=lt6106
}
C 40800 42100 1 0 0 10r0_1206_horz.sym
{
T 42100 42600 5 10 1 1 0 0 1
refdes=R?
T 42100 42100 5 10 1 1 0 0 1
value=10
}
C 43100 41200 1 0 0 100n_x7r_50v_1206_vert.sym
{
T 43600 41800 5 10 1 1 0 0 1
refdes=C?
T 43600 41600 5 10 1 1 0 0 1
value=100n
}
C 41100 42600 1 0 0 vbus.sym
C 43100 40300 1 0 0 gnd_bus.sym
N 43300 41200 43300 40700 4
N 44200 41100 44200 40900 4
N 44200 40900 43300 40900 4
N 42800 42400 44200 42400 4
N 44200 42400 44200 42300 4
N 43300 42300 43300 42400 4
N 41300 42600 41300 42400 4
N 41300 42400 41600 42400 4
T 46500 41700 9 10 1 0 0 0 2
Set output voltage scaling such
that 10mA sensed gives 1V output.
C 43500 45600 1 0 0 1r00_1206_horz.sym
{
T 44800 46100 5 10 1 1 0 0 1
refdes=R?
T 44700 45600 5 10 1 1 0 0 1
value=1.00
T 44600 45400 5 10 1 1 0 0 1
comment=Rsense
}
N 44300 46500 44700 46500 4
N 44700 46500 44700 46901 4
N 44700 46901 44699 46901 4
N 45500 45900 45500 46500 4
N 45500 46500 45100 46500 4
N 45100 46500 45100 46901 4
N 45100 46901 45099 46901 4
C 41500 46200 1 0 0 100_1206.sym
{
T 42800 46200 5 10 1 1 0 0 1
value=100
T 42800 46700 5 10 1 1 0 0 1
refdes=R?
}
T 41700 46900 9 10 1 0 0 0 2
What should Rgain be?

