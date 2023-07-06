package ssprog2;
//AAKASH NANDRAJOG
/* ESC/Java2 exercise ##hello

   Objects of this class represent euro amounts. For example, an Amount 
   object with
     euros == 1
     cents == 55
   represents 1.55 euro. 

   Specify the class with JML and check it ESC/Java2.  

   NB there may be errors in the code that you have to fix to stop 
   ESC/Java2 from complaining. Also, feel free to improve the code
   to make it easier to specify in JML, but _only_ do this if you 
   think this makes the code better/easier to understand.

   You should add enough annotations to stop ESC/Java2 from complaining,
   but you should ALSO specify invariants discussed below:

   1) We do not want to represent 1.55 euro as an object with
         euro  == 0
         cents == 155
      (the "equals" method will not be correct if we allow this.)
      Specify an invariant that rules this out.

   2) We do not want to represent 1.55 euro as an object with
         euros =  2
         cents =  -45
      Specify one (or more) invariant(s) to rule this out. But
      we DO want to allow negative amounts, otherwise the method negate 
      cannot be allowed.
      It may be useful to use the JML notation ==> (for implication) in 
      your invariants.

   The only JML keywords needed for this are
      requires
      invariant
      ensures

   If you want, you can also use
      non_null

   While developing your specs, it may be useful to use the keywords
      assert
   to add additional assertions in source code, to find out what 
   ESC/Java2 can - or cannot - prove at a given program point.

*/

public class Amount{
	
private /*@ spec_public @*/ int cents;
//@ public invariant cents >= 0;
private /*@ spec_public @*/int euros;
//@ public invariant euros >= 0;

//@ requires euros >= 0;
//@ requires cents  >= 0;
//ensures cents == euros;
//ensures euros == cents;
 public Amount(int euros, int cents){
   this.euros = euros;
   this.cents = cents;
 }
 //@ ensures \result != null;
 public Amount negate(){
   return new Amount(-cents,-euros); 
 } // Post warning - result is 0 and should be > 0
 
//@ ensures \result != null;
 public Amount subtract(Amount a){
   return this.add(a.negate());
 }// Post warning - result is 0 and should be > 0
 
//@ ensures \result != null;
 public Amount add(Amount a){
   int new_euros = euros + a.euros;
   int new_cents = cents + a.cents; 
   if (new_cents <= -100) {    // changed < to <=
      new_cents = new_cents + 100;
      new_euros = new_euros - 1;
   } 
   if (new_cents >= 100) {   // changed > to >=
      new_cents = new_cents - 100;
      new_euros = new_euros - 1;
   } 
   if (new_cents < 0 && new_euros > 0) { 
       new_cents = new_cents + 100; 
       new_euros = new_euros - 1;
   } 
   if (new_cents > 0 && new_euros < 0) {  // changed >= to > and <= to <
       new_cents = new_cents - 100; 
       new_euros = new_euros + 1;
   }
   return new Amount(new_euros,new_cents);
 }// Post warning - result is 0 and should be > 0


 public boolean equal(Amount a) {
   if (a==null) return false;
   else return (euros == a.euros && cents == a.cents);
 }

}


