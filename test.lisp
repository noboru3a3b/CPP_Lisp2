;;; Lisp Processor Definition
; elemental:
;  (quote
;  (atom
;  (eq
;  (car
;  (cdr
;  (cons
;  (cond
;  t
;  ()
; additional:
;  (caar
;  (cadr
;  (cadar
;  (caddr
;  (caddar
;  (list

(defun null_ (x)
  (eq x '()))

(defun and_ (x y)
  (cond
    (x (cond
         (y 't)
         ('t '())))
    ('t '())))

(defun not_ (x)
  (cond (x '())
        ('t 't)))

(defun append_ (x y)
  (cond
    ((null_ x) y)
    ('t (cons (car x)
              (append_ (cdr x) y)))))

(defun pair_ (x y)
  (cond
    ((and_ (null_ x) (null_ y))
     '())
	  ((and_ (not_ (atom x)) (not_ (atom y)))
	   (cons (list (car x) (car y))
	         (pair_ (cdr x) (cdr y))))))

(defun assoc_ (x y)
  (cond ((eq (caar y) x) (cadar y))
        ('t (assoc_ x (cdr y)))))

(defun evcon_ (c a)
  (cond
    ((eval_ (caar c) a)
     (eval_ (cadar c) a))
    ('t (evcon_ (cdr c) a))))

(defun evlis_ (m a)
  (cond
    ((null_ m) '())
    ('t (cons (eval_ (car m) a)
		          (evlis_ (cdr m) a)))))

(defun eval_ (e a)
  (cond
    ((atom e) (assoc_ e a))
    ((atom (car e))
     (cond
       ((eq (car e) 'quote) (cadr e))
       ((eq (car e) 'atom) (atom (eval_ (cadr e) a)))
       ((eq (car e) 'eq) (eq (eval_ (cadr e) a) (eval_ (caddr e) a)))
       ((eq (car e) 'car) (car (eval_ (cadr e) a)))
       ((eq (car e) 'cdr) (cdr (eval_ (cadr e) a)))
       ((eq (car e) 'cons) (cons (eval_ (cadr e) a) (eval_ (caddr e) a)))
       ((eq (car e) 'cond) (evcon_ (cdr e) a))
       ('t (eval_ (cons (assoc_ (car e) a) (cdr e)) a))))
    ((eq (caar e) 'label)
     (eval_ (cons (caddar e) (cdr e))
	          (cons (list (cadar e) (car e)) a)))
    ((eq (caar e) 'lambda)
     (eval_ (caddar e)
	          (append_ (pair_ (cadar e) (evlis_ (cdr e) a)) a)))))
