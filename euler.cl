; Problem 1: Sum of multiples of 3 and 5, less than a given number.

(defun multiples-less-than (upper-bound &rest factors)
  (- (reduce #'+ factors
	     :key (sum-function upper-bound))
     (sum-of-factor-multiples-less-than (reduce #'* factors) upper-bound)))
	  
(defmacro sum-function (upper-bound)
  `(lambda (x) (sum-of-factor-multiples-less-than x ,upper-bound)))

(defun sum-of-factor-multiples-less-than (factor upper-bound)
  (* factor (nth-triangular (- (ceiling (/ upper-bound factor)) 1))))

(defun nth-triangular (n)
  (if (= n 1) 1 (+ n (nth-triangular (- n 1)))))

; Problem 2: Each new term in the Fibonacci sequence is generated by adding the previous two terms.
; By starting with 1 and 2, the first 10 terms will be:
; 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, ...
; By considering the terms in the Fibonacci sequence whose values do not exceed four million,
; find the sum of the even-valued terms.


; Do more of this in-place to avoid using gigabytes of memory
; Will storing the list backwards improve performance?


(defun sum-even-fibonacci (&optional (goal 4000000) (fib-list '(1 2)) (sum 0))
  (if (> (second fib-list) goal)
      sum
      (sum-even-fibonacci
       goal
       (list (second fib-list) (next-fibonacci fib-list))
       (if (evenp (second fib-list))
	   (+ sum (second fib-list))
	   sum))))
  
(defun next-fibonacci (fib-list)
  (+ (first fib-list)
     (second fib-list)))

; Problem 3 
; The prime factors of 13195 are 5, 7, 13 and 29.
;
; What is the largest prime factor of the number 600851475143 ?

(defun largest-prime-factor (n)
  (let ((primes (subseq (prime-sieve (range n)) 2)))
    (break)
    (loop for prime in primes
	 do (loop while (= (mod n prime) 0)
	      do (setf n (/ n prime)))
	 (when (member n primes) (return n)))))
	 
(defun prime-sieve (number-list &optional (n 2))
  (break)
  (if (>= (1+ (expt (nth n number-list) 2)) (car (last number-list)))
      number-list
      (prime-sieve                   
       (remove-if (lambda (x) (= (mod x (nth n number-list)) 0))
		  number-list
		  :start (+ n 1))       
       (+ n 1))))

(defun range (max &key (min 0) (step 1))
  (loop for n from min to max by step
     collect n))

; Problem 4 
; A palindromic number reads the same both ways. The largest palindrome made from the product of two 2-digit numbers is 9009 = 91 × 99.

; Find the largest palindrome made from the product of two 3-digit numbers.

(defun func-paltest (palroot div)
  (let ((pal (even-palindrome palroot)))
    (if (and (divisorp pal div)
	     (< (/ pal div) 1000))
	(values pal (list (/ pal div) div))
	(func-paltest
	 (if (= div 100) (- palroot 1) palroot)
	 (if (= div 100) 999 (- div 1))))))

(defun divisorp (number quotient)
  (zerop (mod number quotient)))

(defun even-palindrome (n)
  (digits->number
   (append (number->digits n) (reverse (number->digits n)))))

(defun digits->number (digits)
  (loop for x in (reverse digits)
	      for y from 0
	      sum (* x (expt 10 y))))
    
(defun number->digits (n)
  (let ((digits '()))
    (loop while (>= n 1)
       do (multiple-value-bind (rest digit) (truncate n 10) 
	    (push digit digits)
	    (setf n rest)))
    digits))

; Problem 6 
; The sum of the squares of the first ten natural numbers is,

; 12 + 22 + ... + 102 = 385
; The square of the sum of the first ten natural numbers is,

; (1 + 2 + ... + 10)2 = 552 = 3025
; Hence the difference between the sum of the squares of the first ten natural numbers and the square of the sum is 3025 − 385 = 2640.

; Find the difference between the sum of the squares of the first one hundred natural numbers and the square of the sum.

(defun sum-square-difference (n)
  (let ((lst (range n)))
    (- (expt (reduce #'+ lst) 2)
       (reduce #'+ lst :key (lambda (x) (expt x 2))))))

(defun sum-square-difference (n)
  (let ((lst (range n)))
    (- (expt (reduce #'+ lst) 2)
       (reduce #'+ lst :key (lambda (x) (expt x 2))))))


; Problem 7 
; By listing the first six prime numbers: 2, 3, 5, 7, 11, and 13, we can see that the 6th prime is 13.

; What is the 10 001st prime number?

(defun x-prime (goal &optional (accum 1) (last-prime 2))
  (if (= goal accum)
      last-prime
      (x-prime goal (1+ accum) (next-prime last-prime))))

(defun primep (number)
  (when (> number 1)
    (loop for fac from 2 to (isqrt number) never (divisorp number fac))))

(defun next-prime (number)
  (loop for n from (1+ number) when (primep n) return n))

; Problem 8 
; The four adjacent digits in the 1000-digit number that have the greatest product are 9 × 9 × 8 × 9 = 5832.

; 73167176531330624919225119674426574742355349194934
; 96983520312774506326239578318016984801869478851843
; 85861560789112949495459501737958331952853208805511
; 12540698747158523863050715693290963295227443043557
; 66896648950445244523161731856403098711121722383113
; 62229893423380308135336276614282806444486645238749
; 30358907296290491560440772390713810515859307960866
; 70172427121883998797908792274921901699720888093776
; 65727333001053367881220235421809751254540594752243
; 52584907711670556013604839586446706324415722155397
; 53697817977846174064955149290862569321978468622482
; 83972241375657056057490261407972968652414535100474
; 82166370484403199890008895243450658541227588666881
; 16427171479924442928230863465674813919123162824586
; 17866458359124566529476545682848912883142607690042
; 24219022671055626321111109370544217506941658960408
; 07198403850962455444362981230987879927244284909188
; 84580156166097919133875499200524063689912560717606
; 05886116467109405077541002256983155200055935729725
; 71636269561882670428252483600823257530420752963450

; Find the thirteen adjacent digits in the 1000-digit number that have the greatest product. What is the value of this product?

(defun adjacent-product (digits adjacent &optional (index 0) (product 0))
  (if (>= (+ index adjacent) (list-length digits))
      product
      (adjacent-product digits adjacent (1+ index)
			 (let ((this-product (reduce #'* digits :start index :end (+ index adjacent))))
			   (if (> this-product product)
			       this-product
			       product)))))

; Problem 9 
; A Pythagorean triplet is a set of three natural numbers, a < b < c, for which,

; a^2 + b^2 = c^2
; For example, 3^2 + 4^2 = 9 + 16 = 25 = 5^2.

; There exists exactly one Pythagorean triplet for which a + b + c = 1000.
; Find the product abc.

(defun pythagorean-triplet (sum &optional (a 1) (b 2) (c 997))
  
  (if (= (+ (expt a 2) (expt b 2)) (expt c 2))
    (* a b c)
    (let ((la a) (lb b) (lc c))
      (if (>= (- b c) -1)
          (setf la (1+ a) lb (1+ a) lc (- 1000 (+ la lb))))
      (pythagorean-triplet sum la (1+ lb) (1- lc)))))

; Problem 10 
; The sum of the primes below 10 is 2 + 3 + 5 + 7 = 17.

; Find the sum of all the primes below two million.

(defun sum-primes-below (n)
  (reduce #'+ (remove-if-not #'primep (range (1- n)))))

; Problem 11 
; In the 20×20 grid below, four numbers along a diagonal line have been marked in red.

(defun problem-11-matrix () 
'((08 02 22 97 38 15 00 40 00 75 04 05 07 78 52 12 50 77 91 08)
(49 49 99 40 17 81 18 57 60 87 17 40 98 43 69 48 04 56 62 00)
(81 49 31 73 55 79 14 29 93 71 40 67 53 88 30 03 49 13 36 65)
(52 70 95 23 04 60 11 42 69 24 68 56 01 32 56 71 37 02 36 91)
(22 31 16 71 51 67 63 89 41 92 36 54 22 40 40 28 66 33 13 80)
(24 47 32 60 99 03 45 02 44 75 33 53 78 36 84 20 35 17 12 50)
(32 98 81 28 64 23 67 10 26 38 40 67 59 54 70 66 18 38 64 70)
(67 26 20 68 02 62 12 20 95 63 94 39 63 08 40 91 66 49 94 21)
(24 55 58 05 66 73 99 26 97 17 78 78 96 83 14 88 34 89 63 72)
(21 36 23 09 75 00 76 44 20 45 35 14 00 61 33 97 34 31 33 95)
(78 17 53 28 22 75 31 67 15 94 03 80 04 62 16 14 09 53 56 92)
(16 39 05 42 96 35 31 47 55 58 88 24 00 17 54 24 36 29 85 57)
(86 56 00 48 35 71 89 07 05 44 44 37 44 60 21 58 51 54 17 58)
(19 80 81 68 05 94 47 69 28 73 92 13 86 52 17 77 04 89 55 40)
(04 52 08 83 97 35 99 16 07 97 57 32 16 26 26 79 33 27 98 66)
(88 36 68 87 57 62 20 72 03 46 33 67 46 55 12 32 63 93 53 69)
(04 42 16 73 38 25 39 11 24 94 72 18 08 46 29 32 40 62 76 36)
(20 69 36 41 72 30 23 88 34 62 99 69 82 67 59 85 74 04 36 16)
(20 73 35 29 78 31 90 01 74 31 49 71 48 86 81 16 23 57 05 54)
(01 70 54 71 83 51 54 69 16 92 33 48 61 43 52 01 89 19 67 48)))

; The product of these numbers is 26 × 63 × 78 × 14 = 1788696.

; What is the greatest product of four adjacent numbers in the same direction (up, down, left, right, or diagonally) in the 20×20 grid?

(defun matrix-lookup (matrix coords)
  (if (null coords)
      matrix
      (matrix-lookup (nth (car coords) matrix) (rest coords))))

(defun positive-skew (matrix)
  (let* ((rows (list-length matrix))
        (filler (1- rows))
        (newmatrix (copy-list matrix)))
    (dotimes (i rows)
      (setf (nth i newmatrix) (append (make-list (- filler i)) (nth i newmatrix) (make-list i))))
    newmatrix))
  
(defun negative-skew (matrix)
  (let* ((rows (list-length matrix))
        (filler (1- rows))
        (newmatrix (copy-list matrix)))
    (dotimes (i rows)
      (setf (nth i newmatrix) (append (make-list i) (nth i newmatrix) (make-list (- filler i)))))
    newmatrix))

(defun rotate-2d (matrix &optional (newmatrix nil))
  (if (null (first matrix))
      newmatrix
      (rotate-2d (mapcar #'rest matrix) 
                  (append newmatrix (list (mapcar #'car matrix))))))

(defun horizontal-adjacent (matrix adjacent)
  (apply #'max (mapcar (lambda (x) (adjacent-product x adjacent)) matrix)))

(defun vertical-adjacent (matrix adjacent)
  (horizontal-adjacent (rotate-2d matrix) adjacent))

(defun positive-diagonal-adjacent (matrix adjacent)
  (horizontal-adjacent (remove-if (lambda (x) (< (list-length x) adjacent)) 
             (mapcar (lambda (x) (remove-if #'null x)) 
                     (rotate-2d (positive-skew matrix)))) adjacent))  

(defun negative-diagonal-adjacent (matrix adjacent)
  (horizontal-adjacent (remove-if (lambda (x) (< (list-length x) adjacent)) 
             (mapcar (lambda (x) (remove-if #'null x)) 
                     (rotate-2d (negative-skew matrix)))) adjacent))  

(defun max-geometric-product (matrix adjacent)
  (max (horizontal-adjacent matrix adjacent)
       (vertical-adjacent matrix adjacent)
       (positive-diagonal-adjacent matrix adjacent)
       (negative-diagonal-adjacent matrix adjacent)))

;Problem 12 
;The sequence of triangle numbers is generated by adding the natural numbers. So the 7th triangle number would be 1 + 2 + 3 + 4 + 5 + 6 + 7 = 28. The first ten terms would be:

;1, 3, 6, 10, 15, 21, 28, 36, 45, 55, ...

;Let us list the factors of the first seven triangle numbers:

; 1: 1
; 3: 1,3
; 6: 1,2,3,6
;10: 1,2,5,10
;15: 1,3,5,15
;21: 1,3,7,21
;28: 1,2,4,7,14,28
;We can see that 28 is the first triangle number to have over five divisors.

;What is the value of the first triangle number to have over five hundred divisors?
  






