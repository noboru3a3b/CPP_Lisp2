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
delete-cells delete-floats delete-ints delete-strings div eq eqn equal eval exit
exp floatp floor funcall function gt gte if inc incq
integerp label lambda length let let* list listp ln load
log lt lte make-string make-vector mapc mapcan mapcar mapconcat max
min mod mul nconc nil not nreverse null numberp or
pow print print-atoms print-cells print-floats print-ints print-strings progn quit quote
rassoc reverse round set setcar setcdr setq sin sinh split-string
sqrt string< string= string> stringp sub substring symbol-function symbol-name symbol-value
t tan tanh trunc unless vectorp vref vset when while
zerop
 ********** Total: 141 atoms **********
[eval] t
Release 0 Integers.
Release 0 Floats.
Release 0 Strings.
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
Release 38061 Cells.

> (print-atoms)
* + - / 0= 1+ 1- < <= =
> >= IN_FILE OUT_FILE SPLIT_LIST a abs acos add and
append apply asin assoc atan atom b c caaar caadr
caar cadar caddar caddr cadr car cdaar cdadr cdar cddar
cdddar cdddr cddr cdr closure concat cond cons consp const_e
const_pi cos cosh d dec dec-c decq defun delete-cells delete-floats
delete-ints delete-strings div e en-queue eq eqn equal eval exit
exp f floatp floor funcall funcs function get-c get-list gt
gte if inc inc-c incq integerp is-prime label lambda length
let let* list listp ln load log lt lte make-pvect
make-queue make-string make-variable-c make-vector mapc mapcan mapcar mapconcat max min
mod mul n nconc nil not nreverse null numberp or
p p-list pi pidx plen pow ppvect primes primeset print
print-atoms print-cells print-floats print-ints print-strings progn pvect px q queue
quit quote rassoc reverse round rtn set setcar setcdr setq
sin sinh split-string sqr+ sqr+0 sqrt string< string= string> stringp
sub substring symbol-function symbol-name symbol-value t tan tanh tree trunc
unless vectorp vref vset when while x y zerop
 ********** Total: 179 atoms **********
[eval] t
Release 330 Integers.
Release 8 Floats.
Release 3 Strings.
Release 1 Cells.

> (print-cells)
41635952:2 41636000:2 41636048:2 41636192:2 41636240:2 41636288:2 41636336:2 41636432:2 41636480:2 41636528:2
41636576:2 41636672:2 41636816:2 41636864:2 41636912:2 41636960:2 41637008:2 41637104:2 41637152:2 41637200:2
41637296:2 41637344:2 41637392:2 41637440:2 41637488:2 41637824:2 41645136:2 41645280:2 41645712:2 41645808:2
41645856:2 41645904:2 41646576:2 41659072:2 41659216:2 41659408:2 41659504:2 41659552:2 41659696:2 41659792:2
41660128:2 41660272:2 41660416:2 41660896:2 41660944:2 41660992:2 41661232:2 41661280:2 41661328:2 41661376:2
41661424:2 41661616:2 41661664:2 41661712:2 41661808:2 41661952:2 41662048:2 41662144:2 41662192:2 41662384:2
41662480:2 41662528:2 41662768:2 41663104:2 41663248:2 41663632:2 41663872:2 41681744:2 41681792:2 41681888:2
41682032:2 41682944:2 41683040:2 41683280:2 41683664:2 41683856:2 41683904:2 41683952:2 41684000:2 41684048:2
41684192:2 41684576:2 41684624:2 41684768:2 41684816:2 41684864:2 41684912:2 41684960:2 41685056:2 41685152:2
41685200:2 41685248:2 41685296:2 41685632:2 41685904:2 41685952:2 41686000:2 41686048:2 41686096:2 41686336:2
41686384:2 41686480:2 41686816:2 41686864:2 41686912:2 41687104:2 41687152:2 41687248:2 41687392:2 41687440:2
41687920:2 41688160:2 41688640:2 41708624:1 61457728:2 61457824:2 61457920:2 61457968:2 61458016:2 61458112:2
61458160:2 61458304:2 61458400:2 61458448:2 61458688:2 61458736:2 61458784:2 61458880:2 61458976:2 61459024:2
61459072:2 61459120:2 61459168:2 61459216:2 61459264:2 61459312:2 61459792:2 61459984:2 61460080:2 61460128:2
61460224:2 61460272:2 61460320:2 61460416:2 61460512:2 61460608:2 61460752:2 61460848:2 61460896:2 61460944:2
61460992:2 61461040:2 61461088:2 61461184:2 61461376:2 61461472:2 61461520:2 61461568:2 61461712:2 61461808:2
61462000:2 61462144:2 61462192:2 61462336:2 61462432:2 61463056:2 61463152:2 61463296:2 61463344:2 61463440:2
61463488:2 61466896:2 61466944:2 61466992:2 61467040:2 61467088:2 61467184:2 61467232:2 61467280:2 61467328:2
61467376:2 61467424:2 61467472:2 61467520:2 61467568:2 61467616:2 61467664:2 61467712:2 61467760:2 61467808:2
61467856:2 61467904:2 61467952:2 61468000:2 61468048:2 61468096:2 61468144:2 61468192:2 61468240:2 61468288:2
61468336:2 61468384:2 61468432:2 61468480:2 61468528:2 61468576:2 61468624:2 61468672:2 61468720:2 61468768:2
61468816:2 61468864:2 61468912:2 61468960:2 61469008:2 61469056:2 61469104:2 61469152:2 61469200:2 61469248:2
61469296:2 61469344:2 61469392:2 61469440:2 61469488:2 61469536:2 61469584:2 61469632:2 61469680:2 61469728:2
61469776:2 61469824:2 61469872:2 61469920:2 61471216:2 61471312:2 61471456:2 61471792:2 61471936:2 61472080:2
61472128:2 61472224:2 61472320:2 61473184:2 61473232:2 61473280:2 61473328:2 61473424:2 61473520:2 61473760:2
61473856:2 61473904:2 61473952:2 61474000:2 61474048:2 61474096:2 61474144:2 61474768:2 61474864:2 61474912:2
61475152:2 61475200:2 61475296:2 61475536:2 61475584:2 61475680:2 61475728:2 61475776:2 61475872:2 61475920:2
61475968:2 61754784:2 61755264:2 61767456:2 61767504:2 61767840:2 61769088:2 61769184:2 61769376:2 61771344:2
61771392:2
 ********** Total: 281 Cells **********
[eval] t
Release 0 Integers.
Release 0 Floats.
Release 0 Strings.
Release 1 Cells.

> (delete-cells)
 ----------> Delete: 1 Cells.
[eval] t
Release 0 Integers.
Release 0 Floats.
Release 0 Strings.
Release 0 Cells.

> (quit)

```
