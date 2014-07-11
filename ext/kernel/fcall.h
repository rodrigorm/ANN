
/*
  +------------------------------------------------------------------------+
  | Zephir Language                                                        |
  +------------------------------------------------------------------------+
  | Copyright (c) 2011-2014 Zephir Team (http://www.zephir-lang.com)       |
  +------------------------------------------------------------------------+
  | This source file is subject to the New BSD License that is bundled     |
  | with this package in the file docs/LICENSE.txt.                        |
  |                                                                        |
  | If you did not receive a copy of the license and are unable to         |
  | obtain it through the world-wide-web, please send an email             |
  | to license@zephir-lang.com so we can send you a copy immediately.      |
  +------------------------------------------------------------------------+
  | Authors: Andres Gutierrez <andres@zephir-lang.com>                     |
  |          Eduar Carvajal <eduar@zephir-lang.com>                        |
  |          Vladimir Kolesnikov <vladimir@extrememember.com>              |
  +------------------------------------------------------------------------+
*/

#ifndef ZEPHIR_KERNEL_FCALL_H
#define ZEPHIR_KERNEL_FCALL_H

#include "php_ext.h"
#include "kernel/main.h"
#include "kernel/memory.h"
#include <Zend/zend_hash.h>
#include <Zend/zend.h>

typedef enum _zephir_call_type {
	zephir_fcall_parent,
	zephir_fcall_self,
	zephir_fcall_static,
	zephir_fcall_ce,
	zephir_fcall_method,
	zephir_fcall_function
} zephir_call_type;

#ifndef ZEPHIR_RELEASE

typedef struct _zephir_fcall_cache_entry {
	zend_function *f;
	zend_uint times;
} zephir_fcall_cache_entry;

#else

typedef zend_function zephir_fcall_cache_entry;

#endif

/**
 * @addtogroup callfuncs Calling Functions
 * @{
 */

/**
 * @brief Invokes a function @a func_name and returns if the function fails due to an error or exception.
 * @param[out] return_value_ptr function return value (<tt>zval**</tt>); can be @c NULL (in this case it is assumed that the caller is not interested in the return value)
 * @param[in] func_name name of the function to call (<tt>const char*</tt>)
 * @param arguments function arguments (<tt>zval*</tt>)
 * @note If the call fails or an exception occurs, the memory frame is @em not restored.
 * In this case if @c return_value_ptr is not @c NULL, <tt>*return_value_ptr</tt> is set to @c NULL
 */
#define ZEPHIR_CALL_FUNCTIONW(return_value_ptr, func_name, ...) \
	do { \
		zval *params_[] = {__VA_ARGS__}; \
		if (__builtin_constant_p(func_name)) { \
			ZEPHIR_LAST_CALL_STATUS = zephir_call_func_aparams(return_value_ptr, func_name, sizeof(func_name)-1, sizeof(params_)/sizeof(zval*), params_ TSRMLS_CC); \
		} \
		else { \
			ZEPHIR_LAST_CALL_STATUS = zephir_call_func_aparams(return_value_ptr, func_name, strlen(func_name), sizeof(params_)/sizeof(zval*), params_ TSRMLS_CC); \
		} \
	} while (0)

/**
 * @brief Invokes a function @a func_name and returns if the function fails due to an error or exception.
 * @param[out] return_value_ptr function return value (<tt>zval**</tt>); can be @c NULL (in this case it is assumed that the caller is not interested in the return value)
 * @param[in] func_name name of the function to call (<tt>const char*</tt>)
 * @param arguments function arguments (<tt>zval*</tt>)
 * @note If the call fails or an exception occurs, the memory frame is restored.
 * In this case if @c return_value_ptr is not @c NULL, <tt>*return_value_ptr</tt> is set to @c NULL
 */
#define ZEPHIR_CALL_FUNCTION(return_value_ptr, func_name, cache, ...) \
	do { \
		zval *params_[] = {__VA_ARGS__}; \
		ZEPHIR_OBSERVE_OR_NULLIFY_PPZV(return_value_ptr); \
		if (__builtin_constant_p(func_name)) { \
			ZEPHIR_LAST_CALL_STATUS = zephir_call_func_aparams(return_value_ptr, func_name, sizeof(func_name)-1, cache, sizeof(params_)/sizeof(zval*), params_ TSRMLS_CC); \
		} \
		else { \
			ZEPHIR_LAST_CALL_STATUS = zephir_call_func_aparams(return_value_ptr, func_name, strlen(func_name), cache, sizeof(params_)/sizeof(zval*), params_ TSRMLS_CC); \
		} \
	} while (0)

/**
 * @brief Invokes a function @a func_name passing @c return_value and @c return_value_ptr
 * as return value address; returns if the function fails due to an error or exception.
 * @param[in] func_name name of the function to call (<tt>const char*</tt>)
 * @param arguments function arguments (<tt>zval*</tt>)
 * @note If the call fails or an exception occurs, the memory frame is @em not restored.
 * @li if @c return_value_ptr is not @c NULL, @c *return_value_ptr is initialized with @c ALLOC_INIT_ZVAL
 * @li otherwise, if @c return_value is not @c NULL, @c return_value and @c *return_value are not changed
 */
