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
* + - / 0= 1+ 1- < <= =
> >= abs acos add and append apply asin assoc
atan atom caaar caadr caar cadar caddar caddr cadr car
cdaar cdadr cdar cddar cdddar cdddr cddr cdr closure concat
cond cons consp const_e const_pi cos cosh dec decq defun
div eq eqn equal eval exit exp floatp floor funcall
function gt gte if inc incq integerp label lambda length
let let* list listp ln load log lt lte make-string
make-vector mapc mapcan mapcar mapconcat max min mod mul nconc
nil not nreverse null numberp or pow print print-atoms progn
quit quote rassoc reverse round set setcar setcdr setq sin
sinh split-string sqrt string< string= string> stringp sub substring symbol-function
symbol-name symbol-value t tan tanh trunc unless vectorp vref vset
when while zerop
[eval] 133

> (load "sample.lisp")
----------
(let ((n 0))
  (while (< n 10)
    (print n)
    (setq n (+ n 1))))
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
10
20
[eval] (10 . 20)

(defun sqr+0 (x y)
  (if (null x) y
      (sqr+0 (cdr x) (+ (* (car x) (car x)) y))))
[eval] sqr+0

(defun sqr+ (x)
  (sqr+0 x 0))
[eval] sqr+

(sqr+ '(1 2 3 4 5))
[eval] 55

(defun make-variable-c ()
  (let ((c 0))
    (list
      (closure () c)
      (closure () (setq c (+ c 1)))
      (closure () (setq c (- c 1))))))
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
0
1
0
[eval] 0

(defun make-queue ()
  (let ((queue (cons nil nil)))
    (setcar queue queue)
    queue))
[eval] make-queue

(defun en-queue (queue x)
  (let ((q (cons x nil)))
    (setcdr (car queue) q)
    (setcar queue q)
    queue))
[eval] en-queue

(defun get-list (queue) (cdr queue))
[eval] get-list

(defun is-prime (p-list x)
  (if (null p-list) t
      (let ((p (car p-list)))
        (cond ((gt (mul p p) x) t)
              ((zerop (mod x p)) nil)
              (t (is-prime (cdr p-list) x))))))
[eval] is-prime

(defun primes (queue x max)
  (cond ((gt x max)
         (cons 2 (get-list queue)))
        ((is-prime (get-list queue) x)
         (primes (en-queue queue x) (add x 2) max))
        (t (primes queue (add x 2) max))))
[eval] primes

(primes (make-queue) 3 100)
[eval] (2 3 5 7 11 13 17 19 23 29 31 37 41 43 47 53 59 61 67 71 73 79 83 89 97)

(defun make-pvect ()
  (setq plen 25)
  (setq pidx 1)
  (setq pvect (make-vector plen 0))
  (setq ppvect (make-vector plen 0)))
[eval] make-pvect

(defun primeset (x)
  (if (eqn pidx plen) nil
      (vset pvect pidx x)
      (vset ppvect pidx (mul x x))
      (incq pidx)))
[eval] primeset

(defun is-prime (x)
  (let ((pi 1) (rtn 0))
    (while (eq rtn 0)
      (cond ((zerop (vref pvect pi)) (setq rtn t))
            ((gt (vref ppvect pi) x) (setq rtn t))
            ((zerop (mod x (vref pvect pi))) (setq rtn nil))
            (t (incq pi))))
    rtn))
[eval] is-prime

(defun primes (x)
  (let ((rtn 0))
    (while (eq rtn 0)
      (if (is-prime x)
            (unless (primeset x)
              (vset pvect 0 2)
              (setq rtn pvect)))
      (incq x 2))
    rtn))
[eval] primes

(make-pvect)
[eval] #(0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0)
(primes 3)
[eval] #(2 3 5 7 11 13 17 19 23 29 31 37 41 43 47 53 59 61 67 71 73 79 83 89 97)

(symbol-function #'primes)
[eval] (lambda (x) (let ((rtn 0)) (while (eq rtn 0) (if (is-prime x) (unless (primeset x) (vset pvect 0 2) (setq rtn pvect))) (incq x 2)) rtn))
(symbol-function #'incq)
[eval] "#<subr incq>"

(setq IN_FILE "sample.lisp")
[eval] "sample.lisp"
(setq SPLIT_LIST (split-string IN_FILE "."))
[eval] ("sample" "lisp")
(setq OUT_FILE (concat (car SPLIT_LIST) "." "txt"))
[eval] "sample.txt"

(mapcar #'list '(a b c d e f))
[eval] ((a) (b) (c) (d) (e) (f))
(mapcan #'list '(a b c d e f))
[eval] (a b c d e f)
(mapc #'list '(a b c d e f))
[eval] (a b c d e f)
(mapconcat #'symbol-name '(a b c d e f) " ")
[eval] "a b c d e f"

(setq tree '((a . 10) (b . 20) (c . 30) (d . 40)))
[eval] ((a . 10) (b . 20) (c . 30) (d . 40))
(assoc 'b tree)
[eval] (b . 20)
(assoc 'e tree)
[eval] nil
(rassoc 30 tree)
[eval] (c . 30)
(rassoc 50 tree)
[eval] nil
----------
[eval] t

> (print-atoms)
* + - / 0= 1+ 1- < <= =
> >= IN_FILE OUT_FILE SPLIT_LIST a abs acos add and
append apply asin assoc atan atom b c caaar caadr
caar cadar caddar caddr cadr car cdaar cdadr cdar cddar
cdddar cdddr cddr cdr closure concat cond cons consp const_e
const_pi cos cosh d dec dec-c decq defun div e
en-queue eq eqn equal eval exit exp f floatp floor
funcall funcs function get-c get-list gt gte if inc inc-c
incq integerp is-prime label lambda length let let* list listp
ln load log lt lte make-pvect make-queue make-string make-variable-c make-vector
mapc mapcan mapcar mapconcat max min mod mul n nconc
nil not nreverse null numberp or p p-list pi pidx
plen pow ppvect primes primeset print print-atoms progn pvect q
queue quit quote rassoc reverse round rtn set setcar setcdr
setq sin sinh split-string sqr+ sqr+0 sqrt string< string= string>
stringp sub substring symbol-function symbol-name symbol-value t tan tanh tree
trunc unless vectorp vref vset when while x y zerop
[eval] 170

> (quit)

```
