Require Import PocklingtonRefl.


Local Open Scope positive_scope.

Lemma prime31030386103 : prime 31030386103.
Proof.
 apply (Pocklington_refl
         (Pock_certif 31030386103 3 ((84551, 1)::(2,1)::nil) 1)
        ((Pock_certif 84551 11 ((5, 2)::(2,1)::nil) 90) ::
         (Proof_certif 5 prime5) ::
         (Proof_certif 2 prime2) ::
          nil)).
 vm_cast_no_check (refl_equal true).
Qed.

Lemma prime56789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901643: prime  56789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901643.
apply (Pocklington_refl

(Ell_certif
56789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901643
317
((179145149355453947112201546130778514234528955524399267792187560848619386999688437122681777466211395429779987918108071301842037244132304188175485466219491519937063802289928803326944503266519981874693,1)::nil)
56789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456680479071004636323
13762346127466829996235398
1918747
3681590050009)
(
(Ell_certif
179145149355453947112201546130778514234528955524399267792187560848619386999688437122681777466211395429779987918108071301842037244132304188175485466219491519937063802289928803326944503266519981874693
256
((699785739669741980907037289573353571228628732517184639813232659564919480467532957510475693227388266268729616064759650055755420572534054645393258240788867258678634769432810090625846855254672199487,1)::nil)
179145149355453947112201546130778514234528955524399267792187560848619386999688437122681777466211395429779987918108071301842037244132304188175485466219491519937063802289928803326944503266519981731333
25690112
64
4096)
::
(Ell_certif
699785739669741980907037289573353571228628732517184639813232659564919480467532957510475693227388266268729616064759650055755420572534054645393258240788867258678634769432810090625846855254672199487
29640002
((23609503793884426219237005772582389543314765380825029627637429294536467321005341278670483666883298235949993802567141838835021254617951052047082292084221450958585795971061285696783774395563,1)::nil)
688669969755872957071488664446682594109994277588839308607776291470500076785036745311955632548393955536528006146869588193178271864656460843078169324225781496941280622763280009425042981064090915716
512077864979424165061153389050637516889123733880068100680171161928411481074803146317805959230380047556661273490286183558260398607639069942552592301966758865027845811159185012282523513849269685889
0
208901508578337366782627272991156365547342104201435622457701598029106056082410515099242019239485806719023769612439607940378356595117139389477957384552679180399090679339561677787638938236442494555)
::
(Ell_certif
23609503793884426219237005772582389543314765380825029627637429294536467321005341278670483666883298235949993802567141838835021254617951052047082292084221450958585795971061285696783774395563
1017
((23214851321420281434844646777367148026858176382325496192367187113605179273358251011475401835667270510248819191840820919363338006377086789135806926178760226369675478797541521385458382619,1)::nil)
23609503793884426219237005772582389543314765380825029627637429294536467321005341278670483666883298235949993802567141838835021254617951052047082292084221450958585795971061285696783016811659
8234810772496
0
2869636)
::
(Ell_certif
23214851321420281434844646777367148026858176382325496192367187113605179273358251011475401835667270510248819191840820919363338006377086789135806926178760226369675478797541521385458382619
46783130
((496222705095197380655049090930152557703133081996127582578745524585575596873450985675293676070445749532850077836134040936495613613270571263062604572264485396359807152508056450699,1)::nil)
18726013183914340835224516737784903891057399468896536015841234024485867053868875959327210216354206901872006048552921168424678379109158930348164609108820646969125424793011151702281228396
6742017161081699532635478255282669220184481865940669433083042492456741984269723852641542417330489170581302722424009211668394639240623093858430042518282035567437350553800494538080154947
11872342586489416293786828512821382631269376866160658306117072168628898678289974141019864927951570940980661882344716635398313467301749507930553399667295812006176400208074677675512023088
955699490833930088893174944782865971072429497387997290840893068650622629009749502640527367604610484418657468630743460897699925208330155730181433300235781652005790059276657320196645042)
::
(Ell_certif
496222705095197380655049090930152557703133081996127582578745524585575596873450985675293676070445749532850077836134040936495613613270571263062604572264485396359807152508056450699
1355603457
((366052994725578794872495733780171790830076853364152775673207452277525135341589045295045772639270693427420812253321776535745754275157586406350046812209324747664865298473,1)::nil)
37501051029651645717254953884295152421359407776507279631195497118214239440917765223905200453966247798591613142805064257122991665587455785150000990887480319001610859923392714671
239369720244233189227573193409596772218487069838648628627614653893734745673336122356751009892000959678203038582456807447848006285706561146080174313488402120910200381772558818325
392223734638268510795658282321898622069359294523447100817493693593869289340694090872458634741156118567450791770054267083318523123795188653298387873160751270220384784164748008641
196019141629857122128382069067645833318597409687095636020783743406036700582777199271309229446413878092179023894387317122230664383192127960717023809034378615056903335881229166287)
::
(Ell_certif
366052994725578794872495733780171790830076853364152775673207452277525135341589045295045772639270693427420812253321776535745754275157586406350046812209324747664865298473
968177437
((378084616245378164986606410432359405242034010924954839319610638971671403804454746133752882129254267397384044920833682361483455540845204901908829434152506023761,1)::nil)
0
3584
8
64)
::
(Ell_certif
378084616245378164986606410432359405242034010924954839319610638971671403804454746133752882129254267397384044920833682361483455540845204901908829434152506023761
102612
((3684604298185184627398417440770664300881320030064269669430579649277583555572980824006797207740285698994786470047512772175668624582444693867352772412189813,1)::nil)
214669133444526218610284373654351666253302766806873035555606735159691836366789312255338675352071645728060597821427531918571525570298073892090605088179100179499
139831144162400097124357779493753469185862064020541805680296065568471000904700162792666716144916038789619156894009418102234855775678575562545638279998453583359
154254063115109440049975687812872533007570393047263412275481257849737391901807873766983783616667917861187932068126036717311084331783217907154243325680241601245
65850363782280009803853995097810380180644328589036104359847376595823487126356165250595515696649059700044258810908200716381171819651269500464250858180295265922)
::
(Ell_certif
3684604298185184627398417440770664300881320030064269669430579649277583555572980824006797207740285698994786470047512772175668624582444693867352772412189813
1882092
((1957717421988502489463011075319731607637309988068739290869192180444730414651934236258539156763771779249451072419443514305748132312249499180471893461,1)::nil)
0
5267712
304
5776)
::
(Ell_certif
1957717421988502489463011075319731607637309988068739290869192180444730414651934236258539156763771779249451072419443514305748132312249499180471893461
3250
((602374591381077689065541869329148186965326150174996704882828363213763204482262426640468959632284325086486077422335812702626885799718730263567749,1)::nil)
978858710994251244731505537659865803818654994034369645434596090222365207325967118129269578381885889624725536209721757152874066156124749590235946771
0
18
81)
::
(Ell_certif
602374591381077689065541869329148186965326150174996704882828363213763204482262426640468959632284325086486077422335812702626885799718730263567749
722
((834313838477946937763908406273058430699897714923818150807241500296070922459390005344637665513087826424182656369878105251615800128978663783299,1)::nil)
306754968490475566655222655716424281913848657806685968574134267842763158487430023469241190382920728186925751540636132644251120587986810142790042
443654941058981426309054521651924027099984879487418790921399078778139577443903339613102427363728127681297336737293938247582150884835285317723554
576593332761449832979719656250848464628137016794155265952392686995609217394313903818790845572296247541017410375514531538142609980060660942546029
303999545921120866366767784641606946859020906270942941887613169491823478584466397918162199351199061793078359332931029209176793204246748745310027)
::
(Ell_certif
834313838477946937763908406273058430699897714923818150807241500296070922459390005344637665513087826424182656369878105251615800128978663783299
364379248
((2289685384272890693720045237793175397024524609930086223810532427181667915565877271225522316675693073655524378268057314790644788514091,1)::nil)
834313838477946937763908406273058430699897714923818150807241500296070922459390005344637665513087826424182656369878105251615800128978663639939
25690112
64
4096)
::
(Ell_certif
2289685384272890693720045237793175397024524609930086223810532427181667915565877271225522316675693073655524378268057314790644788514091
473819154
((4832403597328804258765877661824484615547062941085927952609810339535746733911011298911956868358813309822083472778824903314859,1)::nil)
2289685384272890693720045237793175397024524609930086223810532427181667915565877271225522316675693073655524378268057314790644788485261
1668296
155
961)
::
(Ell_certif
4832403597328804258765877661824484615547062941085927952609810339535746733911011298911956868358813309822083472778824903314859
301450219
((16030519444833457754979695874178431482735339930490904545038032983369866902148656853512089847249529379660599829844891,1)::nil)
0
13310
11
121)
::
(Ell_certif
16030519444833457754979695874178431482735339930490904545038032983369866902148656853512089847249529379660599829844891
13560
((1182191699471493934733015919924663088697296455050951662613268599099710849396211713004928707305092597963034137439,1)::nil)
4213812983812081513659698442752618724274799264077923911345749191843346091152458387709930977086115347249783034528526
7310602653083487183983123520883998079797059894647957529392730775236857499039251904048928787034302297599244895825071
0
3993723456244310534317058116694927763971280236510192093770666212378773439507784592484302354177552358716555076885112)
::
(Ell_certif
1182191699471493934733015919924663088697296455050951662613268599099710849396211713004928707305092597963034137439
107256684629
((11022079449506437855131401498922076929725983941973329728301196395820370719198192610500582807651792781,1)::nil)
1039831084985524878980613494917742930767855122879763952866053382782707549011321505090258650311355231140350505950
422748403504648853360301080349272868764239419274514116440207738971656363563098644819062768656148685395490232232
0
914018479318734979940410394265550752427960943823766535745172895262391660308697662053563538798096585938713306923)
::
(Ell_certif
11022079449506437855131401498922076929725983941973329728301196395820370719198192610500582807651792781
10442
((1055552523415671121924095144505083023340929318327261137857218212113030779011118353714687420815437,1)::nil)
6257010676449663590551676035059976871541981751115821585611011718555683621312937092489812417859235906
3073396148241313984645266053415765675060919598993674617276029238273103560191984169632483499555483827
10444403415119173069749673885479238479263210634280575873587107468303674778951798531206653392823643513
2846308131738858183297286569859749301170570493331169847514686989111298790052823980651991580975399858)
::
(Ell_certif
1055552523415671121924095144505083023340929318327261137857218212113030779011118353714687420815437
71258968
((14812907807136234725208133024114003774808095990499272107615472701051163411359308152470131,1)::nil)
101760306095130389474865677238456413232600342350659137442897495052152905578169948800645769401336
322946624316770841802909848248872235054427444916448995173075109248179267400096634724099278934375
20530146683728348121956509189337399883590488081217017596275327924535406347408009318082788242074
442365458155661673361608348366098919760361138175488764994513100698917211079461496878684186249303)
::
(SPock_certif
14812907807136234725208133024114003774808095990499272107615472701051163411359308152470131
2
((1468078078011519794371470071765510780456699305302207344659610773146795184475649965557, 1)::nil))
::
(Ell_certif
1468078078011519794371470071765510780456699305302207344659610773146795184475649965557
112
((13107839982245712449745268497906346254077687911308198543528431473477600455551842567,1)::nil)
0
1642545
276
4761)
::
(Ell_certif
13107839982245712449745268497906346254077687911308198543528431473477600455551842567
193149778989
((67863603317880120827070425107781878074338318830799432746628756283207181,1)::nil)
0
119164
93
961)
::
(Ell_certif
67863603317880120827070425107781878074338318830799432746628756283207181
248389200
((273214790811678288859058385420066083965125590824706730550960027,1)::nil)
0
78608
17
289)
::
(Ell_certif
273214790811678288859058385420066083965125590824706730550960027
257245429
((1062078311260015776058972792943502281326069730826612251,1)::nil)
187642008825906325036380855818707592634949004622506215701923627
157481667176591695832147219347353521407425915851509032059744844
0
201998141425037148144597186151519507221158848735141524822340878)
::
(Ell_certif
1062078311260015776058972792943502281326069730826612251
3558
((298504303333337767301566271389814635870826599308377,1)::nil)
1062078311260015776058972792943502281326069730826518171
9834496
0
3136)
::
(Ell_certif
298504303333337767301566271389814635870826599308377
1032336
((289154212711111273172267847483560408011708003,1)::nil)
298504303333337767301566271389814635870826599307897
3584
8
16)
::
(Ell_certif
289154212711111273172267847483560408011708003
898492
((321821688686277978181489769409229248421,1)::nil)
0
1080
6
36)
::
(Ell_certif
321821688686277978181489769409229248421
7525
((42767001818774482145611811235813937,1)::nil)
0
2058
7
49)
::
(Ell_certif
42767001818774482145611811235813937
22723
((1882101915186132224744370320173,1)::nil)
0
37922302393991435340054223363466179
32075251364080861609208858426861234
40094064205101077011511073033599980)
::
(SPock_certif
1882101915186132224744370320173
2
((3200853597255326912830561769, 1)::nil))
::
(SPock_certif
3200853597255326912830561769
2
((215923745092777044848257, 1)::nil))
::
(Ell_certif
215923745092777044848257
3809424
((56681468141079247,1)::nil)
0
5832
9
81)
::
(Ell_certif
56681468141079247
1826644
((31030386103,1)::nil)
0
3584
8
64)
:: (Proof_certif 31030386103 prime31030386103) :: nil)).
vm_cast_no_check (refl_equal true).
Time Qed.