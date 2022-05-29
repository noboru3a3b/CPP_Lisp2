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
> (print-atoms)
[exp] (print-atoms)
* + - / 0= 1+ 1- < <= =
> >= abs acos add and append apply asin assoc
atan atom caaar caadr caar cadar caddar caddr cadr car
cdaar cdadr cdar cddar cdddar cdddr cddr cdr closure concat
cond cons consp const_e const_pi cos cosh dec decq defun
div eq eqn equal exp floatp floor funcall function gt
gte if inc incq integerp label lambda length let let*
list listp ln load log lt lte make-string make-vector max
min mod mul nil nondef not null numberp pow print
print-atoms quote rassoc reverse round seq setcar setcdr setq sin
sinh split-string sqrt string< string= string> stringp sub substring symbol-value
t tan tanh trunc vectorp vref vset while zerop
[eval] 119

> (load "sample.lisp")
[exp] (load "sample.lisp")
----------
(let ((n 0))
  (while (< n 10)
    (print n)
    (setq n (+ n 1))))
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

(let* ((x 10)
       (y (* 2 x)))
  (print x)
  (print y)
  (cons x y))
[exp] (let* ((x 10) (y (* 2 x))) (print x) (print y) (cons x y))
10
20
[eval] (10 . 20)

(defun sqr+0 (x y)
  (if (null x) y
      (sqr+0 (cdr x) (+ (* (car x) (car x)) y))))
[exp] (defun sqr+0 (x y) (if (null x) y (sqr+0 (cdr x) (+ (* (car x) (car x)) y))))
[eval] sqr+0

(defun sqr+ (x)
  (sqr+0 x 0))
[exp] (defun sqr+ (x) (sqr+0 x 0))
[eval] sqr+

