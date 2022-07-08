;; for Common Lisp
(declaim (type integer plen pidx p_i px rtn rtn2) (optimize (speed 3) (safety 0)))
;(defparameter plen 5761455)    ; 2 .. 100000000 -> last 1個表示((99999989)
(defparameter plen 50847534)   ; 2 .. 1000000000 -> Heap exhausted は表示のせいだったので、last 1個表示(999999937)に変えた。
(defparameter pidx 1)
(defparameter p_i 1)
(defparameter px 3)
(defparameter rtn 0)
(defparameter rtn2 0)
(defparameter pvect (make-array plen :element-type 'integer :initial-element 0))
(defparameter ppvect (make-array plen :element-type 'integer :initial-element 0))

(defun primeset ()
  (if (= pidx plen) nil
    (progn (setf (aref pvect pidx) px)
           (setf (aref ppvect pidx) (* px px))
           (setf pidx (+ pidx 1)))))

(defun is-prime ()
  (setf p_i 1)
  (setf rtn 0)
  (do ()
      ((> rtn 0) rtn)
    (cond ((= (aref pvect p_i) 0) (setf rtn 1))
          ((> (aref ppvect p_i) px) (setf rtn 1))
          ((= (mod px (aref pvect p_i)) 0) (setf rtn 2))
          (t (setf p_i (+ p_i 1)))))
  (if (= rtn 1) t nil))

(defun primes ()
  (setf rtn2 0)
  (do ()
      ((> rtn2 0) rtn2)
    (if (is-prime)
          (if (primeset) t
              (progn (setf (aref pvect 0) 2)
                     (setf rtn2 1))))
    (setf px (+ px 2)))
  pvect)

;(primes)
(format t "~S~%" (aref (primes) (- plen 1)))
