Require Import PocklingtonRefl.


Local Open Scope positive_scope.

Lemma prime3051683430797 : prime 3051683430797.
Proof.
 apply (Pocklington_refl
         (Pock_certif 3051683430797 2 ((762158699, 1)::(2,2)::nil) 1)
        ((Pock_certif 762158699 2 ((157, 1)::(7, 1)::(2,1)::nil) 3862) ::
         (Proof_certif 157 prime157) ::
         (Proof_certif 7 prime7) ::
         (Proof_certif 2 prime2) ::
          nil)).
 vm_cast_no_check (refl_equal true).
Qed.

Lemma prime78901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123703: prime  78901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123703.
apply (Pocklington_refl

(SPock_certif
78901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123456789012345678901234567890123703
2
((13150205761315020576131502057613150205761315020576131502057613150205761315020576131502057613150205761315020576131502057613150205761315020576131502057613150205761315020576131502057613150205761315020617, 1)::nil))
(
(Ell_certif
13150205761315020576131502057613150205761315020576131502057613150205761315020576131502057613150205761315020576131502057613150205761315020576131502057613150205761315020576131502057613150205761315020617
210582796
((62446724096658971970965292234096607805327625247107705332479359568412992840215570751098098313549819932037201887236272497895214604823710061681092711442295140668497291619167034204323663746522827,1)::nil)
13150205761315020576131502057613150205761315020576131502057613150205761315020576131502057613150205761315020576131502057613150205761315020576131502057613150205761315020576131502057613150205761315006617
784000
60
400)
::
(Ell_certif
62446724096658971970965292234096607805327625247107705332479359568412992840215570751098098313549819932037201887236272497895214604823710061681092711442295140668497291619167034204323663746522827
7737346244210743
((8070819390224784062308166051157733088932770668799185567819163606799819832933891942298622447941461846445641514874043146000795503625960020435432968305761506782239066106950321473,1)::nil)
703092603074645806763560144016687037130034493134718604327160987766285229453611250253626691763163069811391083629548366767290939750612326842662362885166592174569807256394643910827102566161412
30284909960067258094348193654431594304229402776593941377978820423713414868536883342074227365805065848497435103175771823169987570776694362633102503406829334544323377919451317281905567190456598
33522029641721680144520027834992177905559507705146180553042078115996896981686367949556861275274942305121052430888425410026002010978827458639758423582459031239167409462483500500220052502420777
8118683479780496549333867808418691670928603118765007741779546833490837947827640031413050511823563163299228737858097475417454845130426090576676643702939917936999225315017397695192878555222591)
::
(Ell_certif
8070819390224784062308166051157733088932770668799185567819163606799819832933891942298622447941461846445641514874043146000795503625960020435432968305761506782239066106950321473
3268
((2469650976200974315271776637441166795879060792166213454045031703427117451938155429099946905047328575104372061798074097382609952144415878714420835508392525391047958268095987,1)::nil)
6107494343868143024592055621343595077079671341499163601270540060592889482197787399575923604427720870303988431326834544112523130315706095647463961594212256711442903378385567925
1062119645895688949200582600801260557924370240299527503413449998507155137031821218948756213798943325483291543206581013304463752107007140369474197473815440165348302887833508431
4693820211891152847426762580666485024615073734664234160852862460448173004398932181354060644697446460505277370196586470166444012765155221955877857380966615449159581689087999192
340630880860780886332718254554188800860130682573241288247103055406989323319375878336340516140525980957149304472112218568626318324548512442641543913093586857719527589539094892)
::
(Ell_certif
2469650976200974315271776637441166795879060792166213454045031703427117451938155429099946905047328575104372061798074097382609952144415878714420835508392525391047958268095987
4755858983437
((519285997503691402946432462451668073310423856217512711074002559147742151123952303498878710492842823058827485683378365380976115402309534291796662460778721443497,1)::nil)
0
2209179974804777805457956445211043735376191099242433128813719765956288658179053098687061879905618139448832820905308469924287808754184516506259263013366751228710868919507622
1234825488100487157635888318720583397939530396083106727022515851713558725969077714549973452523664287552186030899037048691304976072207939357210417754196262695523979134048009
771765930062804473522430199200364623712206497551941704389072407320974203730673571593733407827290179720116269311898155432065610045129962098256511096372664184702486958780056)
::
(Ell_certif
519285997503691402946432462451668073310423856217512711074002559147742151123952303498878710492842823058827485683378365380976115402309534291796662460778721443497
80879
((6420529401991758094764184305588200562697657688862531820052208350100052561529596889402973813278977475034023979031247338583493895080833257739352644792337101,1)::nil)
478210302584949727954004671322735221980657885354810766981707938508206314117920457446990772765517243630650637606839232540176828135948998265877792443382035564011
445858719734253901533118214418872182037115153525264671449733691979270067934454252780386576420396150736176022259866960779665411127035364691482483807869849882780
0
241008292658777285465555206484533171181857337072552890775112403977998686473889224128130473775918088256035937740864314957573893080447813154140843791830918983066)
::
(Ell_certif
6420529401991758094764184305588200562697657688862531820052208350100052561529596889402973813278977475034023979031247338583493895080833257739352644792337101
19066
((336752827126390333303481816090852856535070685453819984267922393270746489118301489396338892012078514072616455431635116221691000974368758702627238273969,1)::nil)
103968
0
1368
51984)
::
(Ell_certif
336752827126390333303481816090852856535070685453819984267922393270746489118301489396338892012078514072616455431635116221691000974368758702627238273969
40148361
((8387710450406439587994185269253030193064934467781137672542159149927602003906668329941099679281501747829021263200867916576405633004826743812763,1)::nil)
336752827126390333303481816090852856535070685453819984267922393270746489118301489396338892012078514072616455431635116221691000974368758687016369579969
23740460778072323250
202095
4538043225)
::
(Ell_certif
8387710450406439587994185269253030193064934467781137672542159149927602003906668329941099679281501747829021263200867916576405633004826743812763
131
((64028324048904118992322024956130001473778125708252959332382894274256504224779513676160350341036817857817143015471305633749803209440031159071,1)::nil)
7162674947405557906952564445665038525720208586281788380418123672074883870454519779285902361231098408166456612154619991137027856540614344174857
6745746983004155019430308651534543064168572235664318750205052457980357503292700793470130878431805651322066931334737998576357865647697288888585
0
7197443410403997469356309452235292038275280891934365439251397431717229301495357713508441814826247928367767441415568444133101000466802165612125)
::
(Ell_certif
64028324048904118992322024956130001473778125708252959332382894274256504224779513676160350341036817857817143015471305633749803209440031159071
5852512
((10940314868026604472117618034124492435688833394660781444340976024356120659458717421629165740605139330873299593697598390613241511273833,1)::nil)
64028324048904118992322024956130001473778125708252959332382894274256504224779513676160350341036817857817143015471305633749803209440031142131
1043504
88
484)
::
(Ell_certif
10940314868026604472117618034124492435688833394660781444340976024356120659458717421629165740605139330873299593697598390613241511273833
2641
((4142489537306552242376985245787388275535340172154782826331304818007900977114121212612772890509733672593753880202210962593132138561,1)::nil)
0
19008
12
144)
::
(Ell_certif
4142489537306552242376985245787388275535340172154782826331304818007900977114121212612772890509733672593753880202210962593132138561
1940525
((2134726188689427985919782144413181111057749924455898700780100652085337844452279367588088993525474223148456272073465649049011,1)::nil)
4142489537306552242376985245787388275535340172154782826331304818007900977114121212612772890509733672593753880202210943644029872721
31749105730618655022
74219
5508459961)
::
(Ell_certif
2134726188689427985919782144413181111057749924455898700780100652085337844452279367588088993525474223148456272073465649049011
920
((2320354552923291289043241461318675120714945570060759457369674713250866810112327106062656449078691593283446602053575919163,1)::nil)
1632074358799289760669837192721751720873282080428283903704997593399969004240511194341711020443110534966346636502292150133550
2008136420944272164278158305627271957873327424314965298152035741802404334582008327118102662847199044272541274335042932628971
1222663957274203146169952750045707739663548315743171137996605168239598252558349691854580518934271393076570748591124090519608
1694611433523701628456504065952568388322069234036122379511426215395426501653750165549685439660023095911054243609972140241345)
::
(Ell_certif
2320354552923291289043241461318675120714945570060759457369674713250866810112327106062656449078691593283446602053575919163
157
((14779328362568734325116187651711306501369080064081270429106223446026080003313444782835934267658154554466322911712221479,1)::nil)
360919338944395125675580118925697333919911595453059986469639366157743684847768706951650421836939326402037143040160098508
1017359749703613438691808869181561385671314882088215429079221445252739647763803288184173035224933768925445850560483055423
815777614476277861425720218158868175004711203759041987598186830092182336670868377491591358297272209522540462897751463822
1569137569450449949427381261805199212962846404635067723753734614207919944188849722177714165565632006045262240689285142632)
::
(Ell_certif
14779328362568734325116187651711306501369080064081270429106223446026080003313444782835934267658154554466322911712221479
72
((205268449480121310071058161829323701407903889778906533737584988885249808755122945511269846924093599145290277029638923,1)::nil)
12018957655627221707636655733883409920425435417656233363945641315178318496843736925564064007625174231542853465073770011
13189945880149608772478909342820819912194895046013554015679007258546568698183896698294223253906371951279908516695927848
4723718154632092445193770597888548170927707538654164142455796843909480318734483363612135482292090175769895644610103987
8902381836232399581670956949734154472224245390320172602139813771039944149510685521699214785758943856348330535575086456)
::
(Ell_certif
205268449480121310071058161829323701407903889778906533737584988885249808755122945511269846924093599145290277029638923
15343
((13378638433169608946819928425296467536199171594792839323313704727393076258184684893896162178624891870573847881073,1)::nil)
170668734752342157728016552554008302451859695201868220387158543021314969802685501705662787124905722605279739016344493
40709564126789631846951624226712471842301811521652979111333593203876665315229022598783756884318236609459974895874837
170507930847899378531160462857831152171621509237002041265475228604852037971627199607802925579379705773860031878569816
136543059445003486457975776092209162406699887290538869638751271921353726461419117447569014229137030181932895764829481)
::
(Ell_certif
13378638433169608946819928425296467536199171594792839323313704727393076258184684893896162178624891870573847881073
7771788
((1721436358424806356892381576195396417941298912784656416657161286200103344698931356253565931475192456745827,1)::nil)
13378638433169608946819928425296467536199171594792839323313704727393076258184684893896162178624891870573847786993
9834496
0
3136)
::
(Ell_certif
1721436358424806356892381576195396417941298912784656416657161286200103344698931356253565931475192456745827
48742
((35317310705855450266554133523355554099981513125941825985839828592446218456024550770849912923460204513,1)::nil)
89450538684894501459619731814309607167796567275015709440693630025879599941024169154066430698783482038559
391738640474998873531549439432108841807154771116505245311171161388274164665456412072300127195803474397018
0
747512751982657613531186859154298607818943243086059094446882214950306786034575668073672039027461849809814)
::
(Ell_certif
35317310705855450266554133523355554099981513125941825985839828592446218456024550770849912923460204513
2993842
((11796651495254408972335258014068729779320856987757394676493970597939389457072845040895946177369,1)::nil)
11772436901951816755518044507785184699993837708647275328613276197482072818674850256949970974486750679
0
1308
47524)
::
(Ell_certif
11796651495254408972335258014068729779320856987757394676493970597939389457072845040895946177369
836914258
((14095412262954192581500096768656950972056276029935656502909928066765621722764459898437,1)::nil)
48
0
4
16)
::
(Ell_certif
14095412262954192581500096768656950972056276029935656502909928066765621722764459898437
14612
((964646336090486763037236296787363192722164769505258931204787088221018683786613533,1)::nil)
100
0
20
100)
::
(Ell_certif
964646336090486763037236296787363192722164769505258931204787088221018683786613533
8676646704
((111177321031842575647325365247159565887764429885138305096638718446173723,1)::nil)
0
78608
17
289)
::
(Ell_certif
111177321031842575647325365247159565887764429885138305096638718446173723
6064042968
((18333861026138193361054259147056816436807405015216694130463873,1)::nil)
111177321031842575647325365247159565887764429885138305096638718445837583
92236816
0
9604)
::
(Ell_certif
18333861026138193361054259147056816436807405015216694130463873
869632356
((21082312427365792908761388297590516552572762146075011,1)::nil)
18333861026138193361054259147056816436807405015216694130369793
9834496
0
3136)
::
(Ell_certif
21082312427365792908761388297590516552572762146075011
914722
((23047781104385586996662798681759200915353275197,1)::nil)
17450524287644722387772233289807011872118464591769092
9038208780082230374518578657610700108941721577803809
0
19258362161866507852935702045370850083024125773511032)
::
(Ell_certif
23047781104385586996662798681759200915353275197
327
((70482511022585892956156059579676628950328877,1)::nil)
0
9000
10
100)
::
(SPock_certif
70482511022585892956156059579676628950328877
2
((22677770599287610346253558423319378684147, 1)::nil))
::
(SPock_certif
22677770599287610346253558423319378684147
2
((28606604132698327338176592701561, 1)::nil))
::
(Ell_certif
28606604132698327338176592701561
621136
((46055298892188406370132437,1)::nil)
100
0
20
100)
::
(SPock_certif
46055298892188406370132437
2
((538054335391705294291, 1)::nil))
::
(Ell_certif
538054335391705294291
1359
((395919304944741187,1)::nil)
0
78608
17
289)
::
(SPock_certif
395919304944741187
2
((3051683430797, 1)::nil))
:: (Proof_certif 3051683430797 prime3051683430797) :: nil)).
vm_cast_no_check (refl_equal true).
Time Qed.
