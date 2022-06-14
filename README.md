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
delete-cells delete-floats delete-ints delete-strings delete-vectors div eq eqn equal eval
exit exp floatp floor funcall function gt gte if inc
incq integerp label lambda length let let* list listp ln
load log lt lte make-string make-vector mapc mapcan mapcar mapconcat
max min mod mul nconc nil not nreverse null numberp
or pow print print-atoms print-cells print-floats print-ints print-strings print-vectors progn
quit quote rassoc reverse round set setcar setcdr setq sin
sinh split-string sqrt string< string= string> stringp sub substring symbol-function
symbol-name symbol-value t tan tanh trunc unless vectorp vref vset
when while zerop
 ********** Total: 143 atoms **********
[eval] t
Release 0 Integers.
Release 0 Floats.
Release 0 Strings.
Release 0 Vectors.
Release 1 Cells.

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

(primes (make-queue) 3 1000)
[eval] (2 3 5 7 11 13 17 19 23 29 31 37 41 43 47 53 59 61 67 71 73 79 83 89 97 101 103 107 109 113 127 131 137 139 149 151 157 163 167 173 179 181 191 193 197 199 211 223 227 229 233 239 241 251 257 263 269 271 277 281 283 293 307 311 313 317 331 337 347 349 353 359 367 373 379 383 389 397 401 409 419 421 431 433 439 443 449 457 461 463 467 479 487 491 499 503 509 521 523 541 547 557 563 569 571 577 587 593 599 601 607 613 617 619 631 641 643 647 653 659 661 673 677 683 691 701 709 719 727 733 739 743 751 757 761 769 773 787 797 809 811 821 823 827 829 839 853 857 859 863 877 881 883 887 907 911 919 929 937 941 947 953 967 971 977 983 991 997)

(defun make-pvect ()
  (setq plen 168)
  (setq pidx 1)
  (setq pi 1)
  (setq px 3)
  (setq pvect (make-vector plen 0))
  (setq ppvect (make-vector plen 0)))
[eval] make-pvect

(defun primeset ()
  (if (eqn pidx plen) nil
      (vset pvect pidx px)
      (vset ppvect pidx (mul px px))
      (incq pidx)))
[eval] primeset

(defun is-prime ()
  (let ((rtn 0))
    (setq pi 1)
    (while (eq rtn 0)
      (cond ((zerop (vref pvect pi)) (setq rtn t))
            ((gt (vref ppvect pi) px) (setq rtn t))
            ((zerop (mod px (vref pvect pi))) (setq rtn nil))
            (t (incq pi))))
    rtn))
[eval] is-prime

(defun primes ()
  (let ((rtn 0))
    (while (eq rtn 0)
      (if (is-prime px)
            (unless (primeset)
              (vset pvect 0 2)
              (setq rtn pvect)))
      (incq px 2))
    rtn))
[eval] primes

(make-pvect)
[eval] #(0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0)
(primes)
[eval] #(2 3 5 7 11 13 17 19 23 29 31 37 41 43 47 53 59 61 67 71 73 79 83 89 97 101 103 107 109 113 127 131 137 139 149 151 157 163 167 173 179 181 191 193 197 199 211 223 227 229 233 239 241 251 257 263 269 271 277 281 283 293 307 311 313 317 331 337 347 349 353 359 367 373 379 383 389 397 401 409 419 421 431 433 439 443 449 457 461 463 467 479 487 491 499 503 509 521 523 541 547 557 563 569 571 577 587 593 599 601 607 613 617 619 631 641 643 647 653 659 661 673 677 683 691 701 709 719 727 733 739 743 751 757 761 769 773 787 797 809 811 821 823 827 829 839 853 857 859 863 877 881 883 887 907 911 919 929 937 941 947 953 967 971 977 983 991 997)

