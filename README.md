### CPP_Lisp2

CPP_Lisp means C++ Lisp and is implemented in the C++ language.
I started writing CPP_Lisp because I wanted to create a my own Lisp reader & printer, but it failed.
I tried it again and succeeded with CPP_Lisp2.
Object-oriented programming in C++ is very expressive, and as a result, completed Lisp reader & printer is now easy to understand.
CPP_Lisp2 reads S-expression from the keyboard and builds a list structure on the heap, and after that, print it as S-expression.
CPP_Lisp2 has a reference counter type garbage collector that can free cells that are no longer needed.
This garbage collector is still experimental and will be tuned for future use.

The Lisp reader & printer managed to work, so I became a little greedy and ported the interpreter described in Paul Graham's "The Roots of Lisp".
Now Lisp system works, I'll publish the source code.

### Usage:
make read_test  
./a.out  
```
> (let ((n 0))
>   (while (< n 10)
>     (print n)
>     (setq n (+ n 1))))
[str] (let ((n 0))   (while (< n 10)     (print n)     (setq n (+ n 1))))
[exp] (let ((n 0)) (while (< n 10) (print n) (setq n (+ n 1))))
0
1
2
3
4
5
6
7
8
9
[eval] 10
 ---------- atoms ----------
* + - / 1+ 1- < <= = >
>= abs acos add and append apply asin assoc atan
atom caaar caadr caar cadar caddar caddr cadr car cdaar
cdadr cdar cddar cdddar cdddr cddr cdr closure cond cons
const_e const_pi cos cosh dec defun div eq eqn exp
floor funcall gt gte if inc label lambda let let*
list ln log lt lte max min mod mul n
nil nondef not null pow print quote rassoc reverse round
setq sin sinh sqrt sub symbol-value t tan tanh trunc
while
[exp] Delete Object [Class ID]= 4Cell

> (let* ((x 10)
>        (y (* 2 x)))
>   (print x)
>   (print y)
>   (cons x y))
[str] (let* ((x 10)        (y (* 2 x)))   (print x)   (print y)   (cons x y))
[exp] (let* ((x 10) (y (* 2 x))) (print x) (print y) (cons x y))
10
20
[eval] (10 . 20)
 ---------- atoms ----------
* + - / 1+ 1- < <= = >
>= abs acos add and append apply asin assoc atan
atom caaar caadr caar cadar caddar caddr cadr car cdaar
cdadr cdar cddar cdddar cdddr cddr cdr closure cond cons
const_e const_pi cos cosh dec defun div eq eqn exp
floor funcall gt gte if inc label lambda let let*
list ln log lt lte max min mod mul n
nil nondef not null pow print quote rassoc reverse round
setq sin sinh sqrt sub symbol-value t tan tanh trunc
while x y
[exp] Delete Object [Class ID]= 4Cell

> (defun make-variable-c ()
>   (let ((c 0))
>     (list
>       (closure () c)
>       (closure () (setq c (+ c 1)))
>       (closure () (setq c (- c 1))))))
[str] (defun make-variable-c ()   (let ((c 0))     (list       (closure () c)       (closure () (setq c (+ c 1)))       (closure () (setq c (- c 1))))))
[exp] (defun make-variable-c nil (let ((c 0)) (list (closure nil c) (closure nil (setq c (+ c 1))) (closure nil (setq c (- c 1))))))
[eval] make-variable-c
 ---------- atoms ----------
* + - / 1+ 1- < <= = >
>= abs acos add and append apply asin assoc atan
atom c caaar caadr caar cadar caddar caddr cadr car
cdaar cdadr cdar cddar cdddar cdddr cddr cdr closure cond
cons const_e const_pi cos cosh dec defun div eq eqn
exp floor funcall gt gte if inc label lambda let
let* list ln log lt lte make-variable-c max min mod
mul n nil nondef not null pow print quote rassoc
reverse round setq sin sinh sqrt sub symbol-value t tan
tanh trunc while x y
[exp] Delete Object [Class ID]= 4Cell

> (let* ((funcs (make-variable-c))
>        (c 1000)
>        (get-c (car funcs))
>        (inc-c (cadr funcs))
>        (dec-c (caddr funcs)))
>   (print (funcall get-c))
>   (funcall inc-c)
>   (print (funcall get-c))
>   (funcall dec-c)
>   (funcall dec-c)
>   (print (funcall get-c)))
[str] (let* ((funcs (make-variable-c))        (c 1000)        (get-c (car funcs))        (inc-c (cadr funcs))        (dec-c (caddr funcs)))   (print (funcall get-c))   (funcall inc-c)   (print (funcall get-c))   (funcall dec-c)   (funcall dec-c)   (print (funcall get-c)))
[exp] (let* ((funcs (make-variable-c)) (c 1000) (get-c (car funcs)) (inc-c (cadr funcs)) (dec-c (caddr funcs))) (print (funcall get-c)) (funcall inc-c) (print (funcall get-c)) (funcall dec-c) (funcall dec-c) (print (funcall get-c)))
0
1
-1
[eval] -1
 ---------- atoms ----------
* + - / 1+ 1- < <= = >
>= abs acos add and append apply asin assoc atan
atom c caaar caadr caar cadar caddar caddr cadr car
cdaar cdadr cdar cddar cdddar cdddr cddr cdr closure cond
cons const_e const_pi cos cosh dec dec-c defun div eq
eqn exp floor funcall funcs get-c gt gte if inc
inc-c label lambda let let* list ln log lt lte
make-variable-c max min mod mul n nil nondef not null
pow print quote rassoc reverse round setq sin sinh sqrt
sub symbol-value t tan tanh trunc while x y
[exp] Delete Object [Class ID]= 4Cell
```
