dnl $Id$
dnl config.m4 for extension f_redis_get

dnl Comments in this file start with the string 'dnl'.
dnl Remove where necessary. This file will not work
dnl without editing.

dnl If your extension references something external, use with:

PHP_ARG_WITH(f_redis_get, for f_redis_get support,
dnl Make sure that the comment is aligned:
[  --with-f_redis_get             Include f_redis_get support])

dnl Otherwise use enable:

dnl PHP_ARG_ENABLE(f_redis_get, whether to enable f_redis_get support,
dnl Make sure that the comment is aligned:
dnl [  --enable-f_redis_get           Enable f_redis_get support])

if test "$PHP_F_REDIS_GET" != "no"; then
  dnl Write more examples of tests here...

  dnl # --with-f_redis_get -> check with-path
  dnl SEARCH_PATH="/usr/local /usr"     # you might want to change this
  dnl SEARCH_FOR="/include/f_redis_get.h"  # you most likely want to change this
  dnl if test -r $PHP_F_REDIS_GET/$SEARCH_FOR; then # path given as parameter
  dnl   F_REDIS_GET_DIR=$PHP_F_REDIS_GET
  dnl else # search default path list
  dnl   AC_MSG_CHECKING([for f_redis_get files in default path])
  dnl   for i in $SEARCH_PATH ; do
  dnl     if test -r $i/$SEARCH_FOR; then
  dnl       F_REDIS_GET_DIR=$i
  dnl       AC_MSG_RESULT(found in $i)
  dnl     fi
  dnl   done
  dnl fi
  dnl
  dnl if test -z "$F_REDIS_GET_DIR"; then
  dnl   AC_MSG_RESULT([not found])
  dnl   AC_MSG_ERROR([Please reinstall the f_redis_get distribution])
  dnl fi

  dnl # --with-f_redis_get -> add include path
  dnl PHP_ADD_INCLUDE($F_REDIS_GET_DIR/include)

  dnl # --with-f_redis_get -> check for lib and symbol presence
  dnl LIBNAME=f_redis_get # you may want to change this
  dnl LIBSYMBOL=f_redis_get # you most likely want to change this 

  dnl PHP_CHECK_LIBRARY($LIBNAME,$LIBSYMBOL,
  dnl [
  dnl   PHP_ADD_LIBRARY_WITH_PATH($LIBNAME, $F_REDIS_GET_DIR/$PHP_LIBDIR, F_REDIS_GET_SHARED_LIBADD)
  dnl   AC_DEFINE(HAVE_F_REDIS_GETLIB,1,[ ])
  dnl ],[
  dnl   AC_MSG_ERROR([wrong f_redis_get lib version or lib not found])
  dnl ],[
  dnl   -L$F_REDIS_GET_DIR/$PHP_LIBDIR -lm
  dnl ])
  dnl
  dnl PHP_SUBST(F_REDIS_GET_SHARED_LIBADD)
  PHP_NEW_EXTENSION(f_redis_get, f_redis_get.c, $ext_shared,, -DZEND_ENABLE_STATIC_TSRMLS_CACHE=1)
fi
PHP_ADD_LIBRARY_WITH_PATH(hiredis, /usr/local/lib/, F_REDIS_GET_SHARED_LIBADD)
PHP_SUBST(F_REDIS_GET_SHARED_LIBADD)