(sqr+ '(1 2 3 4 5))
[exp] (sqr+ (quote (1 2 3 4 5)))
[eval] 55

(defun make-variable-c ()
  (let ((c 0))
    (list
      (closure () c)
      (closure () (setq c (+ c 1)))
      (closure () (setq c (- c 1))))))
[exp] (defun make-variable-c nil (let ((c 0)) (list (closure nil c) (closure nil (setq c (+ c 1))) (closure nil (setq c (- c 1))))))
[eval] make-variable-c

(let* ((funcs (make-variable-c))
       (get-c (car funcs))
       (inc-c (cadr funcs))
       (dec-c (caddr funcs)))
  (print (funcall get-c))
  (funcall inc-c)
  (print (funcall get-c))
  (funcall dec-c)
  (print (funcall get-c)))
[exp] (let* ((funcs (make-variable-c)) (get-c (car funcs)) (inc-c (cadr funcs)) (dec-c (caddr funcs))) (print (funcall get-c)) (funcall inc-c) (print (funcall get-c)) (funcall dec-c) (print (funcall get-c)))
0
1
0
[eval] 0

(defun make-queue ()
  (let ((queue (cons nil nil)))
    (setcar queue queue)
    queue))
[exp] (defun make-queue nil (let ((queue (cons nil nil))) (setcar queue queue) queue))
[eval] make-queue

(defun en-queue (queue x)
  (let ((q (cons x nil)))
    (setcdr (car queue) q)
    (setcar queue q)
    queue))
[exp] (defun en-queue (queue x) (let ((q (cons x nil))) (setcdr (car queue) q) (setcar queue q) queue))
[eval] en-queue

(defun get-list (queue) (cdr queue))
[exp] (defun get-list (queue) (cdr queue))
[eval] get-list

(defun is-prime (p-list x)
  (if (null p-list) t
      (let ((p (car p-list)))
        (cond ((gt (mul p p) x) t)
              ((zerop (mod x p)) nil)
              (t (is-prime (cdr p-list) x))))))
[exp] (defun is-prime (p-list x) (if (null p-list) t (let ((p (car p-list))) (cond ((gt (mul p p) x) t) ((zerop (mod x p)) nil) (t (is-prime (cdr p-list) x))))))
[eval] is-prime

(defun primes (queue x max)
  (cond ((gt x max)
         (cons 2 (get-list queue)))
        ((is-prime (get-list queue) x)
         (primes (en-queue queue x) (add x 2) max))
        (t (primes queue (add x 2) max))))
[exp] (defun primes (queue x max) (cond ((gt x max) (cons 2 (get-list queue))) ((is-prime (get-list queue) x) (primes (en-queue queue x) (add x 2) max)) (t (primes queue (add x 2) max))))
[eval] primes

(primes (make-queue) 3 1000)
[exp] (primes (make-queue) 3 1000)
[eval] (2 3 5 7 11 13 17 19 23 29 31 37 41 43 47 53 59 61 67 71 73 79 83 89 97 101 103 107 109 113 127 131 137 139 149 151 157 163 167 173 179 181 191 193 197 199 211 223 227 229 233 239 241 251 257 263 269 271 277 281 283 293 307 311 313 317 331 337 347 349 353 359 367 373 379 383 389 397 401 409 419 421 431 433 439 443 449 457 461 463 467 479 487 491 499 503 509 521 523 541 547 557 563 569 571 577 587 593 599 601 607 613 617 619 631 641 643 647 653 659 661 673 677 683 691 701 709 719 727 733 739 743 751 757 761 769 773 787 797 809 811 821 823 827 829 839 853 857 859 863 877 881 883 887 907 911 919 929 937 941 947 953 967 971 977 983 991 997)

(defun make-pvect ()
  (setq plen 100)
  (setq pidx 1)
  (setq pvect (make-vector plen 0)))
[exp] (defun make-pvect nil (setq plen 100) (setq pidx 1) (setq pvect (make-vector plen 0)))
[eval] make-pvect

(defun primeset (x)
  (if (eqn pidx plen) nil
      (seq (vset pvect pidx x)
           (incq pidx))))
[exp] (defun primeset (x) (if (eqn pidx plen) nil (seq (vset pvect pidx x) (incq pidx))))
[eval] primeset

(defun is-prime (x i)
  (let ((p (vref pvect i)))
    (cond ((zerop p) t)
          ((gt (mul p p) x) t)
          ((zerop (mod x p)) nil)
          (t (is-prime x (inc i))))))
[exp] (defun is-prime (x i) (let ((p (vref pvect i))) (cond ((zerop p) t) ((gt (mul p p) x) t) ((zerop (mod x p)) nil) (t (is-prime x (inc i))))))
[eval] is-prime

(defun primes (x)
  (if (is-prime x 1)
        (if (primeset x) (primes (add x 2))
            (seq (vset pvect 0 2) pvect))
      (primes (add x 2))))
[exp] (defun primes (x) (if (is-prime x 1) (if (primeset x) (primes (add x 2)) (seq (vset pvect 0 2) pvect)) (primes (add x 2))))
[eval] primes

(make-pvect)
[exp] (make-pvect)
[eval] #(0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0)
(primes 3)
[exp] (primes 3)
[eval] #(2 3 5 7 11 13 17 19 23 29 31 37 41 43 47 53 59 61 67 71 73 79 83 89 97 101 103 107 109 113 127 131 137 139 149 151 157 163 167 173 179 181 191 193 197 199 211 223 227 229 233 239 241 251 257 263 269 271 277 281 283 293 307 311 313 317 331 337 347 349 353 359 367 373 379 383 389 397 401 409 419 421 431 433 439 443 449 457 461 463 467 479 487 491 499 503 509 521 523 541)

(setq IN_FILE "sample.lisp")
[exp] (setq IN_FILE "sample.lisp")
[eval] "sample.lisp"
(setq SPLIT_LIST (split-string IN_FILE "."))
[exp] (setq SPLIT_LIST (split-string IN_FILE "."))
[eval] ("sample" "lisp")
(setq OUT_FILE (concat (car SPLIT_LIST) "." "txt"))
[exp] (setq OUT_FILE (concat (car SPLIT_LIST) "." "txt"))
[eval] "sample.txt"
----------
[eval] t

> (print-atoms)
[exp] (print-atoms)
* + - / 0= 1+ 1- < <= =
> >= IN_FILE OUT_FILE SPLIT_LIST abs acos add and append
apply asin assoc atan atom c caaar caadr caar cadar
caddar caddr cadr car cdaar cdadr cdar cddar cdddar cdddr
cddr cdr closure concat cond cons consp const_e const_pi cos
cosh dec dec-c decq defun div en-queue eq eqn equal
exp floatp floor funcall funcs function get-c get-list gt gte
i if inc inc-c incq integerp is-prime label lambda length
let let* list listp ln load log lt lte make-pvect
make-queue make-string make-variable-c make-vector max min mod mul n nil
nondef not null numberp p p-list pidx plen pow primes
primeset print print-atoms pvect q queue quote rassoc reverse round
seq setcar setcdr setq sin sinh split-string sqr+ sqr+0 sqrt
string< string= string> stringp sub substring symbol-value t tan tanh
trunc vectorp vref vset while x y zerop
[eval] 148
```
