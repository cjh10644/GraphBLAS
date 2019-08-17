function gbtest10
%GBTEST10 test gb.assign

% SuiteSparse:GraphBLAS, Timothy A. Davis, (c) 2017-2019, All Rights Reserved.
% http://suitesparse.com   See GraphBLAS/Doc/License.txt for license.

rng ('default') ;

n = 6 ;
A = 100 * sprand (n, n, 0.5) ;
AT = A' ;
M = sparse (rand (n)) > 0.5 ;
Cin = sprand (n, n, 0.5) ;


Cout = gb.assign (Cin, A) ;
assert (isequal (A, double (Cout))) ;

Cout = gb.assign (Cin, A, { }, { }) ;
assert (isequal (A, double (Cout))) ;

Cout = gb.assign (Cin, M, A) ;
C2 = Cin ;
C2 (M) = A (M) ;
assert (isequal (C2, double (Cout))) ;

Cout = gb.assign (Cin, '+', A) ;
C2 = Cin + A ;
assert (isequal (C2, double (Cout))) ;

d.in0 = 'transpose' ;
Cout = gb.assign (Cin, M, A, d) ;
C2 = Cin ;
C2 (M) = AT (M) ;
assert (isequal (C2, double (Cout))) ;

Cout = gb.assign (Cin, '+', A, d) ;
C2 = Cin + AT ;
assert (isequal (C2, double (Cout))) ;

d.mask = 'complement' ;
Cout = gb.assign (Cin, M, A, d) ;
C2 = Cin ;
C2 (~M) = AT (~M) ;
assert (isequal (C2, double (Cout))) ;

I = [2 1 5] ;
J = [3 3 1 2] ;
B = sprandn (length (I), length (J), 0.5) ;
Cout = gb.assign (Cin, B, {I}, {J}) ;
C2 = Cin ;
C2 (I,J) = B ;
assert (isequal (C2, double (Cout))) ;

fprintf ('gbtest10: all tests passed\n') ;