#define ZEPHIR_RETURN_CALL_FUNCTIONW(func_name, cache, ...) \
	do { \
		zval *params_[] = {__VA_ARGS__}; \
		if (__builtin_constant_p(func_name)) { \
			ZEPHIR_LAST_CALL_STATUS = zephir_return_call_function(return_value, return_value_ptr, func_name, sizeof(func_name)-1, cache, sizeof(params_)/sizeof(zval*), params_ TSRMLS_CC); \
		} \
		else { \
			ZEPHIR_LAST_CALL_STATUS = zephir_return_call_function(return_value, return_value_ptr, func_name, strlen(func_name), cache, sizeof(params_)/sizeof(zval*), params_ TSRMLS_CC); \
		} \
	} while (0)

/**
 * @brief Invokes a function @a func_name passing @c return_value and @c return_value_ptr
 * as return value address; returns if the function fails due to an error or exception.
 * @param[in] func_name name of the function to call (<tt>const char*</tt>)
 * @param arguments function arguments (<tt>zval*</tt>)
 * @note If the call fails or an exception occurs, the memory frame is restored.
 * @li if @c return_value_ptr is not @c NULL, @c *return_value_ptr is initialized with @c ALLOC_INIT_ZVAL
 * @li otherwise, if @c return_value is not @c NULL, @c return_value and @c *return_value are not changed
 */
#define ZEPHIR_RETURN_CALL_FUNCTION(func_name, cache, ...) \
	do { \
		zval *params_[] = {__VA_ARGS__}; \
		if (__builtin_constant_p(func_name)) { \
			ZEPHIR_LAST_CALL_STATUS = zephir_return_call_function(return_value, return_value_ptr, func_name, sizeof(func_name)-1, cache, sizeof(params_)/sizeof(zval*), params_ TSRMLS_CC); \
		} \
		else { \
			ZEPHIR_LAST_CALL_STATUS = zephir_return_call_function(return_value, return_value_ptr, func_name, strlen(func_name), cache, sizeof(params_)/sizeof(zval*), params_ TSRMLS_CC); \
		} \
	} while (0)

/**
 * @brief Invokes a function @a func_name and returns if the function fails due to an error or exception.
 * @param[out] return_value_ptr function return value (<tt>zval**</tt>); can be @c NULL (in this case it is assumed that the caller is not interested in the return value)
 * @param[in] func_name name of the function to call (<tt>const char*</tt>)
 * @param arguments function arguments (<tt>zval*</tt>)
 * @note If the call fails or an exception occurs, the memory frame is restored.
 * In this case if @c return_value_ptr is not @c NULL, <tt>*return_value_ptr</tt> is set to @c NULL
 */
#define ZEPHIR_CALL_ZVAL_FUNCTION(return_value_ptr, func_name, cache, ...) \
	do { \
		zval *params_[] = {__VA_ARGS__}; \
		ZEPHIR_OBSERVE_OR_NULLIFY_PPZV(return_value_ptr); \
		if (__builtin_constant_p(func_name)) { \
			ZEPHIR_LAST_CALL_STATUS = zephir_call_zval_func_aparams(return_value_ptr, func_name, cache, sizeof(params_)/sizeof(zval*), params_ TSRMLS_CC); \
		} \
		else { \
			ZEPHIR_LAST_CALL_STATUS = zephir_call_zval_func_aparams(return_value_ptr, func_name, cache, sizeof(params_)/sizeof(zval*), params_ TSRMLS_CC); \
		} \
	} while (0)

/**
 * @brief Invokes a function @a func_name passing @c return_value and @c return_value_ptr
 * as return value address; returns if the function fails due to an error or exception.
 * @param[in] func_name name of the function to call (<tt>const char*</tt>)
 * @param arguments function arguments (<tt>zval*</tt>)
 * @note If the call fails or an exception occurs, the memory frame is restored.
 * @li if @c return_value_ptr is not @c NULL, @c *return_value_ptr is initialized with @c ALLOC_INIT_ZVAL
 * @li otherwise, if @c return_value is not @c NULL, @c return_value and @c *return_value are not changed
 */
#define ZEPHIR_RETURN_CALL_ZVAL_FUNCTION(func_name, cache, ...) \
	do { \
		zval *params_[] = {__VA_ARGS__}; \
		if (__builtin_constant_p(func_name)) { \
			ZEPHIR_LAST_CALL_STATUS = zephir_return_call_zval_function(return_value, return_value_ptr, func_name, cache, sizeof(params_)/sizeof(zval*), params_ TSRMLS_CC); \
		} \
		else { \
			ZEPHIR_LAST_CALL_STATUS = zephir_return_call_zval_function(return_value, return_value_ptr, func_name, cache, sizeof(params_)/sizeof(zval*), params_ TSRMLS_CC); \
		} \
	} while (0)

/**
 * @}
 */

