
#ifdef HAVE_CONFIG_H
#include "../ext_config.h"
#endif

#include <php.h>
#include "../php_ext.h"
#include "../ext.h"

#include <Zend/zend_exceptions.h>

#include "kernel/main.h"


ZEPHIR_INIT_CLASS(Ann_Branch) {

	ZEPHIR_REGISTER_INTERFACE_EX(Ann, Branch, ann, branch, ann_visitee_ce, ann_branch_method_entry);

	return SUCCESS;

}

ZEPHIR_DOC_METHOD(Ann_Branch, output);

