;; for Common Lisp
(defparameter plen 5761455)
(defparameter pidx 1)
(defparameter p_i 1)
(defparameter px 3)
(defparameter pvect (make-array plen :initial-element 0))
(defparameter ppvect (make-array plen :initial-element 0))

(defun primeset ()
  (if (= pidx plen) nil
    (progn (setf (aref pvect pidx) px)
           (setf (aref ppvect pidx) (* px px))
           (setf pidx (+ pidx 1)))))

(defun is-prime ()
  (setf p_i 1)
  (do ((rtn 0))
      ((not (eql rtn 0)) rtn)
    (cond ((= (aref pvect p_i) 0) (setf rtn t))
          ((> (aref ppvect p_i) px) (setf rtn t))
          ((= (mod px (aref pvect p_i)) 0) (setf rtn nil))
          (t (setf p_i (+ p_i 1))))))

(defun primes ()
  (do ((rtn 0))
      ((not (eql rtn 0)) rtn)
    (if (is-prime)
          (if (primeset) t
              (progn (setf (aref pvect 0) 2)
                     (setf rtn pvect))))
    (setf px (+ px 2))))

(primes)
