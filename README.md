### CPP_Lisp2

CPP_Lisp means C++ Lisp and is implemented in the C++ language.
I started writing CPP_Lisp because I wanted to create a my own Lisp reader & printer, but it failed.
I tried it again and succeeded with CPP_Lisp2.
Object-oriented programming in C++ is very expressive, and as a result, completed Lisp reader & printer is now easy to understand.
CPP_Lisp2 reads S-expression from the keyboard and builds a list structure on the heap, and after that, print it as S-expression.
CPP_Lisp2 has a reference counter type garbage collector that can free cells that are no longer needed.
This garbage collector is still experimental and will be tuned for future use.

The Lisp reader & printer managed to work, so I became a little greedy and ported the interpreter described in Paul Graham's "The Roots of Lisp".
To make a reasonably usable Lisp system, I made a slight expansion.
Now Lisp system works, I'll publish the source code.

### Usage:
make read_test  
./a.out  
```
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
* + - / 0= 1+ 1- < <= =
> >= abs acos add and append apply asin assoc
atan atom c caaar caadr caar cadar caddar caddr cadr
car cdaar cdadr cdar cddar cdddar cdddr cddr cdr closure
cond cons const_e const_pi cos cosh dec defun div eq
eqn exp floor funcall gt gte if inc label lambda
let let* list ln log lt lte make-variable-c max min
mod mul nil nondef not null pow print quote rassoc
reverse round setcar setcdr setq sin sinh sqrt sub symbol-value
t tan tanh trunc while zerop

> (let* ((funcs (make-variable-c))
>        (get-c (car funcs))
>        (inc-c (cadr funcs))
>        (dec-c (caddr funcs)))
>   (print (funcall get-c))
>   (funcall inc-c)
>   (print (funcall get-c))
>   (funcall dec-c)
>   (print (funcall get-c)))
[str] (let* ((funcs (make-variable-c))        (get-c (car funcs))        (inc-c (cadr funcs))        (dec-c (caddr funcs)))   (print (funcall get-c))   (funcall inc-c)   (print (funcall get-c))   (funcall dec-c)   (print (funcall get-c)))
[exp] (let* ((funcs (make-variable-c)) (get-c (car funcs)) (inc-c (cadr funcs)) (dec-c (caddr funcs))) (print (funcall get-c)) (funcall inc-c) (print (funcall get-c)) (funcall dec-c) (print (funcall get-c)))
0
1
0
[eval] 0
 ---------- atoms ----------
* + - / 0= 1+ 1- < <= =
> >= abs acos add and append apply asin assoc
atan atom c caaar caadr caar cadar caddar caddr cadr
car cdaar cdadr cdar cddar cdddar cdddr cddr cdr closure
cond cons const_e const_pi cos cosh dec dec-c defun div
eq eqn exp floor funcall funcs get-c gt gte if
inc inc-c label lambda let let* list ln log lt
lte make-variable-c max min mod mul nil nondef not null
pow print quote rassoc reverse round setcar setcdr setq sin
sinh sqrt sub symbol-value t tan tanh trunc while zerop

> (defun make-queue ()
>   (let ((queue (cons nil nil)))
>     (setcar queue queue)
>     queue))
[str] (defun make-queue ()   (let ((queue (cons nil nil)))     (setcar queue queue)     queue))
[exp] (defun make-queue nil (let ((queue (cons nil nil))) (setcar queue queue) queue))
[eval] make-queue
 ---------- atoms ----------
* + - / 0= 1+ 1- < <= =
> >= abs acos add and append apply asin assoc
atan atom c caaar caadr caar cadar caddar caddr cadr
car cdaar cdadr cdar cddar cdddar cdddr cddr cdr closure
cond cons const_e const_pi cos cosh dec dec-c defun div
eq eqn exp floor funcall funcs get-c gt gte if
inc inc-c label lambda let let* list ln log lt
lte make-queue make-variable-c max min mod mul nil nondef not
null pow print queue quote rassoc reverse round setcar setcdr
setq sin sinh sqrt sub symbol-value t tan tanh trunc
while zerop

> (defun en-queue (queue x)
>   (let ((q (cons x nil)))
>     (setcdr (car queue) q)
>     (setcar queue q)
>     queue))
[str] (defun en-queue (queue x)   (let ((q (cons x nil)))     (setcdr (car queue) q)     (setcar queue q)     queue))
[exp] (defun en-queue (queue x) (let ((q (cons x nil))) (setcdr (car queue) q) (setcar queue q) queue))
[eval] en-queue
 ---------- atoms ----------
* + - / 0= 1+ 1- < <= =
> >= abs acos add and append apply asin assoc
atan atom c caaar caadr caar cadar caddar caddr cadr
car cdaar cdadr cdar cddar cdddar cdddr cddr cdr closure
cond cons const_e const_pi cos cosh dec dec-c defun div
en-queue eq eqn exp floor funcall funcs get-c gt gte
if inc inc-c label lambda let let* list ln log
lt lte make-queue make-variable-c max min mod mul nil nondef
not null pow print q queue quote rassoc reverse round
setcar setcdr setq sin sinh sqrt sub symbol-value t tan
tanh trunc while x zerop

> (defun get-list (queue) (cdr queue))
[str] (defun get-list (queue) (cdr queue))
[exp] (defun get-list (queue) (cdr queue))
[eval] get-list
 ---------- atoms ----------
* + - / 0= 1+ 1- < <= =
> >= abs acos add and append apply asin assoc
atan atom c caaar caadr caar cadar caddar caddr cadr
car cdaar cdadr cdar cddar cdddar cdddr cddr cdr closure
cond cons const_e const_pi cos cosh dec dec-c defun div
en-queue eq eqn exp floor funcall funcs get-c get-list gt
gte if inc inc-c label lambda let let* list ln
log lt lte make-queue make-variable-c max min mod mul nil
nondef not null pow print q queue quote rassoc reverse
round setcar setcdr setq sin sinh sqrt sub symbol-value t
tan tanh trunc while x zerop

> (defun is-prime (p-list x)
>   (if (null p-list) t
>       (let ((p (car p-list)))
>         (cond ((gt (mul p p) x) t)
>               ((zerop (mod x p)) nil)
>               (t (is-prime (cdr p-list) x))))))
[str] (defun is-prime (p-list x)   (if (null p-list) t       (let ((p (car p-list)))         (cond ((gt (mul p p) x) t)               ((zerop (mod x p)) nil)               (t (is-prime (cdr p-list) x))))))
[exp] (defun is-prime (p-list x) (if (null p-list) t (let ((p (car p-list))) (cond ((gt (mul p p) x) t) ((zerop (mod x p)) nil) (t (is-prime (cdr p-list) x))))))
[eval] is-prime
 ---------- atoms ----------
* + - / 0= 1+ 1- < <= =
> >= abs acos add and append apply asin assoc
atan atom c caaar caadr caar cadar caddar caddr cadr
car cdaar cdadr cdar cddar cdddar cdddr cddr cdr closure
cond cons const_e const_pi cos cosh dec dec-c defun div
en-queue eq eqn exp floor funcall funcs get-c get-list gt
gte if inc inc-c is-prime label lambda let let* list
ln log lt lte make-queue make-variable-c max min mod mul
nil nondef not null p p-list pow print q queue
quote rassoc reverse round setcar setcdr setq sin sinh sqrt
sub symbol-value t tan tanh trunc while x zerop

> (defun primes (queue x max)
>   (cond ((gt x max)
>          (cons 2 (get-list queue)))
>         ((is-prime (get-list queue) x)
>          (primes (en-queue queue x) (add x 2) max))
>         (t (primes queue (add x 2) max))))
[str] (defun primes (queue x max)   (cond ((gt x max)          (cons 2 (get-list queue)))         ((is-prime (get-list queue) x)          (primes (en-queue queue x) (add x 2) max))         (t (primes queue (add x 2) max))))
[exp] (defun primes (queue x max) (cond ((gt x max) (cons 2 (get-list queue))) ((is-prime (get-list queue) x) (primes (en-queue queue x) (add x 2) max)) (t (primes queue (add x 2) max))))
[eval] primes
 ---------- atoms ----------
* + - / 0= 1+ 1- < <= =
> >= abs acos add and append apply asin assoc
atan atom c caaar caadr caar cadar caddar caddr cadr
car cdaar cdadr cdar cddar cdddar cdddr cddr cdr closure
cond cons const_e const_pi cos cosh dec dec-c defun div
en-queue eq eqn exp floor funcall funcs get-c get-list gt
gte if inc inc-c is-prime label lambda let let* list
ln log lt lte make-queue make-variable-c max min mod mul
nil nondef not null p p-list pow primes print q
queue quote rassoc reverse round setcar setcdr setq sin sinh
sqrt sub symbol-value t tan tanh trunc while x zerop

> (primes (make-queue) 3 1000)
[str] (primes (make-queue) 3 1000)
[exp] (primes (make-queue) 3 1000)
[eval] (2 3 5 7 11 13 17 19 23 29 31 37 41 43 47 53 59 61 67 71 73 79 83 89 97 101 103 107 109 113 127 131 137 139 149 151 157 163 167 173 179 181 191 193 197 199 211 223 227 229 233 239 241 251 257 263 269 271 277 281 283 293 307 311 313 317 331 337 347 349 353 359 367 373 379 383 389 397 401 409 419 421 431 433 439 443 449 457 461 463 467 479 487 491 499 503 509 521 523 541 547 557 563 569 571 577 587 593 599 601 607 613 617 619 631 641 643 647 653 659 661 673 677 683 691 701 709 719 727 733 739 743 751 757 761 769 773 787 797 809 811 821 823 827 829 839 853 857 859 863 877 881 883 887 907 911 919 929 937 941 947 953 967 971 977 983 991 997)
 ---------- atoms ----------
* + - / 0= 1+ 1- < <= =
> >= abs acos add and append apply asin assoc
atan atom c caaar caadr caar cadar caddar caddr cadr
car cdaar cdadr cdar cddar cdddar cdddr cddr cdr closure
cond cons const_e const_pi cos cosh dec dec-c defun div
en-queue eq eqn exp floor funcall funcs get-c get-list gt
gte if inc inc-c is-prime label lambda let let* list
ln log lt lte make-queue make-variable-c max min mod mul
nil nondef not null p p-list pow primes print q
queue quote rassoc reverse round setcar setcdr setq sin sinh
sqrt sub symbol-value t tan tanh trunc while x zerop
```
