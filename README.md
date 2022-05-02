### CPP_Lisp2

CPP_Lisp means C++ Lisp and is implemented in the C++ language.
I started writing CPP_Lisp because I wanted to create a my own Lisp reader, but it failed.
I tried it again and succeeded with CPP_Lisp2.
Object-oriented programming in C++ is very expressive, and as a result, Lisp readers are easy to understand.
CPP_Lisp2 reads sexp from the keyboard and builds a list structure on the heap.
CPP_Lisp2 has a reference counter type garbage collector that can retrieve cells that are no longer needed.
This garbage collector is still experimental and will be tuned for future use.

The Lisp reader managed to work, so I became a little greedy and ported the interpreter described in Paul Graham's "The Roots of Lisp".
Now that it works, I'll publish the source code.

### Usage:
make read_test  
./a.out  

> (append '(100 200 300) '(aaa bbb ccc))  <--- Input  
[str] (append (quote (100 200 300)) (quote (aaa bbb ccc)))  
[exp] (append (quote (100 200 300)) (quote (aaa bbb ccc)))  
[eval] (100 200 300 aaa bbb ccc)          <--- Output  
 ---------- atoms ----------  
aaa append atom bbb car ccc cdr cond cons eq   
label lambda nil not null quote t  
Delete Object [Class ID]= 4Cell  
Delete Object [Class ID]= 4Cell  

> ((label subst (lambda (x y z) (cond ((atom z) (cond ((eq z y) x) ('t z))) ('t (cons (subst x y (car z)) (subst x y (cdr z))))))) 'm 'b '(a b (a b c) d))     <--- Input  
[str] ((label subst (lambda (x y z) (cond ((atom z) (cond ((eq z y) x) ((quote t) z))) ((quote t) (cons (subst x y (car z)) (subst x y (cdr z))))))) (quote m) (quote b) (quote (a b (a b c) d)))  
[exp] ((label subst (lambda (x y z) (cond ((atom z) (cond ((eq z y) x) ((quote t) z))) ((quote t) (cons (subst x y (car z)) (subst x y (cdr z))))))) (quote m) (quote b) (quote (a b (a b c) d)))  
[eval] (a m (a m c) d)   <--- Output  
 ---------- atoms ----------  
a aaa append atom b bbb c car ccc cdr  
cond cons d eq label lambda m nil not null  
quote subst t x y z  
Delete Object [Class ID]= 4Cell  
Delete Object [Class ID]= 4Cell  
