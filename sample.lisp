> (append '(1 2 3 4 5) '(6 7 8 9 10))
[str] (append (quote (1 2 3 4 5)) (quote (6 7 8 9 10)))
[exp] (append (quote (1 2 3 4 5)) (quote (6 7 8 9 10)))
[eval] (1 2 3 4 5 6 7 8 9 10)
 ---------- atoms ----------
* + - / < <= = > >= add
and append atom caaar caadr caar cadar caddar caddr cadr
car cdaar cdadr cdar cddar cdddr cddr cdr cond cons
div eq eqn gt gte if label lambda list lt
lte mod mul nil nondef not null quote reverse sub
t
[exp] Delete Object [Class ID]= 4Cell

> (reverse '(1 2 3 4 5 6 7 8 9 10))
[str] (reverse (quote (1 2 3 4 5 6 7 8 9 10)))
[exp] (reverse (quote (1 2 3 4 5 6 7 8 9 10)))
[eval] (10 9 8 7 6 5 4 3 2 1)
 ---------- atoms ----------
* + - / < <= = > >= add
and append atom caaar caadr caar cadar caddar caddr cadr
car cdaar cdadr cdar cddar cdddr cddr cdr cond cons
div eq eqn gt gte if label lambda list lt
lte mod mul nil nondef not null quote reverse sub
t
[exp] Delete Object [Class ID]= 4Cell

> ((label sqr+ (lambda (x y) (if (null x) y (sqr+ (cdr x) (+ (* (car x) (car x)) y))))) '(1 2 3 4 5) 0)
[str] ((label sqr+ (lambda (x y) (if (null x) y (sqr+ (cdr x) (+ (* (car x) (car x)) y))))) (quote (1 2 3 4 5)) 0)
[exp] ((label sqr+ (lambda (x y) (if (null x) y (sqr+ (cdr x) (+ (* (car x) (car x)) y))))) (quote (1 2 3 4 5)) 0)
[eval] 55
 ---------- atoms ----------
* + - / < <= = > >= add
and append atom caaar caadr caar cadar caddar caddr cadr
car cdaar cdadr cdar cddar cdddr cddr cdr cond cons
div eq eqn gt gte if label lambda list lt
lte mod mul nil nondef not null quote reverse sqr+
sub t x y
[exp] Delete Object [Class ID]= 4Cell
