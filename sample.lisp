(let ((n 0))
  (while (< n 10)
    (print n)
    (setq n (+ n 1))))

(let* ((x 10)
       (y (* 2 x)))
  (print x)
  (print y)
  (cons x y))


(defun sqr+0 (x y)
  (if (null x) y
      (sqr+0 (cdr x) (+ (* (car x) (car x)) y))))

(defun sqr+ (x)
  (sqr+0 x 0))

(sqr+ '(1 2 3 4 5))


(defun make-variable-c ()
  (let ((c 0))
    (list
      (closure () c)
      (closure () (setq c (+ c 1)))
      (closure () (setq c (- c 1))))))

(let* ((funcs (make-variable-c))
       (c 1000)
       (get-c (car funcs))
       (inc-c (cadr funcs))
       (dec-c (caddr funcs)))
  (print (funcall get-c))
  (funcall inc-c)
  (print (funcall get-c))
  (funcall dec-c)
  (funcall dec-c)
  (print (funcall get-c)))