#define ZEPHIR_CALL_METHODW(return_value_ptr, object, method, cache, ...) \
	do { \
		zval *params_[] = {__VA_ARGS__}; \
		if (__builtin_constant_p(method)) { \
			ZEPHIR_LAST_CALL_STATUS = zephir_call_class_method_aparams(return_value_ptr, Z_OBJCE_P(object), zephir_fcall_method, object, method, sizeof(method)-1, cache, sizeof(params_)/sizeof(zval*), params_ TSRMLS_CC); \
		} \
		else { \
			ZEPHIR_LAST_CALL_STATUS = zephir_call_class_method_aparams(return_value_ptr, Z_OBJCE_P(object), zephir_fcall_method, object, method, strlen(method), cache, sizeof(params_)/sizeof(zval*), params_ TSRMLS_CC); \
		} \
	} while (0)

#define ZEPHIR_CALL_METHOD(return_value_ptr, object, method, cache, ...) \
	do { \
		zval *params_[] = {__VA_ARGS__}; \
		ZEPHIR_OBSERVE_OR_NULLIFY_PPZV(return_value_ptr); \
		if (__builtin_constant_p(method)) { \
			ZEPHIR_LAST_CALL_STATUS = zephir_call_class_method_aparams(return_value_ptr, Z_OBJCE_P(object), zephir_fcall_method, object, method, sizeof(method)-1, cache, sizeof(params_)/sizeof(zval*), params_ TSRMLS_CC); \
		} \
		else { \
			ZEPHIR_LAST_CALL_STATUS = zephir_call_class_method_aparams(return_value_ptr, Z_OBJCE_P(object), zephir_fcall_method, object, method, strlen(method), cache, sizeof(params_)/sizeof(zval*), params_ TSRMLS_CC); \
		} \
	} while (0)

#define ZEPHIR_RETURN_CALL_METHODW(object, method, cache, ...) \
	do { \
		zval *params_[] = {__VA_ARGS__}; \
		if (__builtin_constant_p(method)) { \
			ZEPHIR_LAST_CALL_STATUS = zephir_return_call_class_method(return_value, return_value_ptr, Z_OBJCE_P(object), zephir_fcall_method, object, method, sizeof(method)-1, cache, sizeof(params_)/sizeof(zval*), params_ TSRMLS_CC); \
		} \
		else { \
			ZEPHIR_LAST_CALL_STATUS = zephir_return_call_class_method(return_value, return_value_ptr, Z_OBJCE_P(object), zephir_fcall_method, object, method, strlen(method), cache, sizeof(params_)/sizeof(zval*), params_ TSRMLS_CC); \
		} \
	} while (0)

#define ZEPHIR_RETURN_CALL_METHOD(object, method, cache, ...) \
	do { \
		zval *params_[] = {__VA_ARGS__}; \
		if (__builtin_constant_p(method)) { \
			ZEPHIR_LAST_CALL_STATUS = zephir_return_call_class_method(return_value, return_value_ptr, Z_OBJCE_P(object), zephir_fcall_method, object, method, sizeof(method)-1, cache, sizeof(params_)/sizeof(zval*), params_ TSRMLS_CC); \
		} \
		else { \
			ZEPHIR_LAST_CALL_STATUS = zephir_return_call_class_method(return_value, return_value_ptr, Z_OBJCE_P(object), zephir_fcall_method, object, method, strlen(method), cache, sizeof(params_)/sizeof(zval*), params_ TSRMLS_CC); \
		} \
	} while (0)

#define ZEPHIR_CALL_METHOD_THIS(return_value_ptr, method, cache, ...) \
	do { \
		zval *params_[] = {__VA_ARGS__}; \
		ZEPHIR_OBSERVE_OR_NULLIFY_PPZV(return_value_ptr); \
		if (__builtin_constant_p(method)) { \
			ZEPHIR_LAST_CALL_STATUS = zephir_call_class_method_aparams(return_value_ptr, THIS_CE, zephir_fcall_method, this_ptr, method, sizeof(method)-1, cache, sizeof(params_)/sizeof(zval*), params_ TSRMLS_CC); \
		} \
		else { \
			ZEPHIR_LAST_CALL_STATUS = zephir_call_class_method_aparams(return_value_ptr, THIS_CE, zephir_fcall_method, this_ptr, method, strlen(method), cache, sizeof(params_)/sizeof(zval*), params_ TSRMLS_CC); \
		} \
	} while (0)

#define ZEPHIR_CALL_PARENTW(return_value_ptr, class_entry, this_ptr, method, cache, ...) \
	do { \
		zval *params_[] = {__VA_ARGS__}; \
		if (__builtin_constant_p(method)) { \
			ZEPHIR_LAST_CALL_STATUS = zephir_call_class_method_aparams(return_value_ptr, class_entry, zephir_fcall_parent, this_ptr, method, sizeof(method)-1, cache, sizeof(params_)/sizeof(zval*), params_ TSRMLS_CC); \
		} \
		else { \
			ZEPHIR_LAST_CALL_STATUS = zephir_call_class_method_aparams(return_value_ptr, class_entry, zephir_fcall_parent, this_ptr, method, strlen(method), cache, sizeof(params_)/sizeof(zval*), params_ TSRMLS_CC); \
		} \
	} while (0)

