> (append '(1 2 3 4 5) '(6 7 8 9 10))
[str] (append (quote (1 2 3 4 5)) (quote (6 7 8 9 10)))
[exp] (append (quote (1 2 3 4 5)) (quote (6 7 8 9 10)))
[eval] (1 2 3 4 5 6 7 8 9 10)
 ---------- atoms ----------
* + - / < <= = > >= add
and append atom caaar caadr caar cadar caddar caddr cadr
car cdaar cdadr cdar cddar cdddr cddr cdr cond cons
defun div eq eqn gt gte if label lambda list
lt lte mod mul nil nondef not null quote reverse
sub t
[exp] Delete Object [Class ID]= 4Cell

> (reverse (append '(1 2 3 4 5) '(6 7 8 9 10)))
[str] (reverse (append (quote (1 2 3 4 5)) (quote (6 7 8 9 10))))
[exp] (reverse (append (quote (1 2 3 4 5)) (quote (6 7 8 9 10))))
[eval] (10 9 8 7 6 5 4 3 2 1)
 ---------- atoms ----------
* + - / < <= = > >= add
and append atom caaar caadr caar cadar caddar caddr cadr
car cdaar cdadr cdar cddar cdddr cddr cdr cond cons
defun div eq eqn gt gte if label lambda list
lt lte mod mul nil nondef not null quote reverse
sub t
[exp] Delete Object [Class ID]= 4Cell

> (defun sqr+0 (x y) (if (null x) y (sqr+0 (cdr x) (+ (* (car x) (car x)) y))))
[str] (defun sqr+0 (x y) (if (null x) y (sqr+0 (cdr x) (+ (* (car x) (car x)) y))))
[exp] (defun sqr+0 (x y) (if (null x) y (sqr+0 (cdr x) (+ (* (car x) (car x)) y))))
[eval] t
 ---------- atoms ----------
* + - / < <= = > >= add
and append atom caaar caadr caar cadar caddar caddr cadr
car cdaar cdadr cdar cddar cdddr cddr cdr cond cons
defun div eq eqn gt gte if label lambda list
lt lte mod mul nil nondef not null quote reverse
sqr+0 sub t x y
[exp] Delete Object [Class ID]= 4Cell

> (defun sqr+ (x) (sqr+0 x 0))
[str] (defun sqr+ (x) (sqr+0 x 0))
[exp] (defun sqr+ (x) (sqr+0 x 0))
[eval] t
 ---------- atoms ----------
* + - / < <= = > >= add
and append atom caaar caadr caar cadar caddar caddr cadr
car cdaar cdadr cdar cddar cdddr cddr cdr cond cons
defun div eq eqn gt gte if label lambda list
lt lte mod mul nil nondef not null quote reverse
sqr+ sqr+0 sub t x y
[exp] Delete Object [Class ID]= 4Cell

> (sqr+ '(1 2 3 4 5))
[str] (sqr+ (quote (1 2 3 4 5)))
[exp] (sqr+ (quote (1 2 3 4 5)))
[eval] 55
 ---------- atoms ----------
* + - / < <= = > >= add
and append atom caaar caadr caar cadar caddar caddr cadr
car cdaar cdadr cdar cddar cdddr cddr cdr cond cons
defun div eq eqn gt gte if label lambda list
lt lte mod mul nil nondef not null quote reverse
sqr+ sqr+0 sub t x y
[exp] Delete Object [Class ID]= 4Cell
