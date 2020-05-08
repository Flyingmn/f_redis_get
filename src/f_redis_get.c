/*
  +----------------------------------------------------------------------+
  | PHP Version 7                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2018 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author:                                                              |
  +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_f_redis_get.h"

#include <hiredis/hiredis.h>
#include <string.h>


#define CMD_MAX_LENGHT  256
#define RES_MAX_LENGHT  40

/* If you declare any globals in php_f_redis_get.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(f_redis_get)
*/

/* True global resources - no need for thread safety here */
static int le_f_redis_get;

/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("f_redis_get.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_f_redis_get_globals, f_redis_get_globals)
    STD_PHP_INI_ENTRY("f_redis_get.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_f_redis_get_globals, f_redis_get_globals)
PHP_INI_END()
*/
/* }}} */

/* Remove the following function when you have successfully modified config.m4
   so that your module can be compiled into PHP, it exists only for testing
   purposes. */

/* Every user-visible function in PHP should document itself in the source */
/* {{{ proto string confirm_f_redis_get_compiled(string arg)
   Return a string to confirm that the module is compiled in */
PHP_FUNCTION(confirm_f_redis_get_compiled)
{
	char *arg = NULL;
	size_t arg_len, len;
	zend_string *strg;

	if (zend_parse_parameters(ZEND_NUM_ARGS(), "s", &arg, &arg_len) == FAILURE) {
		return;
	}

	strg = strpprintf(0, "Congratulations! You have successfully modified ext/%.78s/config.m4. Module %.78s is now compiled into PHP.", "f_redis_get", arg);

	RETURN_STR(strg);
}
/* }}} */
/* The previous line is meant for vim and emacs, so it can correctly fold and
   unfold functions in source code. See the corresponding marks just before
   function definition, where the functions purpose is also documented. Please
   follow this convention for the convenience of others editing your code.
*/

/* {{{ proto string f_redis_get(string host, int port, string database, string key)
    */
PHP_FUNCTION(f_redis_get)
{
	char *host = NULL;
	char *database = NULL;
	char *key = NULL;
	char cmd[CMD_MAX_LENGHT] = {0};
	char ret_str[RES_MAX_LENGHT];

	int argc = ZEND_NUM_ARGS();
	zend_long port;
	size_t host_len;
	size_t port_len;
	size_t database_len;
	size_t key_len;

	if (zend_parse_parameters(argc, "slss", &host, &host_len, &port, &database, &database_len, &key, &key_len) == FAILURE) 
		return;

	/*php_error(E_WARNING, "f_redis_get: not yet implemented");*/
	redisContext *context = redisConnect(host, port);

	/*链接*/
	if(context->err)
    {
        redisFree(context);
        php_printf("connect fail\n");
        RETURN_FALSE;
    }

    /*选择数据库*/
    snprintf(cmd, CMD_MAX_LENGHT, "select %s", database);
    redisReply *replysel = (redisReply *)redisCommand(context, cmd);

    if(NULL == replysel)
    {
        redisFree(context);
        php_printf("select fail\n");
        RETURN_FALSE;
     }
	freeReplyObject(replysel);
	/*查询结果*/
	snprintf(cmd, CMD_MAX_LENGHT, "get %s", key);
	redisReply *reply = (redisReply *)redisCommand(context, cmd);

	if(NULL == reply)
	{
		redisFree(context);
        php_printf("get fail\n");
		RETURN_FALSE;
	}
	if (reply->type != REDIS_REPLY_STRING) {
		freeReplyObject(reply);
        redisFree(context);
        php_printf("type fail\n");
        RETURN_FALSE;
	}
	if (reply->len == 0) {
		freeReplyObject(reply);
        redisFree(context);
        php_printf("empty\n");
        RETURN_FALSE;
	}

    strcpy(ret_str, reply->str);
	freeReplyObject(reply);
    redisFree(context);

    RETURN_STRING(ret_str);
}
/* }}} */


/* {{{ php_f_redis_get_init_globals
 */
/* Uncomment this function if you have INI entries
static void php_f_redis_get_init_globals(zend_f_redis_get_globals *f_redis_get_globals)
{
	f_redis_get_globals->global_value = 0;
	f_redis_get_globals->global_string = NULL;
}
*/
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(f_redis_get)
{
	/* If you have INI entries, uncomment these lines
	REGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(f_redis_get)
{
	/* uncomment this line if you have INI entries
	UNREGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(f_redis_get)
{
#if defined(COMPILE_DL_F_REDIS_GET) && defined(ZTS)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(f_redis_get)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(f_redis_get)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "f_redis_get support", "enabled");
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}
/* }}} */

/* {{{ f_redis_get_functions[]
 *
 * Every user visible function must have an entry in f_redis_get_functions[].
 */
const zend_function_entry f_redis_get_functions[] = {
	PHP_FE(confirm_f_redis_get_compiled,	NULL)		/* For testing, remove later. */
	PHP_FE(f_redis_get,	NULL)
	PHP_FE_END	/* Must be the last line in f_redis_get_functions[] */
};
/* }}} */

/* {{{ f_redis_get_module_entry
 */
zend_module_entry f_redis_get_module_entry = {
	STANDARD_MODULE_HEADER,
	"f_redis_get",
	f_redis_get_functions,
	PHP_MINIT(f_redis_get),
	PHP_MSHUTDOWN(f_redis_get),
	PHP_RINIT(f_redis_get),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(f_redis_get),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(f_redis_get),
	PHP_F_REDIS_GET_VERSION,
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_F_REDIS_GET
#ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
#endif
ZEND_GET_MODULE(f_redis_get)
#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