#define ZEPHIR_CALL_PARENT(return_value_ptr, class_entry, this_ptr, method, cache, ...) \
	do { \
		zval *params_[] = {__VA_ARGS__}; \
		ZEPHIR_OBSERVE_OR_NULLIFY_PPZV(return_value_ptr); \
		if (__builtin_constant_p(method)) { \
			ZEPHIR_LAST_CALL_STATUS = zephir_call_class_method_aparams(return_value_ptr, class_entry, zephir_fcall_parent, this_ptr, method, sizeof(method)-1, cache, sizeof(params_)/sizeof(zval*), params_ TSRMLS_CC); \
		} \
		else { \
			ZEPHIR_LAST_CALL_STATUS = zephir_call_class_method_aparams(return_value_ptr, class_entry, zephir_fcall_parent, this_ptr, method, strlen(method), cache, sizeof(params_)/sizeof(zval*), params_ TSRMLS_CC); \
		} \
	} while (0)

#define ZEPHIR_RETURN_CALL_PARENTW(class_entry, this_ptr, method, ...) \
	do { \
		zval *params_[] = {__VA_ARGS__}; \
		if (__builtin_constant_p(method)) { \
			ZEPHIR_LAST_CALL_STATUS = zephir_return_call_class_method(return_value, return_value_ptr, class_entry, zephir_fcall_parent, this_ptr, method, sizeof(method)-1, cache, sizeof(params_)/sizeof(zval*), params_ TSRMLS_CC); \
		} \
		else { \
			ZEPHIR_LAST_CALL_STATUS = zephir_return_call_class_method(return_value, return_value_ptr, class_entry, zephir_fcall_parent, this_ptr, method, strlen(method), cache, sizeof(params_)/sizeof(zval*), params_ TSRMLS_CC); \
		} \
	} while (0)

#define ZEPHIR_RETURN_CALL_PARENT(class_entry, this_ptr, method, cache, ...) \
	do { \
		zval *params_[] = {__VA_ARGS__}; \
		if (__builtin_constant_p(method)) { \
			ZEPHIR_LAST_CALL_STATUS = zephir_return_call_class_method(return_value, return_value_ptr, class_entry, zephir_fcall_parent, this_ptr, method, sizeof(method)-1, cache, sizeof(params_)/sizeof(zval*), params_ TSRMLS_CC); \
		} \
		else { \
			ZEPHIR_LAST_CALL_STATUS = zephir_return_call_class_method(return_value, return_value_ptr, class_entry, zephir_fcall_parent, this_ptr, method, strlen(method), cache, sizeof(params_)/sizeof(zval*), params_ TSRMLS_CC); \
		} \
	} while (0)

#define ZEPHIR_CALL_SELFW(return_value_ptr, method, cache, ...) \
	do { \
		zval *params_[] = {__VA_ARGS__}; \
		if (__builtin_constant_p(method)) { \
			ZEPHIR_LAST_CALL_STATUS = zephir_call_class_method_aparams(return_value_ptr, NULL, zephir_fcall_self, NULL, method, cache, sizeof(method)-1, sizeof(params_)/sizeof(zval*), params_ TSRMLS_CC); \
		} \
		else { \
			ZEPHIR_LAST_CALL_STATUS = zephir_call_class_method_aparams(return_value_ptr, NULL, zephir_fcall_self, NULL, method, cache, strlen(method), sizeof(params_)/sizeof(zval*), params_ TSRMLS_CC); \
		} \
	} while (0)

#define ZEPHIR_CALL_SELF(return_value_ptr, method, cache, ...) \
	do { \
		zval *params_[] = {__VA_ARGS__}; \
		ZEPHIR_OBSERVE_OR_NULLIFY_PPZV(return_value_ptr); \
		if (__builtin_constant_p(method)) { \
			ZEPHIR_LAST_CALL_STATUS = zephir_call_class_method_aparams(return_value_ptr, NULL, zephir_fcall_self, NULL, method, sizeof(method)-1, cache, sizeof(params_)/sizeof(zval*), params_ TSRMLS_CC); \
		} \
		else { \
			ZEPHIR_LAST_CALL_STATUS = zephir_call_class_method_aparams(return_value_ptr, NULL, zephir_fcall_self, NULL, method, strlen(method), cache, sizeof(params_)/sizeof(zval*), params_ TSRMLS_CC); \
		} \
	} while (0)

#define ZEPHIR_RETURN_CALL_SELFW(method, ...) \
	do { \
		zval *params_[] = {__VA_ARGS__}; \
		if (__builtin_constant_p(method)) { \
			ZEPHIR_LAST_CALL_STATUS = zephir_return_call_class_method(return_value, return_value_ptr, NULL, zephir_fcall_self, NULL, method, sizeof(method)-1, cache, sizeof(params_)/sizeof(zval*), params_ TSRMLS_CC); \
		} \
		else { \
			ZEPHIR_LAST_CALL_STATUS = zephir_return_call_class_method(return_value, return_value_ptr, NULL, zephir_fcall_self, NULL, method, strlen(method), cache, sizeof(params_)/sizeof(zval*), params_ TSRMLS_CC); \
		} \
	} while (0)

