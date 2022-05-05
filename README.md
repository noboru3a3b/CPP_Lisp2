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
```
> (append '(1 2 3) '(4 5 6))  
[str] (append (quote (1 2 3)) (quote (4 5 6)))  
[exp] (append (quote (1 2 3)) (quote (4 5 6)))  
[eval] (1 2 3 4 5 6)  
 ---------- atoms ----------  
* + - / < <= = > >= add  
and append atom caaar caadr caar cadar caddar caddr cadr  
car cdaar cdadr cdar cddar cdddr cddr cdr cond cons  
div eq eqn gt gte if label lambda list lt  
lte mod mul nil not null quote reverse sub t  

[exp] Delete Object [Class ID]= 4Cell  
[eval] Delete Object [Class ID]= 4Cell  

> (reverse '(1 2 3 4 5 6))  
[str] (reverse (quote (1 2 3 4 5 6)))  
[exp] (reverse (quote (1 2 3 4 5 6)))  
[eval] (6 5 4 3 2 1)  
 ---------- atoms ----------  
* + - / < <= = > >= add  
and append atom caaar caadr caar cadar caddar caddr cadr  
car cdaar cdadr cdar cddar cdddr cddr cdr cond cons  
div eq eqn gt gte if label lambda list lt  
lte mod mul nil not null quote reverse sub t  

[exp] Delete Object [Class ID]= 4Cell  
[eval] Delete Object [Class ID]= 4Cell  

> ((label sqr+ (lambda (x y) (if (null x) y (sqr+ (cdr x) (+ (* (car x) (car x)) y))))) '(1 2 3 4 5) 0)  
[str] ((label sqr+ (lambda (x y) (if (null x) y (sqr+ (cdr x) (+ (* (car x) (car x)) y))))) (quote (1 2 3 4 5)) 0)  
[exp] ((label sqr+ (lambda (x y) (if (null x) y (sqr+ (cdr x) (+ (* (car x) (car x)) y))))) (quote (1 2 3 4 5)) 0)  
[eval] 55  
 ---------- atoms ----------  
* + - / < <= = > >= add  
and append atom caaar caadr caar cadar caddar caddr cadr  
car cdaar cdadr cdar cddar cdddr cddr cdr cond cons  
div eq eqn gt gte if label lambda list lt  
lte mod mul nil not null quote reverse sqr+ sub  
t x y  
[exp] Delete Object [Class ID]= 4Cell  
[eval] Delete Object [Class ID]= 4Cell  
```
