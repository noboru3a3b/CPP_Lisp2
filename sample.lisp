> (let ((n 0)) (while (< n 10) (print n) (setq n (+ n 1))))
[str] (let ((n 0)) (while (< n 10) (print n) (setq n (+ n 1))))
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
>= abs acos add and append asin atan atom caaar
caadr caar cadar caddar caddr cadr car cdaar cdadr cdar
cddar cdddr cddr cdr cond cons const_e const_pi cos cosh
dec defun div eq eqn exp floor gt gte if
inc label lambda let let* list ln log lt lte
max min mod mul n nil nondef not null pow
print quote reverse round setq sin sinh sqrt sub t
tan tanh trunc while
[exp] Delete Object [Class ID]= 4Cell

> (let* ((x 10) (y (* 2 x))) (print x) (print y) (cons x y))
[str] (let* ((x 10) (y (* 2 x))) (print x) (print y) (cons x y))
[exp] (let* ((x 10) (y (* 2 x))) (print x) (print y) (cons x y))
10
20
[eval] (10 . 20)
 ---------- atoms ----------
* + - / 1+ 1- < <= = >
>= abs acos add and append asin atan atom caaar
caadr caar cadar caddar caddr cadr car cdaar cdadr cdar
cddar cdddr cddr cdr cond cons const_e const_pi cos cosh
dec defun div eq eqn exp floor gt gte if
inc label lambda let let* list ln log lt lte
max min mod mul n nil nondef not null pow
print quote reverse round setq sin sinh sqrt sub t
tan tanh trunc while x y
[exp] Delete Object [Class ID]= 4Cell

> (defun sqr+0 (x y) (if (null x) y (sqr+0 (cdr x) (+ (* (car x) (car x)) y))))
[str] (defun sqr+0 (x y) (if (null x) y (sqr+0 (cdr x) (+ (* (car x) (car x)) y))))
[exp] (defun sqr+0 (x y) (if (null x) y (sqr+0 (cdr x) (+ (* (car x) (car x)) y))))
[eval] sqr+0
 ---------- atoms ----------
* + - / 1+ 1- < <= = >
>= abs acos add and append asin atan atom caaar
caadr caar cadar caddar caddr cadr car cdaar cdadr cdar
cddar cdddr cddr cdr cond cons const_e const_pi cos cosh
dec defun div eq eqn exp floor gt gte if
inc label lambda let let* list ln log lt lte
max min mod mul n nil nondef not null pow
print quote reverse round setq sin sinh sqr+0 sqrt sub
t tan tanh trunc while x y
[exp] Delete Object [Class ID]= 4Cell

> (defun sqr+ (x) (sqr+0 x 0))
[str] (defun sqr+ (x) (sqr+0 x 0))
[exp] (defun sqr+ (x) (sqr+0 x 0))
[eval] sqr+
 ---------- atoms ----------
* + - / 1+ 1- < <= = >
>= abs acos add and append asin atan atom caaar
caadr caar cadar caddar caddr cadr car cdaar cdadr cdar
cddar cdddr cddr cdr cond cons const_e const_pi cos cosh
dec defun div eq eqn exp floor gt gte if
inc label lambda let let* list ln log lt lte
max min mod mul n nil nondef not null pow
print quote reverse round setq sin sinh sqr+ sqr+0 sqrt
sub t tan tanh trunc while x y
[exp] Delete Object [Class ID]= 4Cell

> (sqr+ '(1 2 3 4 5))
[str] (sqr+ (quote (1 2 3 4 5)))
[exp] (sqr+ (quote (1 2 3 4 5)))
[eval] 55
 ---------- atoms ----------
* + - / 1+ 1- < <= = >
>= abs acos add and append asin atan atom caaar
caadr caar cadar caddar caddr cadr car cdaar cdadr cdar
cddar cdddr cddr cdr cond cons const_e const_pi cos cosh
dec defun div eq eqn exp floor gt gte if
inc label lambda let let* list ln log lt lte
max min mod mul n nil nondef not null pow
print quote reverse round setq sin sinh sqr+ sqr+0 sqrt
sub t tan tanh trunc while x y
[exp] Delete Object [Class ID]= 4Cell