#define ZEPHIR_RETURN_CALL_SELF(method, cache, ...) \
	do { \
		zval *params_[] = {__VA_ARGS__}; \
		if (__builtin_constant_p(method)) { \
			ZEPHIR_LAST_CALL_STATUS = zephir_return_call_class_method(return_value, return_value_ptr, NULL, zephir_fcall_self, NULL, method, sizeof(method)-1, cache, sizeof(params_)/sizeof(zval*), params_ TSRMLS_CC); \
		} \
		else { \
			ZEPHIR_LAST_CALL_STATUS = zephir_return_call_class_method(return_value, return_value_ptr, NULL, zephir_fcall_self, NULL, method, strlen(method), cache, sizeof(params_)/sizeof(zval*), params_ TSRMLS_CC); \
		} \
	} while (0)

#define ZEPHIR_CALL_STATICW(return_value_ptr, method, ...) \
	do { \
		zval *params_[] = {__VA_ARGS__}; \
		if (__builtin_constant_p(method)) { \
			ZEPHIR_LAST_CALL_STATUS = zephir_call_class_method_aparams(return_value_ptr, NULL, zephir_fcall_static, NULL, method, sizeof(method)-1, sizeof(params_)/sizeof(zval*), params_ TSRMLS_CC); \
		} \
		else { \
			ZEPHIR_LAST_CALL_STATUS = zephir_call_class_method_aparams(return_value_ptr, NULL, zephir_fcall_static, NULL, method, strlen(method), sizeof(params_)/sizeof(zval*), params_ TSRMLS_CC); \
		} \
	} while (0)

#define ZEPHIR_CALL_STATIC(return_value_ptr, method, cache, ...) \
	do { \
		zval *params_[] = {__VA_ARGS__}; \
		ZEPHIR_OBSERVE_OR_NULLIFY_PPZV(return_value_ptr); \
		if (__builtin_constant_p(method)) { \
			ZEPHIR_LAST_CALL_STATUS = zephir_call_class_method_aparams(return_value_ptr, NULL, zephir_fcall_static, NULL, method, sizeof(method)-1, cache, sizeof(params_)/sizeof(zval*), params_ TSRMLS_CC); \
		} \
		else { \
			ZEPHIR_LAST_CALL_STATUS = zephir_call_class_method_aparams(return_value_ptr, NULL, zephir_fcall_static, NULL, method, strlen(method), cache, sizeof(params_)/sizeof(zval*), params_ TSRMLS_CC); \
		} \
	} while (0)

#define ZEPHIR_RETURN_CALL_STATICW(method, cache, ...) \
	do { \
		zval *params_[] = {__VA_ARGS__}; \
		if (__builtin_constant_p(method)) { \
			RETURN_ON_FAILURE(zephir_return_call_class_method(return_value, return_value_ptr, NULL, zephir_fcall_static, NULL, method, sizeof(method)-1, cache, sizeof(params_)/sizeof(zval*), params_ TSRMLS_CC)); \
		} \
		else { \
			RETURN_ON_FAILURE(zephir_return_call_class_method(return_value, return_value_ptr, NULL, zephir_fcall_static, NULL, method, strlen(method), cache, sizeof(params_)/sizeof(zval*), params_ TSRMLS_CC)); \
		} \
	} while (0)

#define ZEPHIR_RETURN_CALL_STATIC(method, cache, ...) \
	do { \
		zval *params_[] = {__VA_ARGS__}; \
		if (__builtin_constant_p(method)) { \
			ZEPHIR_LAST_CALL_STATUS = zephir_return_call_class_method(return_value, return_value_ptr, NULL, zephir_fcall_static, NULL, method, sizeof(method)-1, cache, sizeof(params_)/sizeof(zval*), params_ TSRMLS_CC); \
		} \
		else { \
			ZEPHIR_LAST_CALL_STATUS = zephir_return_call_class_method(return_value, return_value_ptr, NULL, zephir_fcall_static, NULL, method, strlen(method), cache, sizeof(params_)/sizeof(zval*), params_ TSRMLS_CC); \
		} \
	} while (0)

#define ZEPHIR_CALL_CE_STATICW(return_value_ptr, class_entry, method, cache, ...) \
	do { \
		zval *params[] = {__VA_ARGS__}; \
		if (__builtin_constant_p(method)) { \
			ZEPHIR_LAST_CALL_STATUS = zephir_call_class_method_aparams(return_value_ptr, class_entry, zephir_fcall_ce, NULL, method, sizeof(method)-1, cache, sizeof(params)/sizeof(zval*), params TSRMLS_CC); \
		} \
		else { \
			ZEPHIR_LAST_CALL_STATUS = zephir_call_class_method_aparams(return_value_ptr, class_entry, zephir_fcall_ce, NULL, method, strlen(method), cache, sizeof(params)/sizeof(zval*), params TSRMLS_CC); \
		} \
	} while (0)

#define ZEPHIR_CALL_CE_STATIC(return_value_ptr, class_entry, method, cache, ...) \
	do { \
		zval *params_[] = {__VA_ARGS__}; \
		ZEPHIR_OBSERVE_OR_NULLIFY_PPZV(return_value_ptr); \
		if (__builtin_constant_p(method)) { \
			ZEPHIR_LAST_CALL_STATUS = zephir_call_class_method_aparams(return_value_ptr, class_entry, zephir_fcall_ce, NULL, method, sizeof(method)-1, cache, sizeof(params_)/sizeof(zval*), params_ TSRMLS_CC); \
		} \
		else { \
			ZEPHIR_LAST_CALL_STATUS = zephir_call_class_method_aparams(return_value_ptr, class_entry, zephir_fcall_ce, NULL, method, strlen(method), cache, sizeof(params_)/sizeof(zval*), params_ TSRMLS_CC); \
		} \
	} while (0)

