% hi
natSymb(o). % hi
natSymb(s(A)) :- natSymb(A). % wenn A ein natsymb ist, muss auch s(A) eins sein
 
%I.A.
add(o, A, A).
 
%I.S.: quasi "umschichten". B wird abgebaut, A aufgebaut fuer jeden Schritt
add(s(A), B, C) :- natSymb(A), natSymb(B), natSymb(C), add(A, s(B), C).
 
%I.A.
mult(o, X, o).
%I.S.: siehe Übung 1
mult(s(A), B, C) :- mult(A, B, D), add(D, B, C).
 
% X mit o addiert muss wieder o sein, dann gilt X=0
%eqZero(X) :-  natSymb(X), add(o, X, o).
 
%o equals zero. always.
eqZero(o).
 
%wenn A ein natSymb ist, ist s(A) auch eins. Da es natSymb nur fuer A>0 gibt, ist diese
%Bedingung nur erfuellt, wenn A > 0
neqZero(s(X)) :-  natSymb(X).
 
less(o, s(A)).
less(s(X), s(s(Y))) :- less(X, s(Y)), natSymb(X), natSymb(Y).
 
square(X, Y) :- mult(X, X, Y).
 
exp(A, o, s(o)).
 
%y mal x miteinander multen x^y = B
exp(X, s(Y), B) :- exp(X, Y, A), mult(A, X, B), natSymb(X), natSymb(Y), natSymb(B).
 
log(X, Y, A) :- exp(X, A, Y).
 
 
% list(o, list(s(o), list(s(s(o)), nil))).
 
natList(nil).
natList(list(A, T)) :- natSymb(A), natList(T).
 
invList(list(o, nil)).
invList(list(s(A), list(A, B))) :- invList(list(A, B)).
 
% A ist head von Bs
head(list(A, Bs), A) :- natList(Bs).
tail(list(A, Bs), Bs) :- natList(Bs).
 
appendl(nil, As, As).
appendl(list(D, As), Bs, list(D, Cs)) :- appendl(As, Bs, Cs).
 
% Aufgabe 20
% Die leere Liste hat keine Elemente
anz(nil, o).
% wenn Xs N Elemente hat, dann hat Xs mit einem Element davor ein Element mehr
anz(list(A_Y, Xs), s(N)) :- anz(Xs, N).
 
% Aufgabe 21
% baum: nib ist der leere baum
binbaum(nib).
% wenn Ab und Bb Teilbaeume sind, dann kann der naechsthoehere Baum diese beiden enthalten
binbaum(knoten(A, Ab, Bb)) :- binbaum(Ab), binbaum(Bb).
 
% root(Xb, Y) :- Y ist der Wurzeleintrag des binaerbaums Xb
root(binbaum(knoten(X, Ab, Bb)), X) :- binbaum(Ab), binbaum(Bb).
 
% left(Xb, Yb) :- Yb ist der linke Teilbaum von Xb.
left(binbaum(knoten(A_X, Ab, Bb)), Ab) :- binbaum(Ab), binbaum(Bb).
 
% right(Xb, Yb) :- Yb ist der rechte Teilbaum von Xb
right(binbaum(knoten(A_X, Ab, Bb)), Bb) :- binbaum(Ab), binbaum(Bb).
