
#ifdef HAVE_CONFIG_H
#include "../ext_config.h"
#endif

#include <php.h>
#include "../php_ext.h"
#include "../ext.h"

#include <Zend/zend_exceptions.h>

#include "kernel/main.h"


ZEPHIR_INIT_CLASS(Ann_OutputFunction) {

	ZEPHIR_REGISTER_INTERFACE(Ann, OutputFunction, ann, outputfunction, ann_outputfunction_method_entry);

	return SUCCESS;

}

ZEPHIR_DOC_METHOD(Ann_OutputFunction, forward);

ZEPHIR_DOC_METHOD(Ann_OutputFunction, derivative);