#define ZEPHIR_RETURN_CALL_CE_STATICW(class_entry, method, cache, ...) \
	do { \
		zval *params_[] = {__VA_ARGS__}; \
		if (__builtin_constant_p(method)) { \
			ZEPHIR_LAST_CALL_STATUS = zephir_return_call_class_method(return_value, return_value_ptr, class_entry, zephir_fcall_ce, NULL, method, sizeof(method)-1, sizeof(params_)/sizeof(zval*), params_ TSRMLS_CC); \
		} \
		else { \
			ZEPHIR_LAST_CALL_STATUS = zephir_return_call_class_method(return_value, return_value_ptr, class_entry, zephir_fcall_ce, NULL, method, strlen(method), sizeof(params_)/sizeof(zval*), params_ TSRMLS_CC); \
		} \
	} while (0)

#define ZEPHIR_RETURN_CALL_CE_STATIC(class_entry, method, cache, ...) \
	do { \
		zval *params_[] = {__VA_ARGS__}; \
		if (__builtin_constant_p(method)) { \
			ZEPHIR_LAST_CALL_STATUS = zephir_return_call_class_method(return_value, return_value_ptr, class_entry, zephir_fcall_ce, NULL, method, sizeof(method)-1, cache, sizeof(params_)/sizeof(zval*), params_ TSRMLS_CC); \
		} \
		else { \
			ZEPHIR_LAST_CALL_STATUS = zephir_return_call_class_method(return_value, return_value_ptr, class_entry, zephir_fcall_ce, NULL, method, strlen(method), cache, sizeof(params_)/sizeof(zval*), params_ TSRMLS_CC); \
		} \
	} while (0)

/** Use these functions to call functions in the PHP userland using an arbitrary zval as callable */
#define ZEPHIR_CALL_USER_FUNC(return_value, handler) ZEPHIR_CALL_USER_FUNC_ARRAY(return_value, handler, NULL)
#define ZEPHIR_CALL_USER_FUNC_ARRAY(return_value, handler, params) \
	do { \
		ZEPHIR_LAST_CALL_STATUS = zephir_call_user_func_array(return_value, handler, params TSRMLS_CC); \
	} while (0)

#define ZEPHIR_CALL_USER_FUNC_ARRAY_NOEX(return_value, handler, params) \
	do { \
		ZEPHIR_LAST_CALL_STATUS = zephir_call_user_func_array_noex(return_value, handler, params TSRMLS_CC); \
	} while (0)

int zephir_call_func_aparams(zval **return_value_ptr, const char *func_name, uint func_length,
	zephir_fcall_cache_entry **cache_entry,
	uint param_count, zval **params TSRMLS_DC) ZEPHIR_ATTR_WARN_UNUSED_RESULT;

int zephir_call_zval_func_aparams(zval **return_value_ptr, zval *func_name,
	zephir_fcall_cache_entry **cache_entry,
	uint param_count, zval **params TSRMLS_DC) ZEPHIR_ATTR_WARN_UNUSED_RESULT;

/**
 * @ingroup callfuncs
 * @brief Calls a function @a func
 * @param return_value Calling function's @c return_value
 * @param return_value_ptr Calling function's @c return_value_ptr
 * @param func Function name
 * @param func_len Length of @a func (<tt>strlen(func)</tt>)
 * @param param_count Number of parameters
 */
ZEPHIR_ATTR_WARN_UNUSED_RESULT static inline int zephir_return_call_function(zval *return_value, zval **return_value_ptr,
	const char *func, uint func_len, zephir_fcall_cache_entry **cache_entry, uint param_count, zval **params TSRMLS_DC)
{
	zval *rv = NULL, **rvp = return_value_ptr ? return_value_ptr : &rv;
	int status;

	if (return_value_ptr) {
		zval_ptr_dtor(return_value_ptr);
		*return_value_ptr = NULL;
	}

	status = zephir_call_func_aparams(rvp, func, func_len, cache_entry, param_count, params TSRMLS_CC);

	if (status == FAILURE) {
		if (return_value_ptr && EG(exception)) {
			ALLOC_INIT_ZVAL(*return_value_ptr);
		}

		return FAILURE;
	}

	if (!return_value_ptr) {
		COPY_PZVAL_TO_ZVAL(*return_value, rv);
	}

	return SUCCESS;
}

/**
 * @ingroup callfuncs
 * @brief Calls a function @a func
 * @param return_value Calling function's @c return_value
 * @param return_value_ptr Calling function's @c return_value_ptr
 * @param func Function name
 * @param func_len Length of @a func (<tt>strlen(func)</tt>)
 * @param param_count Number of parameters
 */
