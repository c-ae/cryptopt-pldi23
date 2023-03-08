Require Import PocklingtonRefl.

Local Open Scope positive_scope.

Lemma prime115792089237316195423570985008687907853269984665640564039457584007908834671663 : prime 115792089237316195423570985008687907853269984665640564039457584007908834671663.
Proof.
 apply (Pocklington_refl
         (Pock_certif 115792089237316195423570985008687907853269984665640564039457584007908834671663 3 ((205115282021455665897114700593932402728804164701536103180137503955397371, 1)::(2,1)::nil) 1)
        ((Pock_certif 205115282021455665897114700593932402728804164701536103180137503955397371 2 ((255515944373312847190720520512484175977, 1)::(2,1)::nil) 1) ::
         (Pock_certif 255515944373312847190720520512484175977 3 ((4423, 1)::(2657, 1)::(1627, 1)::(7, 2)::(2,3)::nil) 11257515654800) ::
         (Proof_certif 4423 prime4423) ::
         (Proof_certif 2657 prime2657) ::
         (Proof_certif 1627 prime1627) ::
         (Proof_certif 7 prime7) ::
         (Proof_certif 2 prime2) ::
          nil)).
 vm_cast_no_check (refl_equal true).
Qed.