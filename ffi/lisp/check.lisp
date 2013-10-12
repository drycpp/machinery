(require 'asdf)
(pushnew #p"./" asdf:*central-registry* :test #'equal)

(require 'cffi)
(pushnew #P"../../src/machinery/.libs/" cffi:*foreign-library-directories* :test #'equal)

(require 'machinery)
(machinery:load-library)

(format t "~S~&" (list 'machinery:+version-string+ machinery:+version-string+))

(format t "~S~&" (list 'machinery:+version-major+ machinery:+version-major+))

(format t "~S~&" (list 'machinery:+version-minor+ machinery:+version-minor+))

(format t "~S~&" (list 'machinery:+version-patch+ machinery:+version-patch+))

(format t "~S~&"
  (list 'machinery:featurep
        (mapcar (lambda (feature-name)
                  (list feature-name (machinery:featurep feature-name)))
                '("ascii" "debug" "unicode"))))

(format t "~S~&"
  (list 'machinery:modulep
        (mapcar (lambda (module-name)
                  (list module-name (machinery:modulep module-name)))
                '("arm" "mips" "x86" "ir" "jit"))))

(format t "~&")

(machinery:unload-library)