ZEPHIR_ATTR_WARN_UNUSED_RESULT static inline int zephir_return_call_zval_function(zval *return_value, zval **return_value_ptr,
	zval *func, zephir_fcall_cache_entry **cache_entry, uint param_count, zval **params TSRMLS_DC)
{
	zval *rv = NULL, **rvp = return_value_ptr ? return_value_ptr : &rv;
	int status;

	if (return_value_ptr) {
		zval_ptr_dtor(return_value_ptr);
		*return_value_ptr = NULL;
	}

	status = zephir_call_zval_func_aparams(rvp, func, cache_entry, param_count, params TSRMLS_CC);

	if (status == FAILURE) {
		if (return_value_ptr && EG(exception)) {
			ALLOC_INIT_ZVAL(*return_value_ptr);
		}

		return FAILURE;
	}

	if (!return_value_ptr) {
		COPY_PZVAL_TO_ZVAL(*return_value, rv);
	}

	return SUCCESS;
}

int zephir_call_class_method_aparams(zval **return_value_ptr, zend_class_entry *ce, zephir_call_type type, zval *object,
	const char *method_name, uint method_len,
	zephir_fcall_cache_entry **cache_entry,
	uint param_count, zval **params TSRMLS_DC) ZEPHIR_ATTR_WARN_UNUSED_RESULT;

ZEPHIR_ATTR_WARN_UNUSED_RESULT static inline int zephir_return_call_class_method(zval *return_value,
	zval **return_value_ptr, zend_class_entry *ce, zephir_call_type type, zval *object,
	const char *method_name, uint method_len,
	zephir_fcall_cache_entry **cache_entry,
	uint param_count, zval **params TSRMLS_DC)
{
	zval *rv = NULL, **rvp = return_value_ptr ? return_value_ptr : &rv;
	int status;

	if (return_value_ptr) {
		zval_ptr_dtor(return_value_ptr);
		*return_value_ptr = NULL;
	}

	status = zephir_call_class_method_aparams(rvp, ce, type, object, method_name, method_len, cache_entry, param_count, params TSRMLS_CC);

	if (status == FAILURE) {
		if (return_value_ptr && EG(exception)) {
			ALLOC_INIT_ZVAL(*return_value_ptr);
		}

		return FAILURE;
	}

	if (!return_value_ptr) {
		COPY_PZVAL_TO_ZVAL(*return_value, rv);
	}

	return SUCCESS;
}

/**
 * @brief $object->$method()
 */
//ZEPHIR_ATTR_WARN_UNUSED_RESULT ZEPHIR_ATTR_NONNULL2(2, 3)
//static inline int zephir_call_method(zval **return_value_ptr, zval *object, const char *method,
//	zephir_fcall_cache_entry **cache_entry, uint nparams, zval **params TSRMLS_DC)
//{
	//return zephir_call_class_method_aparams(return_value_ptr, Z_OBJCE_P(object), zephir_fcall_method,
	//	object, method, strlen(method), cache_entry, nparams, params TSRMLS_CC);
//}

//ZEPHIR_ATTR_WARN_UNUSED_RESULT ZEPHIR_ATTR_NONNULL3(1, 3, 4)
//static inline int zephir_return_call_method(zval *return_value, zval **return_value_ptr, zval *object, const char *method,
//	zephir_fcall_cache_entry **cache_entry, uint nparams, zval **params TSRMLS_DC)
//{
	//return zephir_return_call_class_method(return_value, return_value_ptr, Z_OBJCE_P(object), zephir_fcall_method, object, method, strlen(method), nparams, params TSRMLS_CC);
//}

/**
 * @brief static::$method()
 */
//ZEPHIR_ATTR_WARN_UNUSED_RESULT ZEPHIR_ATTR_NONNULL1(2)
//static inline int zephir_call_static(zval **return_value_ptr, const char *method, zephir_fcall_cache_entry **cache_entry, uint nparams, zval **params TSRMLS_DC)
//{
	//return zephir_call_class_method_aparams(return_value_ptr, NULL, zephir_fcall_static, NULL, method, strlen(method), nparams, params TSRMLS_CC);
//}

//ZEPHIR_ATTR_WARN_UNUSED_RESULT ZEPHIR_ATTR_NONNULL2(1, 3)
//static inline int zephir_return_call_static(zval *return_value, zval **return_value_ptr, const char *method, zephir_fcall_cache_entry **cache_entry, uint nparams, zval **params TSRMLS_DC)
//{
	//return zephir_return_call_class_method(return_value, return_value_ptr, NULL, zephir_fcall_static, NULL, method, strlen(method), cache_entry, nparams, params TSRMLS_CC);
//}

/**
 * @brief self::$method()
 */
//ZEPHIR_ATTR_WARN_UNUSED_RESULT ZEPHIR_ATTR_NONNULL1(2)
//static inline int zephir_call_self(zval **return_value_ptr, const char *method, zephir_fcall_cache_entry **cache_entry, uint nparams, zval **params TSRMLS_DC)
//{
	//return zephir_call_class_method_aparams(return_value_ptr, NULL, zephir_fcall_self, NULL, method, strlen(method), cache_entry, nparams, params TSRMLS_CC);
//}

//ZEPHIR_ATTR_WARN_UNUSED_RESULT ZEPHIR_ATTR_NONNULL2(1, 3)
//static inline int zephir_return_call_self(zval *return_value, zval **return_value_ptr, const char *method, uint nparams, zval **params TSRMLS_DC)
//{
	//return zephir_return_call_class_method(return_value, return_value_ptr, NULL, zephir_fcall_self, NULL, method, strlen(method), nparams, params TSRMLS_CC);
