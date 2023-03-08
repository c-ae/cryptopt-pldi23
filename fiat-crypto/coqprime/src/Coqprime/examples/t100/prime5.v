Require Import PocklingtonRefl.


Local Open Scope positive_scope.

Lemma prime172779892108321 : prime 172779892108321.
Proof.
 apply (Pocklington_refl
         (Pock_certif 172779892108321 17 ((29, 1)::(7, 1)::(5, 1)::(3, 1)::(2,5)::nil) 174412)
        ((Proof_certif 29 prime29) ::
         (Proof_certif 7 prime7) ::
         (Proof_certif 5 prime5) ::
         (Proof_certif 3 prime3) ::
         (Proof_certif 2 prime2) ::
          nil)).
 vm_cast_no_check (refl_equal true).
Qed.

Lemma prime5678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901283: prime  5678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901283.
apply (Pocklington_refl

(Ell_certif
5678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901283
8613
((659340675092057369494576687837649936286377323827160029599474171252548335017794784969008387843487,1)::nil)
1068370684844652260561789543542317206494058914638487074483065066870522241572631928238294289071616672
2822867551543524372833926155064065135726625003423672416040767219112868011384344197573385301080637618
0
1485199565862283195881180229577224102904204817342168821758275109328053353215060809132405108152024908)
(
(Ell_certif
659340675092057369494576687837649936286377323827160029599474171252548335017794784969008387843487
784
((840995759045991542722674346731696347304052708961154473076562011004759456840821740229534724691,1)::nil)
659340675092057369494576687837649936286377323827160029599474171252548335017794784969008387829487
784000
60
400)
::
(Ell_certif
840995759045991542722674346731696347304052708961154473076562011004759456840821740229534724691
1238998
((678770876987688069490567657681203962640821622719712124274147234798329001767408254730013,1)::nil)
348502809392728702382143600736008759783891417410604315630621259828045668880210579001104142401
251006917402217510235095378496438958480085365875972945273933630548402752573471274670116690452
0
715846432454144902090661893282057846625308601853694686281147014129806416784517730436789754527)
::
(Ell_certif
678770876987688069490567657681203962640821622719712124274147234798329001767408254730013
1227312638091
((553054581140359855568272010920571331757971842220703771483940258670602561773,1)::nil)
678770876987688069490567657681203962640821622719712124274147234798329001767407714121109
4964006108754
1431
2047761)
::
(SPock_certif
553054581140359855568272010920571331757971842220703771483940258670602561773
2
((1245618425991801476505117141712998494950387032028612097936802384393249013, 1)::nil))
::
(Ell_certif
1245618425991801476505117141712998494950387032028612097936802384393249013
2216
((562102177794134240300143114491425312602019857606760176090665010402453,1)::nil)
1245618425991801476505117141712998494950387032028612097936802384393234613
0
600
14400)
::
(SPock_certif
562102177794134240300143114491425312602019857606760176090665010402453
2
((13574054106151981879085738582925082441400445206162064838440283, 1)::nil))
::
(Ell_certif
13574054106151981879085738582925082441400445206162064838440283
65053
((208661462286934989609791071632731304020957206302253936841,1)::nil)
13574054106151981879085738582925082441400445206162064788882051
134414314742
571
326041)
::
(Ell_certif
208661462286934989609791071632731304020957206302253936841
2864
((72856655826443781288334871374370203901835514626114347,1)::nil)
208661462286934989609791071631883471778573702718360406921
9501955807025115933281263315351902213136
0
97477976010097357444)
::
(Ell_certif
72856655826443781288334871374370203901835514626114347
193909
((375726014916500942650082621555351061909959757389,1)::nil)
42468594832879496729329998977535240386338594816577001
7601203492123761869110523573895967176903156129914483
63698057858557777145788663331134240544889144218776424
68232934711282586914658866416333435773712638774607916)
::
(SPock_certif
375726014916500942650082621555351061909959757389
2
((500887618743807484206232002262750205251, 1)::nil))
::
(Ell_certif
500887618743807484206232002262750205251
87943750
((5695545376946144372855130269723,1)::nil)
62004971613157849451395456945007846064
396441284199113617890290527436816450668
0
242419420997785707670081855384920877972)
::
(SPock_certif
5695545376946144372855130269723
2
((42732959595582599647, 1)::nil))
::
(SPock_certif
42732959595582599647
2
((172779892108321, 1)::nil))
:: (Proof_certif 172779892108321 prime172779892108321) :: nil)).
vm_cast_no_check (refl_equal true).
Time Qed.