(symbol-function #'primes)
[eval] (lambda nil (let ((rtn 0)) (while (eq rtn 0) (if (is-prime px) (unless (primeset) (vset pvect 0 2) (setq rtn pvect))) (incq px 2)) rtn))
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
Release 76 Integers.
Release 9 Floats.
Release 8 Strings.
Release 0 Vectors.
Release 38061 Cells.

> (print-atoms)
* + - / 0= 1+ 1- < <= =
> >= IN_FILE OUT_FILE SPLIT_LIST a abs acos add and
append apply asin assoc atan atom b c caaar caadr
caar cadar caddar caddr cadr car cdaar cdadr cdar cddar
cdddar cdddr cddr cdr closure concat cond cons consp const_e
const_pi cos cosh d dec dec-c decq defun delete-cells delete-floats
delete-ints delete-strings delete-vectors div e en-queue eq eqn equal eval
exit exp f floatp floor funcall funcs function get-c get-list
gt gte if inc inc-c incq integerp is-prime label lambda
length let let* list listp ln load log lt lte
make-pvect make-queue make-string make-variable-c make-vector mapc mapcan mapcar mapconcat max
min mod mul n nconc nil not nreverse null numberp
or p p-list pi pidx plen pow ppvect primes primeset
print print-atoms print-cells print-floats print-ints print-strings print-vectors progn pvect px
q queue quit quote rassoc reverse round rtn set setcar
setcdr setq sin sinh split-string sqr+ sqr+0 sqrt string< string=
string> stringp sub substring symbol-function symbol-name symbol-value t tan tanh
tree trunc unless vectorp vref vset when while x y
zerop
 ********** Total: 181 atoms **********
[eval] t
Release 330 Integers.
Release 8 Floats.
Release 3 Strings.
Release 0 Vectors.
Release 1 Cells.

> (print-cells)
42033328:2 42033376:2 42033424:2 42033472:2 42033616:2 42033664:2 42033712:2 42033808:2 42033904:2 42033952:2
42034096:2 42034144:2 42034192:2 42034240:2 42034288:2 42034384:2 42034432:2 42034480:2 42034528:2 42034624:2
42034768:2 42034816:2 42034864:2 42034912:2 42035104:2 42035152:2 42038016:2 42038496:2 42038640:2 42038880:2
42039264:2 42039408:2 42039792:2 42052288:2 42052384:2 42052432:2 42052480:2 42052528:2 42052672:2 42052720:2
42053104:2 42053344:2 42053392:2 42053632:2 42053680:2 42053776:2 42056320:2 42056656:2 42057424:2 42057472:2
42057520:2 42057568:2 42057616:2 42057664:2 42057712:2 42057760:2 42057808:2 42057856:2 42057904:2 42057952:2
42058000:2 42058048:2 42058096:2 42058144:2 42058192:2 42058240:2 42058288:2 42075440:2 42075488:2 42075536:2
42075632:2 42075824:2 42075968:2 42076016:2 42076208:2 42076352:2 42076400:2 42076592:2 42076832:2 42076976:2
42077360:2 42077504:2 42077888:2 42077984:2 42078032:2 42078080:2 42078176:2 42078464:2 42078560:2 42078608:2
42078656:2 42078752:2 42078800:2 42078848:2 42079312:2 42079360:2 42079504:2 42079552:2 42079600:2 42079696:2
42079936:2 42080608:2 42080848:2 42080896:2 42080944:2 42081088:2 42081232:2 42081328:2 42081520:2 42081568:2
42081616:2 42081712:2 42081808:2 42115968:1 62434592:2 62434832:2 62434880:2 62435216:2 62435264:2 62435360:2
62435504:2 62435552:2 62435600:2 62435648:2 62435696:2 62435744:2 62435792:2 62435840:2 62435936:2 62435984:2
62436032:2 62436080:2 62436128:2 62436224:2 62436272:2 62436320:2 62436416:2 62436464:2 62436704:2 62436848:2
62437040:2 62437136:2 62437376:2 62437472:2 62437520:2 62437568:2 62437664:2 62437712:2 62438096:2 62438240:2
62438288:2 62438336:2 62438480:2 62438576:2 62439008:2 62439152:2 62439200:2 62439248:2 62439344:2 62439392:2
62439440:2 62439488:2 62439680:2 62439728:2 62439824:2 62439920:2 62440112:2 62440256:2 62440496:2 62440544:2
62440640:2 62443808:2 62443856:2 62443952:2 62444000:2 62444048:2 62444096:2 62444144:2 62444192:2 62444240:2
62444288:2 62444336:2 62444384:2 62444432:2 62444480:2 62444528:2 62444576:2 62444624:2 62444672:2 62444720:2
62444816:2 62444864:2 62444912:2 62444960:2 62445008:2 62445056:2 62445104:2 62445152:2 62445200:2 62445248:2
62445296:2 62445344:2 62445392:2 62445440:2 62445488:2 62445536:2 62445584:2 62445632:2 62445680:2 62445728:2
62445776:2 62445824:2 62445872:2 62445920:2 62445968:2 62446016:2 62446064:2 62446112:2 62446160:2 62446208:2
62446256:2 62446304:2 62446352:2 62446400:2 62446448:2 62446496:2 62446544:2 62446592:2 62446640:2 62446688:2
62446736:2 62446784:2 62446832:2 62447744:2 62447792:2 62448176:2 62448512:2 62448560:2 62448608:2 62448704:2
62448752:2 62449040:2 62449952:2 62450000:2 62450384:2 62450528:2 62450576:2 62450624:2 62450720:2 62450864:2
62451104:2 62451152:2 62451248:2 62451440:2 62451488:2 62451536:2 62451584:2 62451632:2 62451680:2 62451728:2
62451776:2 62451824:2 62452016:2 62452112:2 62452160:2 62452400:2 62452496:2 62452544:2 62452736:2 62452784:2
62452928:2 62733296:2 62733440:2 62747120:2 62747744:2 62747792:2 62747888:2 62748080:2 62748416:2 62748464:2
62748560:2
 ********** Total: 281 Cells **********
[eval] t
Release 0 Integers.
Release 0 Floats.
Release 0 Strings.
Release 0 Vectors.
Release 1 Cells.

> (delete-cells)
 ----------> Delete: 1 Cells.
[eval] t
Release 0 Integers.
Release 0 Floats.
Release 0 Strings.
Release 0 Vectors.
Release 0 Cells.

> (quit)

```
