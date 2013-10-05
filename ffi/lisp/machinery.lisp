(defpackage :machinery
  (:use :cl :cffi)
  (:export :load-library
           :unload-library
           :+version-string+
           :+version-major+
           :+version-minor+
           :+version-patch+
           :featurep
           :modulep)
  (:shadow :error))

(in-package :machinery)

(eval-when (:compile-toplevel :load-toplevel :execute)
  (define-foreign-library libmachinery
    (:darwin (:or "libmachinery.0.dylib" "libmachinery.dylib"))
    (:unix (:or "libmachinery.so.0" "libmachinery.so"))
    (t (:default "libmachinery"))))

(defun load-library (&key path version debug features)
  "Loads the libmachinery native library.
   Must be called before invoking any foreign functions in the library."
  (declare (type boolean debug)
           (type list features))
  (load-foreign-library 'libmachinery)
  (values)) ;;; no meaningful return value

(defun unload-library ()
  "Unloads the libmachinery native library."
  (close-foreign-library 'libmachinery)
  (values)) ;;; no meaningful return value

(defcvar ("machinery_version_string" +version-string+ :read-only t) :string)

(defcvar ("machinery_version_major" +version-major+ :read-only t) :short)

(defcvar ("machinery_version_minor" +version-minor+ :read-only t) :short)

(defcvar ("machinery_version_patch" +version-patch+ :read-only t) :short)

(defcfun ("machinery_feature_exists" featurep) :boolean (feature-name :string))

(defcfun ("machinery_module_exists" modulep) :boolean (module-name :string))
