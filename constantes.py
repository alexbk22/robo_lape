import math

#constantes do robo

#pulses per round
ppr = 663

#diam in cm, to be converted
diam = 13.5 
diam /= 100.0

#espessura das rodas
er = 2.1
er /= 100.0

#base entre o centro das rodas
base = 30.0
base /= 100.0
base -= er


r = diam/2

circum = math.pi * diam

#distance per pulse
dpp = circum/ppr

values = [ppr,circum,diam,r,dpp,er,base]

print values