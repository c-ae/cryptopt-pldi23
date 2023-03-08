Require Import Ltac2.Ltac2.
Require Import Ltac2.Bool. (* for && and || notation *)
Require Import Ltac2.Printf. (* for printf *notation* rather than function *)

Ltac2 mkApp(f: constr)(args: constr array) :=
  Constr.Unsafe.make (Constr.Unsafe.App f args).

(* Remove once https://github.com/coq/coq/issues/13976 is fixed *)
Local Ltac2 Notation "[|" l(list0(tactic(5), ";")) "|]" : 0 := Array.of_list l.

Ltac2 Type exn ::= [ Atom_to_cancel_not_found ].

(* non-backtracking version of Control.plus, similar to Ltac1's first,
   but returning a value, and only considering Atom_to_cancel_not_found *)
Ltac2 or_else(t1: unit -> 'a)(t2: unit -> 'a) :=
  match Control.case t1 with
  | Val p => let (x, _) := p in x
  | Err e =>
      match e with
      | Atom_to_cancel_not_found => t2 ()
      | _ => Control.zero e
      end
  end.

Ltac2 try_transform(f: 'a -> 'a)(arg: 'a) := or_else (fun _ => f arg) (fun _ => arg).

Ltac2 get_last(arr: 'a array) :=
  let l := Array.length arr in (Array.get arr (Int.sub l 1)).

Ltac2 set_last(arr: 'a array)(x: 'a) :=
  let l := Array.length arr in (Array.set arr (Int.sub l 1) x).

Ltac2 get_2nd_last(arr: 'a array) :=
  let l := Array.length arr in (Array.get arr (Int.sub l 2)).

Ltac2 set_2nd_last(arr: 'a array)(x: 'a) :=
  let l := Array.length arr in (Array.set arr (Int.sub l 2) x).

Ltac2 update_elem(f: 'a -> 'a)(arr: 'a array)(i: int) :=
  Array.set arr i (f (Array.get arr i)).

Ltac2 update_last(f: 'a -> 'a)(arr: 'a array) :=
  let l := Array.length arr in update_elem f arr (Int.sub l 1).

Ltac2 update_2nd_last(f: 'a -> 'a)(arr: 'a array) :=
  let l := Array.length arr in update_elem f arr (Int.sub l 2).

Ltac2 extract_addsub_atoms(add: constr)(sub: constr)(opp: constr)(e: constr) :=
  let rec r e acc :=
    match Constr.Unsafe.kind e with
    | Constr.Unsafe.App f args =>
        if Constr.equal f add || Constr.equal f sub
        then r (get_2nd_last args) (r (get_last args) acc)
        else if  Constr.equal f opp then r (get_last args) acc
        else e :: acc (* note: no deduplication, because if the same atom appears
                         eg 4 times, it might be cancelable twice *)
    | _ => e :: acc
    end in
  r e [].

Ltac2 cancel_addsub_atom(add: constr)(sub: constr)(opp: constr)(zero: constr)
  (atom: constr)(e: constr) :=

  let mkAdd args := Constr.Unsafe.make
    (match Constr.Unsafe.kind (get_last args) with
     | Constr.Unsafe.App f inner_args =>
         if Constr.equal f opp then (* a + - b --> a - b *)
           set_last args (get_last inner_args);
           Constr.Unsafe.App sub args
         else Constr.Unsafe.App add args
     | _ => Constr.Unsafe.App add args
     end) in

  let mkSub args := Constr.Unsafe.make
    (match Constr.Unsafe.kind (get_last args) with
     | Constr.Unsafe.App f inner_args =>
         if Constr.equal f opp then (* a - - b --> a + b *)
           set_last args (get_last inner_args);
           Constr.Unsafe.App add args
         else Constr.Unsafe.App sub args
     | _ => Constr.Unsafe.App sub args
     end) in

  let mkOpp args :=
    match Constr.Unsafe.kind (get_last args) with
    | Constr.Unsafe.App f inner_args =>
        if Constr.equal f opp then (* - - a --> a *)
          get_last inner_args
        else Constr.Unsafe.make (Constr.Unsafe.App opp args)
     | _ => Constr.Unsafe.make (Constr.Unsafe.App opp args)
     end in

  let rec matches remove_opp candidate :=
    match Constr.Unsafe.kind candidate with
    | Constr.Unsafe.App f args =>
        if Constr.equal f opp then matches (Bool.neg remove_opp) (get_last args)
        else Bool.neg remove_opp && Constr.equal candidate atom
    | _ => Bool.neg remove_opp && Constr.equal candidate atom
    end in

  let rec r remove_opp e :=
    if matches remove_opp e then zero else
    match Constr.Unsafe.kind e with
    | Constr.Unsafe.App f args =>
        if Constr.equal f add then
          if matches remove_opp (get_2nd_last args) then get_last args
          else if matches remove_opp (get_last args) then get_2nd_last args
          else (or_else (fun _ => update_2nd_last (r remove_opp) args)
                        (fun _ => update_last (r remove_opp) args);
                mkAdd args)
        else if Constr.equal f sub then
          if matches remove_opp (get_2nd_last args) then
            let args' := Array.sub args 0 (Int.sub (Array.length args) 1) in
            set_last args' (get_last args);
            mkOpp args'
          else if matches (Bool.neg remove_opp) (get_last args) then
            get_2nd_last args
          else
            (or_else (fun _ => update_2nd_last (r remove_opp) args)
                     (fun _ => update_last (r (Bool.neg remove_opp)) args);
             mkSub args)
        else if Constr.equal f opp then
          (update_last (r (Bool.neg remove_opp)) args; mkOpp args)
        else Control.zero Atom_to_cancel_not_found
    | _ => Control.zero Atom_to_cancel_not_found
    end in

  r true (r false e).

(* TODO maybe also eliminate x+0, 0+x, x-0, 0-x?
   OR more generally, collect and simplify all constants? (needed by Softmul) *)
Ltac2 cancel_addsub_unproven(add: constr)(sub: constr)(opp: constr)(zero: constr)
  (e: constr) :=
  let rec r atoms e :=
    match atoms with
    | [] => e
    | atom :: rest => r rest (try_transform (cancel_addsub_atom add sub opp zero atom) e)
    end in
  r (extract_addsub_atoms add sub opp e) e.

Require Import Coq.ZArith.ZArith.
Require Import coqutil.Word.Interface coqutil.Word.Properties.
Local Open Scope Z_scope.

Lemma combine_app_eq: forall (A B: Type) (f1 f2: A -> B) (x1 x2: A),
    f1 = f2 -> x1 = x2 -> f1 x1 = f2 x2.
Proof. intros. subst. reflexivity. Qed.

(* to be used once at top-level for each Prop,
   potentially with pf=eq_refl but P1<>P2 (but convertible) *)
Lemma rew_Prop_hyp: forall (P1 P2: Prop) (pf: P1 = P2), P1 -> P2.
Proof. intros. subst. assumption. Qed.

Lemma rew_Prop_goal: forall (P1 P2: Prop) (pf: P1 = P2), P2 -> P1.
Proof. intros. subst. assumption. Qed.

(* returns (rhs, pf) such that pf is of type `e = rhs`.
   TODO: if the atoms of a Z or word expression contain again a Z or word expression
   further down, also recurse into these (or unnecessary?) *)
Ltac2 rec cancel_addsub(e: constr) :=
  let isZ := match! e with
             | Z.add _ _ => true
             | Z.sub _ _ => true
             | Z.opp _ => true
             | _ => false
             end in
  if isZ then
    let e' := cancel_addsub_unproven 'Z.add 'Z.sub 'Z.opp 'Z0 e in
    if Constr.equal e e' then (e, mkApp '@eq_refl [| 'Z;  e |])
    else (e', constr:(ltac:(ring) : $e = $e'))
  else
    let w := match! e with
             | @word.add ?wi ?wo _ _ => Some (wi, wo)
             | @word.sub ?wi ?wo _ _ => Some (wi, wo)
             | @word.opp ?wi ?wo _ _ => Some (wi, wo)
             | _ => None
             end in
    match w with
    | Some p =>
      let (wi, wo) := p in
      let e' := cancel_addsub_unproven '@word.add '@word.sub '@word.opp
                                       '(@word.of_Z $wi $wo 0) e in
      if Constr.equal e e' then (e, mkApp '@eq_refl [| '(@word.rep $wi $wo);  e |])
      else (e', constr:(ltac:(ring) : $e = $e'))
    | None =>
      match! e with
      | ?f ?a =>
          let (f', eq1) := cancel_addsub f in
          let (a', eq2) := cancel_addsub a in
          (mkApp f' [| a' |],
           (* mkApp '@combine_app_eq [| '_; '_; f; f'; a; a'; eq1; eq2 |]
              doesn't work and creates evars for _ that are never instantiated
              instead of holes that are instantiated on typechecking *)
           constr:(combine_app_eq _ _ $f $f' $a $a' $eq1 $eq2))
      | _ => (e, constr:(eq_refl $e))
      end
    end.

Ltac2 cancel_addsub_in_hyp(h: ident) :=
  let t := Constr.type (Control.hyp h) in
  let (t', pf) := cancel_addsub t in
  eapply (rew_Prop_hyp $t $t' $pf) in $h.

Ltac2 cancel_addsub_in_goal() :=
  let t := Control.goal () in
  let (t', pf) := cancel_addsub t in
  eapply (rew_Prop_goal $t $t' $pf).

(* Given a goal "t = e" where e is an evar, instantiates e to a simplified
   version of t and proves the equality, failing if no simplification is possible *)
Ltac2 cancel_addsub_input_in_goal () :=
  lazy_match! goal with
  | [ |- ?t = _ ] =>
      let (t', pf) := cancel_addsub t in
      if Constr.equal t t' then Control.backtrack_tactic_failure "nothing to cancel"
      else exact $pf
  end.

Ltac cancel_addsub_in_hyp H :=
  eapply rew_Prop_hyp in H; [ | ltac2:(cancel_addsub_input_in_goal ()) ].

Ltac cancel_addsub_in_goal :=
  eapply rew_Prop_goal; [ ltac2:(cancel_addsub_input_in_goal ()) | ].

Local Set Ltac2 Backtrace.

Section Tests.

  Declare Scope word_scope.
  Local Open Scope word_scope.
  Import List.ListNotations.

  Local Infix "^+" := word.add  (at level 50, left associativity) : word_scope.
  Local Infix "^-" := word.sub  (at level 50, left associativity) : word_scope.

  Context {word: word.word 32} {word_ok: word.ok word}.

  Add Ring wring : (Properties.word.ring_theory (word := word))
      ((* too expensive: preprocess [autorewrite with rew_word_morphism], *)
       morphism (Properties.word.ring_morph (word := word)),
       constants [Properties.word_cst]).

  Hypothesis P: Z -> Prop.
  Hypothesis Q: forall T, list T -> Z.
  Arguments Q [_] _.

  Goal forall (a b c x y z: word) (a0 x0 y0 z0: Z),
      P ((a0 + ((x0 - y0) + z0)) - x0 - z0) ->
      Q [ (a ^+ word.of_Z 8 ^- a);
          (a ^+ word.of_Z 8 ^- (word.opp b) ^+ b);
          (a ^- (b ^+ b) ^+ word.of_Z 8 ^- (word.opp b) ^+ b);
          (word.opp (b ^+ b) ^+ a ^+ word.of_Z 8 ^- (word.opp b) ^+ b);
          (word.opp y ^+ (x ^+ (y ^- z)));
          ((a ^+ ((x ^- y) ^+ z)) ^- x ^- z);
          a ^- a ] =
        Q [(a0 + ((x0 - y0) + z0)) - (x0 + z0); a0 - a0; -a0 - - - - a0] ->
      P (a0 - y0) /\
        Q [word.of_Z 8; a ^+ word.of_Z 8 ^- word.opp b ^+ b; a ^+ word.of_Z 8;
           a ^+ word.of_Z 8; x ^- z; a ^- y; word.of_Z 0] = Q [- x0 + a0 - y0 + x0; 0; 0].
  Proof.
    intros.
    cancel_addsub_in_hyp @H.
    cancel_addsub_in_hyp @H0.
    cancel_addsub_in_goal ().
    split; assumption.
  Abort.

  Set Default Proof Mode "Classic".

  Goal forall (a0 x0 y0 z0: Z),
      P ((a0 + ((x0 - y0) + z0)) - x0 - z0) ->
      P (-x0 + a0 - y0 + x0).
  Proof.
    intros * A.
    cancel_addsub_in_hyp A.
    cancel_addsub_in_goal.
    exact A.
  Abort.
End Tests.
