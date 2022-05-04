### CPP_Lisp2

CPP_Lisp means C++ Lisp and is implemented in the C++ language.
I started writing CPP_Lisp because I wanted to create a my own Lisp reader, but it failed.
I tried it again and succeeded with CPP_Lisp2.
Object-oriented programming in C++ is very expressive, and as a result, Lisp readers are easy to understand.
CPP_Lisp2 reads sexp from the keyboard and builds a list structure on the heap.
CPP_Lisp2 has a reference counter type garbage collector that can free cells that are no longer needed.
This garbage collector is still experimental and will be tuned for future use.

The Lisp reader managed to work, so I became a little greedy and ported the interpreter described in Paul Graham's "The Roots of Lisp".
Now that it works, I'll publish the source code.

### Usage:
make read_test  
./a.out  

> (append '(1 2 3) '(4 5 6))  
[str] (append (quote (1 2 3)) (quote (4 5 6)))  
[exp] (append (quote (1 2 3)) (quote (4 5 6)))  
[eval] (1 2 3 4 5 6)  
 ---------- atoms ----------  
and append atom caar cadar caddar caddr cadr car cdr  
cond cons eq label lambda list nil not null quote  
reverse t  
[exp] Delete Object [Class ID]= 4Cell  
[eval] Delete Object [Class ID]= 4Cell  

> (reverse '(1 2 3 4 5 6))  
[str] (reverse (quote (1 2 3 4 5 6)))  
[exp] (reverse (quote (1 2 3 4 5 6)))  
[eval] (6 5 4 3 2 1)  
 ---------- atoms ----------  
and append atom caar cadar caddar caddr cadr car cdr  
cond cons eq label lambda list nil not null quote  
reverse t  
[exp] Delete Object [Class ID]= 4Cell  
[eval] Delete Object [Class ID]= 4Cell  

> ((label subst (lambda (x y z) (cond ((atom z) (cond ((eq z y) x) ('t z))) ('t (cons (subst x y (car z)) (subst x y (cdr z))))))) 'm 'b '(a b (a b c) d))  
[str] ((label subst (lambda (x y z) (cond ((atom z) (cond ((eq z y) x) ((quote t) z))) ((quote t) (cons (subst x y (car z)) (subst x y (cdr z))))))) (quote m) (quote b) (quote (a b (a b c) d)))  
[exp] ((label subst (lambda (x y z) (cond ((atom z) (cond ((eq z y) x) ((quote t) z))) ((quote t) (cons (subst x y (car z)) (subst x y (cdr z))))))) (quote m) (quote b) (quote (a b (a b c) d)))  
[eval] (a m (a m c) d)  
 ---------- atoms ----------  
a and append atom b c caar cadar caddar caddr  
cadr car cdr cond cons d eq label lambda list  
m nil not null quote reverse subst t x y  
z  
[exp] Delete Object [Class ID]= 4Cell  
[eval] Delete Object [Class ID]= 4Cell  
