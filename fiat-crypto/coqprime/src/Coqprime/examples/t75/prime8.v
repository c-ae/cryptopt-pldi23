Require Import PocklingtonRefl.


Local Open Scope positive_scope.

Lemma prime1428863796293 : prime 1428863796293.
Proof.
 apply (Pocklington_refl
         (Pock_certif 1428863796293 2 ((5521, 1)::(2,2)::nil) 39360)
        ((Proof_certif 5521 prime5521) ::
         (Proof_certif 2 prime2) ::
          nil)).
 vm_cast_no_check (refl_equal true).
Qed.

Lemma prime890123456789012345678901234567890123456789012345678901234567890123456789173: prime  890123456789012345678901234567890123456789012345678901234567890123456789173.
apply (Pocklington_refl

(Ell_certif
890123456789012345678901234567890123456789012345678901234567890123456789173
8157
((109123876031508194885239822798564438326984028833593131325708554662494431,1)::nil)
0
6912
24
144)
(
(Ell_certif
109123876031508194885239822798564438326984028833593131325708554662494431
23126
((4718666264442973055662017763494094857332768848910597827514106537269,1)::nil)
75086423499566443626294790461747896159635481549407206330838166528837345
59953269250185783651557418217622427910089096673128817048258912126221366
0
82899844225043528315881252052116704460417867294689765206259949533005158)
::
(Ell_certif
4718666264442973055662017763494094857332768848910597827514106537269
6154934806532
((766647643356876932190231753946036742091898972419711353,1)::nil)
900
0
90
900)
::
(Ell_certif
766647643356876932190231753946036742091898972419711353
432
((1774647322585363268958869804318404498357590845516267,1)::nil)
111886407845002772474570366365409298112033165382738455
752469734628528106621455495761382810994729448598465265
0
223244498068698190097254653622960681088833419085712351)
::
(Ell_certif
1774647322585363268958869804318404498357590845516267
3484036
((509365380433888532999908672890634937587338727,1)::nil)
1774647322585363268958869804318404498336845014040107
36370126051009921296
0
6030764964)
::
(SPock_certif
509365380433888532999908672890634937587338727
2
((84894230072314755499984778815105822931223121, 1)::nil))
::
(Ell_certif
84894230072314755499984778815105822931223121
1332936
((63689652070553091446225773835726149979,1)::nil)
84894230072314755499984778815105822931129041
9834496
0
3136)
::
(SPock_certif
63689652070553091446225773835726149979
2
((18538246409960803251808677733, 1)::nil))
::
(Ell_certif
18538246409960803251808677733
22305783
((831095972284889937607,1)::nil)
0
6912
24
144)
::
(SPock_certif
831095972284889937607
2
((1428863796293, 1)::nil))
:: (Proof_certif 1428863796293 prime1428863796293) :: nil)).
vm_cast_no_check (refl_equal true).
Time Qed.