//}

/**
 * @brief parent::$method()
 */
//ZEPHIR_ATTR_WARN_UNUSED_RESULT ZEPHIR_ATTR_NONNULL1(3)
//static inline int zephir_call_parent(zval **return_value_ptr, zval *object, const char *method, uint nparams, zval **params TSRMLS_DC)
//{
	//return zephir_call_class_method_aparams(return_value_ptr, (object ? Z_OBJCE_P(object) : NULL), zephir_fcall_parent, object, method, strlen(method), nparams, params TSRMLS_CC);
//}

//ZEPHIR_ATTR_WARN_UNUSED_RESULT ZEPHIR_ATTR_NONNULL2(1, 4)
//static inline int zephir_return_call_parent(zval *return_value, zval **return_value_ptr, zval *object, const char *method, zephir_fcall_cache_entry **cache_entry, uint nparams, zval **params TSRMLS_DC)
//{
	//return zephir_return_call_class_method(return_value, return_value_ptr, (object ? Z_OBJCE_P(object) : NULL), zephir_fcall_parent, object, method, strlen(method), cache_entry, nparams, params TSRMLS_CC);
//}

/**
 * @brief $ce::$method()
 */
//ZEPHIR_ATTR_WARN_UNUSED_RESULT ZEPHIR_ATTR_NONNULL2(2, 3)
//static inline int zephir_call_ce(zval **return_value_ptr, zend_class_entry *ce, const char *method, zephir_fcall_cache_entry **cache_entry, uint nparams, zval **params TSRMLS_DC)
//{
	//return zephir_call_class_method_aparams(return_value_ptr, ce, zephir_fcall_ce, NULL, method, strlen(method), cache_entry, nparams, params TSRMLS_CC);
//}

//ZEPHIR_ATTR_WARN_UNUSED_RESULT ZEPHIR_ATTR_NONNULL3(1, 3, 4)
//static inline int zephir_return_call_ce(zval *return_value, zval **return_value_ptr, zend_class_entry *ce, const char *method, zephir_fcall_cache_entry **cache_entry, uint nparams, zval **params TSRMLS_DC)
//{
	//return zephir_return_call_class_method(return_value, return_value_ptr, ce, zephir_fcall_ce, NULL, method, strlen(method), nparams, params TSRMLS_CC);
//}

/** Fast call_user_func_array/call_user_func */
int zephir_call_user_func_array_noex(zval *return_value, zval *handler, zval *params TSRMLS_DC) ZEPHIR_ATTR_WARN_UNUSED_RESULT;

/**
 * Replaces call_user_func_array avoiding function lookup
 */
ZEPHIR_ATTR_WARN_UNUSED_RESULT static inline int zephir_call_user_func_array(zval *return_value, zval *handler, zval *params TSRMLS_DC)
{
	int status = zephir_call_user_func_array_noex(return_value, handler, params TSRMLS_CC);
	return (EG(exception)) ? FAILURE : status;
}

/**
 * @brief Checks if the class defines a constructor
 * @param ce Class entry
 * @return Whether the class defines a constructor
 */
int zephir_has_constructor_ce(const zend_class_entry *ce) ZEPHIR_ATTR_PURE ZEPHIR_ATTR_NONNULL;

/**
 * @brief Checks if an object has a constructor
 * @param object Object to check
 * @return Whether @a object has a constructor
 * @retval 0 @a object is not an object or does not have a constructor
 * @retval 1 @a object has a constructor
 */
ZEPHIR_ATTR_WARN_UNUSED_RESULT ZEPHIR_ATTR_NONNULL static inline int zephir_has_constructor(const zval *object TSRMLS_DC)
{
	return Z_TYPE_P(object) == IS_OBJECT ? zephir_has_constructor_ce(Z_OBJCE_P(object)) : 0;
}

/** PHP < 5.3.9 has problems with closures */
#if PHP_VERSION_ID <= 50309
int zephir_call_function(zend_fcall_info *fci, zend_fcall_info_cache *fci_cache TSRMLS_DC);
#define ZEPHIR_ZEND_CALL_FUNCTION_WRAPPER zephir_call_function
#else
#define ZEPHIR_ZEND_CALL_FUNCTION_WRAPPER zend_call_function
#endif

#ifndef zend_error_noreturn
#define zend_error_noreturn zend_error
#endif

#define zephir_check_call_status() \
	do \
		if (ZEPHIR_LAST_CALL_STATUS == FAILURE) { \
			ZEPHIR_MM_RESTORE(); \
			return; \
	} \
	while(0)

#define zephir_check_call_status_or_jump(label) \
	if (ZEPHIR_LAST_CALL_STATUS == FAILURE) { \
		if (EG(exception)) { \
			goto label; \
		} else { \
			ZEPHIR_MM_RESTORE(); \
			return; \
		} \
	}

#define zephir_check_temp_parameter(param) do { if (Z_REFCOUNT_P(param) > 1) zval_copy_ctor(param); else ZVAL_NULL(param); } while(0)

void zephir_eval_php(zval *str, zval *retval_ptr, char *context TSRMLS_DC);

#endif /* ZEPHIR_KERNEL_FCALL_H */
