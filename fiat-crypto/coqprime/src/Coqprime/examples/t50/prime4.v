Require Import PocklingtonRefl.


Local Open Scope positive_scope.

Lemma prime409355789 : prime 409355789.
Proof.
 apply (Pocklington_refl
         (Pock_certif 409355789 2 ((2069, 1)::(2,2)::nil) 16358)
        ((Proof_certif 2069 prime2069) ::
         (Proof_certif 2 prime2) ::
          nil)).
 vm_cast_no_check (refl_equal true).
Qed.

Lemma prime45678901234567890123456789012345678901234567890173: prime  45678901234567890123456789012345678901234567890173.
apply (Pocklington_refl

(Ell_certif
45678901234567890123456789012345678901234567890173
4681
((9758363861262100005011065186172171907551501609,1)::nil)
9781366845776061026631943744091905444389216947450
40534976206835742715124580184913825944485873842245
44725954163382645029460350557081647367325232751881
23944982921609000437359567501588754878872290232176)
(
(Ell_certif
9758363861262100005011065186172171907551501609
360866384
((27041487636216345396724441079320271749,1)::nil)
100
0
20
100)
::
(Ell_certif
27041487636216345396724441079320271749
17640
((1532964151712944749995301930939497,1)::nil)
27041487636216345396724441079320268149
0
240
3600)
::
(Ell_certif
1532964151712944749995301930939497
11198922432
((136884969158517056128193,1)::nil)
1532964151712944749995301173355593
8234810772496
0
2869636)
::
(SPock_certif
136884969158517056128193
2
((2268109907849235421, 1)::nil))
::
(SPock_certif
2268109907849235421
2
((12600610599162419, 1)::nil))
::
(SPock_certif
12600610599162419
2
((409355789, 1)::nil))
:: (Proof_certif 409355789 prime409355789) :: nil)).
vm_cast_no_check (refl_equal true).
Time Qed.